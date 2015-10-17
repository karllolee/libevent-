/*
 * TimerEvent.h
 *
 *  Created on: 2015Äê10ÔÂ15ÈÕ
 *      Author: wenge
 */

#ifndef TIMEREVENT_H_
#define TIMEREVENT_H_

#include "Event.h"
#include "Constants.h"

namespace libevent_cpp{

class TimerEvent : public Event{
	public:
	TimerEvent(const EventBase& base,EventCallback cb, void* arg):
		Event(base, -1, 0, cb, arg){

	}
};

}


#endif /* TIMEREVENT_H_ */
