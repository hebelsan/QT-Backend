#include <gst/gst.h>
#include <string>
#include <thread>

using std::string;

enum player_state
{
	PLAYING, PAUSED
};

typedef struct internal_data
{
	gboolean seekEnabled = FALSE;
	GMainLoop *mainLoop;
	GstElement *playbin;
	volatile gboolean terminated;
	gint64 duration;
} 
InternalData;

class GstPlayer
{
private:
	GstBus *bus;
	InternalData data;
	gboolean playing;
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
	int pause(void);
	void seek(int);
	void getState(void);
	int getDuration(void);
	void setVolume(double);
	double getVolume(void);
	void join(void);
	static void playerRoutineHelper(void*);
};
