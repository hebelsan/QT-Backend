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
	volatile gboolean terminated;
} 
InternalData;

class GstPlayer
{
private:
	GstBus *bus;
	InternalData data;
	GstElement * playbin;
	gboolean playing;
	gboolean seek_enabled;
	gboolean seek_done;
	gint64 duration;
	gboolean terminate;
	gboolean handleMessage(GstBus*, GstMessage*, InternalData*);
	GThread *t_player;

	//void* playerRoutine(void);

public:
	GstPlayer(int argc, char** argv);
	~GstPlayer(void);
	void open(string);
	int play(void);
	int pause(void);
	void getState(void);
	int getDuration(void);
	void join(void);
	static void playerRoutineHelper(void*);
};
