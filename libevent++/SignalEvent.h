/*
 * SignalEvent.h
 *
 *  Created on: 2015Äê10ÔÂ15ÈÕ
 *      Author: wenge
 */

#ifndef SIGNALEVENT_H_
#define SIGNALEVENT_H_

#include "Event.h"
#include "Constants.h"

namespace libevent_cpp{

class SignalEvent :public Event{
public:
	SignalEvent(const EventBase& base, int signum,
			EventCallback cb, void* arg):
				Event(base, signum, EV_SIGNAL|EV_PERSIST, cb, arg){

	}

};

}



#endif /* SIGNALEVENT_H_ */
