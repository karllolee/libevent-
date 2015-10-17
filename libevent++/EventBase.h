/*
 * EventBase.h
 *
 *  Created on: 2015Äê10ÔÂ14ÈÕ
 *      Author: wenge
 */

#ifndef EVENTBASE_H_
#define EVENTBASE_H_

#include "Log.h"

#include<event2/event.h>
#include<stdlib.h>

namespace libevent_cpp{

class EventBase{
public:

	EventBase(){
		evbase_ = event_base_new();
		if (evbase_ == NULL){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base new fail");
		}
	}

	EventBase(const EventBaseConfig& config){
		evbase_ = event_base_new_with_config(config.getConfig());
		if (evbase_ == NULL){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base new fail");
		}
	}

	~EventBase(){
		event_base_free(evbase_);
	}

	void loop(int flags){
		if (event_base_loop(evbase_, flags) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base loop fail");
		}
	}

	void dispatch(){
		if (event_base_dispatch(evbase_) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base dispatch fail");
		}
	}

	void loopExit(const struct timeval *tv){
		if (event_base_loopexit(evbase_, tv) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base loop exit fail");
		}
	}

	void loopBreak(){
		if (event_base_loopbreak(evbase_) != 0){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base loop break fail");
		}
	}

	struct event_base* getEventBase() const{
		return evbase_;
	}

private:
	struct event_base* evbase_;
};

}



#endif /* EVENTBASE_H_ */
