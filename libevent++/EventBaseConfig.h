/*
 * EventBaseConfig.h
 *
 *  Created on: 2015Äê10ÔÂ14ÈÕ
 *      Author: wenge
 */

#ifndef EVENTBASECONFIG_H_
#define EVENTBASECONFIG_H_

#include "Log.h"
#include <stddef.h>

namespace libevent_cpp{

class EventBaseConfig{
public:
	EventBaseConfig(){
		config_ = event_config_new();
		if (config_ == NULL){
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "event base config new fail");
		}
	}

	~EventBaseConfig(){
		event_config_free(config_);
	}

	const struct event_config* getConfig() const{
		return config_;
	}
private:
	struct event_config* config_;
};

}


#endif /* EVENTBASECONFIG_H_ */
