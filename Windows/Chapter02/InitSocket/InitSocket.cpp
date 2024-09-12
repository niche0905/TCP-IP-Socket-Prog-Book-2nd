#include "..\..\Common.h"
#include <iostream>

WORD myMakeWord(int frontVer, int backVer)
{
	return (backVer << 8) + frontVer;

}

int main(int argc, char *argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	MAKEWORD(2, 2);
	if (WSAStartup(1, &wsa) != 0)
		return 1;
	WSACleanup();

	printf("[알림] 윈속 초기화를 위한 상위 버전 확인\n");
	std::cout << "wVersion: " << (int)LOBYTE(wsa.wVersion) << "." << (int)HIBYTE(wsa.wVersion) << std::endl;
	std::cout << "wHighVersion: " << (int)LOBYTE(wsa.wHighVersion) << "." << (int)HIBYTE(wsa.wHighVersion) << std::endl;

	std::cout << std::endl << std::endl;
	if (WSAStartup(myMakeWord(LOBYTE(wsa.wHighVersion), HIBYTE(wsa.wHighVersion)), &wsa) != 0)
		return 1;
	WSACleanup();
	printf("[알림] 상위 버전을 사용해서 윈속 초기화 성공\n");

	std::cout << "wVersion: " << (int)LOBYTE(wsa.wVersion) << "." << (int)HIBYTE(wsa.wVersion) << std::endl;
	std::cout << "wHighVersion: " << (int)LOBYTE(wsa.wHighVersion) << "." << (int)HIBYTE(wsa.wHighVersion) << std::endl;
	std::cout << "szDescription: " << wsa.szDescription << std::endl;
	std::cout << "szSystemStatus: " << wsa.szSystemStatus << std::endl;

	WSACleanup();
	return 0;
}
