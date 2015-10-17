/*
 * Socket.h
 *
 *  Created on: 2015Äê10ÔÂ13ÈÕ
 *      Author: wenge
 */

#ifndef SOCKET_H_
#define SOCKET_H_

#include "Logger.h"

#include<unistd.h>
#include<fcntl.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#include<stdlib.h>

namespace libevent_cpp{

class Socket{
public:
	Socket():fd_(-1){
	}
	explicit Socket(int fd):fd_(fd){
	}

	void create(){
		if((fd_ = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "create socket fail");
	}

	void bind(short port){
		struct sockaddr_in addr;
		::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
		addr.sin_port = ::htons(port);

		if (::bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "bind port fail");
	}

	void listen(int backlog = 128){
		if (::listen(fd_, backlog) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "listen fail");
	}

	void connect(const char* ip, short port){
		struct sockaddr_in addr;
		::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = ::inet_addr(ip);
		addr.sin_port = ::htons(port);
		if (::connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "connect fail");
	}

	Socket accept(){
		struct sockaddr_in addr;
		int len = sizeof(addr);
		int f = ::accept(fd_, (struct sockaddr*)&addr, &len);
		if (f < 0)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "accept fail");
		return Socket(f);
	}

	int read(char* buffer, int count){
		ssize_t nread, total = 0;
		while(total != count){
			nread = ::read(fd_, buffer, count - total);
			if (nread == 0)
				return total;
			if (nread == -1)
				return -1;
			total += nread;
			buffer += nread;
		}

		return total;
	}

	int write(char* buffer, int count){
		ssize_t nwrite, total = 0;
		while(total != count){
			nwrite = ::write(fd_, buffer, count - total);
			if (nwrite == 0)
				return total;
			if (nwrite == -1)
				return -1;
			total += nwrite;
			buffer += nwrite;
		}
		return total;
	}

	void close(){
		::close(fd_);
	}

	int getFd() const {
		return fd_;
	}

	void setTcpNoDelay(){
		int val = 1;
		if (::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set tcp no delay fail");
	}

	void setReusedAddress(){
		int val = 1;
		if (::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set reused address");
	}

	void setKeepAlive(){
		int val = 1;
		if (::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &val, sizeof(val)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set keep alive fail");

	}

	void setNonBlock(){
		int flag;
		if ((flag = ::fcntl(fd_, F_GETFL)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set non block fail");
		flag |= O_NONBLOCK;
		if (::fcntl(fd_, F_SETFL, flag) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set non block fail");
	}

	void setCloseOnExec(){
		int flag;
		if ((flag = ::fcntl(fd_, F_GETFL)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set non block fail");
		flag |= FD_CLOEXEC;
		if (::fcntl(fd_, F_SETFL, flag) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set non block fail");
	}

	void setSendTimeout(struct timeval tv){
		if (::setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set send timeout fail");
	}

	void setRecvTimeout(struct timeval tv){
		if (::setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set recv timeout fail");
	}

	void setSendBuffer(int size){
		if (::setsockopt(fd_, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set send buffer size fail");
	}

	void setRecvBuffer(int size){
		if (::setsockopt(fd_, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) == -1)
			LoggerSingleton::getLogger()->LOG_FATAL("%s", "set recv buffer size fail");
	}

private:
	Socket(const Socket&);
	Socket& operator=(const Socket&);
private:
	int fd_;
};

}



#endif /* SOCKET_H_ */
