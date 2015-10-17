/*
 * Constants.h
 *
 *  Created on: 2015Äê10ÔÂ15ÈÕ
 *      Author: wenge
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace libevent_cpp{

const int EVLOOP_ONCE = 0x01;
const int EVLOOP_NONBLOCK = 0x02;
const int EVLOOP_NO_EXIT_ON_EMPTY = 0x04;

const int EV_TIMEOUT = 0x01;
const int EV_READ = 0x02;
const int EV_WRITE = 0x04;
const int EV_SIGNAL = 0x08;
const int EV_PERSIST = 0x10;
const int EV_ET = 0x20;

}
#endif /* CONSTANTS_H_ */
