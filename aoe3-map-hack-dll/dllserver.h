#include "../aoe3-map-hack-common/socketserver.h"
#include <stdarg.h>

#ifndef DLLSERVER_H
#define DLLSERVER_H
SocketServer socketServer = SocketServer();

void loggingCallback(const char* format, ...) {
	// write to filesystem to debug, only worth using to debug the socket connection to the dll
}

void logFromBot(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[256];
	vsprintf(buffer, format, args);
	socketServer.socketSend(loggingCallback, buffer);
	va_end(args);
}

#endif DLLSERVER_H
