#include <gst/gst.h>
#include <string>
#include <thread>

using std::string;

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
} 
InternalData;

class GstPlayer
{
private:
	gboolean (*seconds_cb)(void*);
	void* seconds_cb_data;
	GstBus *bus;
	InternalData data;
	gboolean seek_enabled;
	gboolean seek_done;
	gint64 duration;
	gboolean terminate;
	static gboolean handleMessage(GstBus*, GstMessage*, InternalData*);
	GThread *t_player;

	//void* playerRoutine(void);

public:
	GstPlayer(int argc, char** argv);
	~GstPlayer(void);
	void open(string);
	int play(void);
	bool isPlaying();
	int pause(void);
	void advancedSeek(double);
	double getPlaybackRate();
	void seek(int);
	void getState(void);
	int getDuration(void);
	void setVolume(double);
	double getVolume(void);
	void join(void);
	static void playerRoutineHelper(void*);
};
