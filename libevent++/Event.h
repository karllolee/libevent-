/*
 * Event.h
 *
 *  Created on: 2015Äê10ÔÂ15ÈÕ
 *      Author: wenge
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Log.h"
#include<event2/event.h>

namespace libevent_cpp{

typedef void(*EventCallback)(int, short, void*);

class Event{
public:
	Event(const EventBase& base, const Socket& socket,
			short what, EventCallback cb, void* arg){
		ev_ = event_new(base.getEventBase(), socket.getFd(), what, cb, arg);
		if (ev_ == NULL){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event new fail");
		}
	}
	~Event(){
		event_free(ev_);
	}
	void add(const struct timeval* tv){
		if (event_add(ev_, tv) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event add fail");
		}
	}

	void del(){
		if (event_del(ev_) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event delete fail");
		}
	}

	struct event* getEvent(){
		return ev_;
	}
protected:
	Event(const EventBase& base, int fd,
				short what, EventCallback cb, void* arg){
			ev_ = event_new(base.getEventBase(), fd, what, cb, arg);
			if (ev_ == NULL){
				LoggerSingleton::getLogger()->LOG_FATAL("%s", "event new fail");
			}
	}
private:
	struct event* ev_;
};

}


#endif /* EVENT_H_ */
