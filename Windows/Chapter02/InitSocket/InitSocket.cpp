#include "..\..\Common.h"
#include <iostream>

int main(int argc, char *argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(514, &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	std::cout << "wVersion: " << wsa.wVersion << std::endl;
	std::cout << "wHighVersion: " << wsa.wHighVersion << std::endl;
	std::cout << "szDescription: " << wsa.szDescription << std::endl;
	std::cout << "szSystemStatus: " << wsa.szSystemStatus << std::endl;

	// ���� ����
	SOCKET sock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[�˸�] ���� ���� ����\n");

	// ���� �ݱ�
	closesocket(sock);

	// ���� ����
	WSACleanup();
	return 0;
}
