#include <sys/time.h>
#include <ncurses.h>

#include <tetris.h>

#define TIMEVAL_USEC(tv) ((suseconds_t)((tv.tv_sec * (1000 * 1000)) + tv.tv_usec))

static struct timeval now;
static struct timeval last_exec_time;
void update_last_exec_time() {
	gettimeofday(&last_exec_time, NULL);
}

int hasToUpdate() {
	gettimeofday(&now, NULL);
	return timer < (TIMEVAL_USEC(now) - TIMEVAL_USEC(last_exec_time));
}

void set_timeout(int time) {
	timeout(time);
}
