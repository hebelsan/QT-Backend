#include "GstPlayer.hpp"

static gboolean dummy(void*);

GstPlayer::GstPlayer(int argc, char** argv)
{
	t_player = NULL;
	data.terminated = FALSE;
	duration = GST_CLOCK_TIME_NONE;
	seconds_cb = dummy;
	seconds_cb_data = NULL;
	
	/* Initialize GStreamer */
	gst_init (&argc, &argv);

	/* Create the elements */
	data.playbin = gst_element_factory_make ("playbin", "playbin");

	if (!data.playbin) {
		g_printerr ("Not all elements could be created.\n");
	}
	
	// Dem Bus den Handler zuweisen.
	bus = gst_element_get_bus (data.playbin);
	gst_bus_add_watch (bus, ((GstBusFunc)&GstPlayer::handleMessage), &data);
	setVolume(data.playbackRate);
}

void GstPlayer::open(string uri)
{
	// TODO check, if playing. If so, pause and load file.
	if(data.state != GST_STATE_READY)
	{
		gst_element_set_state(data.playbin, GST_STATE_NULL);
		advancedSeek(1.0);
	}
	/* Set the URI to play (Track öffnen) */
	g_object_set (data.playbin, "uri", uri.c_str(),NULL);
	
	/* Create a GLib Main Loop */
	if(data.mainLoop == NULL)
	{
		data.mainLoop = g_main_loop_new (NULL, FALSE);
		g_timeout_add_seconds(1, (GSourceFunc)seconds_cb, seconds_cb_data);
	}
}

int GstPlayer::play()
{
	GstStateChangeReturn ret;

	/* Start playing */
	ret = gst_element_set_state (data.playbin, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr ("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (data.playbin);
		return -1;
	}

	t_player = g_thread_new("MainLoop", (GThreadFunc)playerRoutineHelper, &data);

	return 1;
}

bool GstPlayer::isPlaying()
{
	return data.state == GST_STATE_PLAYING;
}

/* Send seek event to change rate */
void GstPlayer::advancedSeek (double rate) {
	gint64 position;
	GstFormat format = GST_FORMAT_TIME;
	GstEvent *seek_event;

	/* Obtain the current position, needed for the seek event */
	if (!gst_element_query_position (data.playbin, format, &position)) {
		g_printerr ("Unable to retrieve current position.\n");
		return;
	}

	/* Create the seek event */
	if (rate > 0) {
		seek_event = gst_event_new_seek (rate, GST_FORMAT_TIME, (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
        GST_SEEK_TYPE_SET, position, GST_SEEK_TYPE_NONE, 0);
	} else {
		seek_event = gst_event_new_seek (rate, GST_FORMAT_TIME, (GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE),
        GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_SET, position);
	}

	if (data.audioSink == NULL) {
		/* If we have not done so, obtain the sink through which we will send the seek events */
		g_object_get (data.playbin, "audio-sink", &data.audioSink, NULL);
	}

	/* Send the event */
	gst_element_send_event (data.audioSink, seek_event);
	data.playbackRate = rate;
	g_print ("Current rate: %g\n", data.playbackRate);
}

double GstPlayer::getPlaybackRate()
{
	return data.playbackRate;
}

int GstPlayer::pause()
{
	GstStateChangeReturn ret;
	ret = gst_element_set_state(data.playbin, GST_STATE_PAUSED);
	if (ret == GST_STATE_CHANGE_FAILURE) 
	{
		g_printerr ("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (data.playbin);
		return -1;
	}
	return 1;
}

int GstPlayer::getDuration()
{
	/* If we didn't know it yet, query the stream duration */
	if (!GST_CLOCK_TIME_IS_VALID (duration)) 
	{
		if (!gst_element_query_duration (data.playbin, GST_FORMAT_TIME, &duration)) 
		{
			g_printerr ("Could not query current duration.\n");
		}
	}
	return (int)(duration/GST_SECOND);
}

void GstPlayer::setVolume(double volume)
{
	g_object_set(G_OBJECT(data.playbin), "volume", (gdouble)volume, NULL);
}

void GstPlayer::join()
{
	g_thread_join(t_player);
}

void GstPlayer::playerRoutineHelper(void* instance)
{
	g_main_loop_run(((InternalData*)instance)->mainLoop);
	g_thread_exit(0);
}

void GstPlayer::seek(int seconds)
{
	if(data.seekEnabled && seconds < duration)
	gst_element_seek_simple (data.playbin, GST_FORMAT_TIME,
		(GstSeekFlags)(GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_KEY_UNIT), seconds * GST_SECOND);
}

gboolean GstPlayer::handleMessage(GstBus *bus, GstMessage *msg, InternalData* data)
{
	GError *err;
	gchar *debug_info;
	
	GstMessageType typ = GST_MESSAGE_TYPE(msg);
	
	if(typ & GST_MESSAGE_STATE_CHANGED > 0)
	{
		g_print("LOL\n");
	}

	switch (GST_MESSAGE_TYPE (msg))
	{
	case GST_MESSAGE_ERROR:
		gst_message_parse_error (msg, &err, &debug_info);
		g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
		g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
		g_clear_error (&err);
		g_free (debug_info);
		g_main_loop_quit( data->mainLoop);
		return FALSE;
		break;
    case GST_MESSAGE_EOS:
		g_print ("End-Of-Stream reached.\n");
		gst_element_set_state(data->playbin, GST_STATE_PAUSED);
		data->state = GST_STATE_NULL;
		//g_main_loop_quit( data->mainLoop );
		//g_thread_exit(0);
		//return FALSE;
		break;
	case GST_MESSAGE_DURATION:
		/* TODO The duration has changed, mark the current one as invalid */
		data->duration = GST_CLOCK_TIME_NONE;
		break;
	case GST_MESSAGE_STATE_CHANGED: 
	{
		GstState old_state, new_state, pending_state;
		gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
		if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->playbin)) {
			g_print ("Pipeline state changed from %s to %s:\n",
			gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
			data->state = new_state;
			/* Remember whether we are in the PLAYING state or not */
			//playing = (new_state == GST_STATE_PLAYING);

			if (new_state == GST_STATE_PLAYING) {
				/* We just moved to PLAYING. Check if seeking is possible */
				GstQuery *query;
				gint64 start, end;
				query = gst_query_new_seeking (GST_FORMAT_TIME);
				if (gst_element_query (data->playbin, query)) {
					gst_query_parse_seeking (query, NULL, &data->seekEnabled, &start, &end);
					if (data->seekEnabled) {
						g_print ("Seeking is ENABLED from %" GST_TIME_FORMAT " to %" GST_TIME_FORMAT "\n",
						GST_TIME_ARGS (start), GST_TIME_ARGS (end));
						data->duration = end;
					} else {
						g_print ("Seeking is DISABLED for this stream.\n");
					}
				}
				else {
					g_printerr ("Seeking query failed.");
				}
				gst_query_unref (query);
			}
		}
	} 
		break;
	}
	return TRUE;
}

GstPlayer::~GstPlayer(void)
{
	gst_element_set_state(data.playbin, GST_STATE_NULL);
	void* ret;
	g_main_loop_quit(data.mainLoop);
	gst_object_unref(data.playbin);
	gst_object_unref(bus);
	//t_player->~thread();
}

static gboolean dummy(void*)
{
	return false;
}
