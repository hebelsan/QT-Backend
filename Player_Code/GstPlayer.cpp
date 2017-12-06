#include "GstPlayer.hpp"

GstPlayer::GstPlayer(int argc, char** argv)
{
	t_player = NULL;
	data.terminated = FALSE;
	data.mainLoop = NULL;
	playing = FALSE;
	duration = GST_CLOCK_TIME_NONE;
	
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
}

void GstPlayer::open(string uri)
{
	// TODO check, if playing. If so, pause and load file.
	if(GST_IS_ELEMENT(data.playbin))
		gst_element_set_state(data.playbin, GST_STATE_NULL);
	/* Set the URI to play (Track öffnen) */
	g_object_set (data.playbin, "uri", uri.c_str(),NULL);
	
	/* Create a GLib Main Loop */
	if(data.mainLoop == NULL)
	{
		data.mainLoop = g_main_loop_new (NULL, FALSE);
		//g_main_loop_run (data.main_loop);
		//pthread_create(&t_player, NULL, &GstPlayer::playerRoutineHelper, (void*)this);
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
	//if(t_player->joinable())
		//t_player->join();
	//pthread_join(t_player, ret);
	g_thread_join(t_player);
}

/*
void* GstPlayer::playerRoutine(void)
{
	GstBus *bus = gst_element_get_bus (playbin);
	GstMessage *msg;
	do
	{
		msg = gst_bus_timed_pop_filtered (bus, 100 * GST_MSECOND,(GstMessageType)(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_DURATION));
		if(msg != NULL)
		{
			handleMessage(msg);
		}
		if (!GST_CLOCK_TIME_IS_VALID (duration)) {
			if (!gst_element_query_duration (playbin, GST_FORMAT_TIME, &duration)) {
				g_printerr ("Could not query current duration.\n");
			}
		}
	} while(!terminate);

	gst_object_unref(bus);
	gst_element_set_state(playbin, GST_STATE_NULL);
	terminate = FALSE;
}
*/
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
		g_main_loop_quit( data->mainLoop );
		g_thread_exit(0);
		return FALSE;
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
			/* Remember whether we are in the PLAYING state or not */
			//playing = (new_state == GST_STATE_PLAYING);

			//if (playing) {
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
			//}
		}
	} 
		break;
	default:
		/* We should not reach here */
		g_printerr ("Unexpected message received.\n");
		g_printerr(gst_message_type_get_name(GST_MESSAGE_TYPE(msg))); //says "unknown";
		//g_printerr("%s\n",GST_OBJECT_NAME (msg->src));
		break;
	}
	return TRUE;
}

GstPlayer::~GstPlayer()
{
	void* ret;
	gst_object_unref(data.playbin);
	gst_object_unref(bus);
	//t_player->~thread();
}
