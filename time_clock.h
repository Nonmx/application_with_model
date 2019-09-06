#ifndef TIME_H_
#define TIME_H_

typedef struct _tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
}tm;

time_t mktime(tm* timeptr);
tm* localtime(time_t* timer);

#endif /* TIME_H_ */