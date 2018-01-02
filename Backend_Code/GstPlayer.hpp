#ifndef GstPlayer_HPP
#define GstPlayer_HPP

#include <gst/gst.h>
#include <string>
#include <thread>

using std::string;

static void dummy_sec(int, void*);
static void dummy_eof(void*);

typedef void (*seconds_cb)(int, void*);
typedef void (*eof_cb)(void*);

typedef struct internal_data
{
	gboolean seekEnabled = FALSE;
	GMainLoop *mainLoop = NULL;
	GstElement *playbin = NULL;
	GstElement *audioSink = NULL;
	volatile gboolean terminated;
	double playbackRate = 1.0;
	double volume = 1.0;
	gint64 duration = 0;
	GstState state = GST_STATE_NULL;
	seconds_cb seconds_cb_func = dummy_sec;
	void* seconds_cb_data = NULL;
	eof_cb eof_cb_func = dummy_eof;
	void* eof_cb_data = NULL;
} 
InternalData;

class GstPlayer
{
private:
	GstBus *bus;
	InternalData data;
	gboolean seek_enabled;
	gboolean seek_done;
	gboolean terminate;
	static gboolean handleMessage(GstBus*, GstMessage*, InternalData*);
	static gboolean handleSeconds(void*);
	GThread *t_player;

	//void* playerRoutine(void);

public:
	GstPlayer(int argc, char** argv);
	~GstPlayer(void);
	void open(string);
	int play(void);
	bool isPlaying();
	bool isLoaded();
	int pause(void);
	void advancedSeek(double);
	double getPlaybackRate();
	void getState(void);
	int getDuration(void);
	void setVolume(double);
	double getVolume(void);
	void join(void);
	static void playerRoutineHelper(void*);
	void setSecondsCb(seconds_cb, void*);
	void setEofCb(eof_cb, void*);
};

static void dummy_sec(int seconds, void*)
{
	printf("%d\n",seconds);
	//return false;
}

static void dummy_eof(void* dings)
{
	return;
}

#endif
