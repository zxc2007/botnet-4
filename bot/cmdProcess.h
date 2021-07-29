#include<Windows.h>
#include<tchar.h>
#include<stdio.h>
#include<atlstr.h>

void cmdProcess(char* command) {

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	// Set cmd windows hide
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOWNORMAL;

	memset(&pi, 0, sizeof(pi));
	LPTSTR cmdPath = (LPTSTR) TEXT("C:\\Windows\\System32\\cmd.exe");
	LPTSTR cmdTest = (LPTSTR) TEXT("C:\\Windows\\System32\\cmd.exe /k ");
	char buff[512] = "";
	strcat(buff, "C:\\Windows\\System32\\cmd.exe /k ");
	strcat(buff, command);

	printf(buff);
	LPTSTR cmdArgs = (LPTSTR) buff;

	// Start the child process
	if (!CreateProcess(cmdPath, cmdArgs, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		printf("Create process failed (%d)!\n", GetLastError());
		return;
	}

	// Wait until child process exists
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

}