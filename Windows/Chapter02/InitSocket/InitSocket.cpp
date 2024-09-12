#include "..\..\Common.h"
#include <iostream>

int main(int argc, char *argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(514, &wsa) != 0)
		return 1;
	printf("[알림] 윈속 초기화 성공\n");

	std::cout << "wVersion: " << wsa.wVersion << std::endl;
	std::cout << "wHighVersion: " << wsa.wHighVersion << std::endl;
	std::cout << "szDescription: " << wsa.szDescription << std::endl;
	std::cout << "szSystemStatus: " << wsa.szSystemStatus << std::endl;

	// 소켓 생성
	SOCKET sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[알림] 소켓 생성 성공\n");

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}
