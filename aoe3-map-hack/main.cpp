
#include "stdio.h";

#include "../aoe3-map-hack-common/socketclient.h"
#include "Windows.h";
#include "../aoe3-map-hack-common/injector.h"

void dejectPrevious()
{
	SocketClient socketClient = SocketClient();
	printf("attempting to deject\n");
	socketClient.clientConnect("127.0.0.1", "6666");
	socketClient.clientSend("deject\r\n");
	socketClient.clientClose();
}

int main(int argc, char* argv[]) {
	dejectPrevious();

	if (!injectDll(argv[1], "age3y.exe")) {
		return 1;
	}

	printf("connecting to dll, input q to exit\n");

	SocketClient socketClient = SocketClient();
	if (socketClient.clientConnect("127.0.0.1", "6666"))
		printf("connected successfully\n");
	else {
		printf("connection failure\n");
		return 1;
	}

	char inputBuffer[256];

	while (scanf("%s", inputBuffer)) {
		if (strcmp(inputBuffer, "q") == 0) break;
		socketClient.clientSend(strcat(inputBuffer, "\r\n"));
	}

	socketClient.clientSend("deject\r\n");
	socketClient.clientClose();

	return 0;
}


