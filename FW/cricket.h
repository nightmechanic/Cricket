// h file for the cricket project

const unsigned int PLAY_CYCLE = 	500; //in 1 MHz cycles
const unsigned int PLAY_DC = 		250; //in 1MHz cycles
const unsigned int PLAY_PERIOD = 	10;  //in play cycles
const unsigned int PAUSE_PERIOD =	10;  //in play cycles
const unsigned int PLAY_LOOPS =		100;
const unsigned int IDLE_TIME =		20; //in 50msec units
const unsigned int OUTER_LOOPS =	2; // number of cricket chirps
const unsigned int MIN_SLEEP =		20*20; //in 50msec units (20 seconds)


typedef enum {
	INIT,
	START_PLAYING,
	PLAYING,
	PAUSE,
	IDLE,
	GOTOSLEEP,
	EXITSLEEP,
	LOW_BAT
} program_state;

