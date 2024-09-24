#include "..\..\Common.h"

#define TESTNAME "www.google.com"

// ������ �̸� -> IPv4 �ּ�
bool GetIPAddr(const char *name, struct in_addr *addr)
{
	struct hostent *ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return false;
	}
	if (ptr->h_addrtype != AF_INET)
		return false;
	memcpy(addr, ptr->h_addr, ptr->h_length);
	return true;
}

// ������ �̸� -> IPv4 �ּ�
bool GetIPInfo(const char* name, struct in_addr* addr)
{
	struct addrinfo * res;
	int status = getaddrinfo(name, "http", NULL, &res);
	if (status != 0) {
		err_display("getaddrinfo()");
		return false;
	}
	if (res->ai_family != AF_INET)
		return false;
	struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
	*addr = ipv4->sin_addr;
	freeaddrinfo(res);
	return true;
}

// IPv4 �ּ� -> ������ �̸�
bool GetDomainName(struct in_addr addr, char *name, int namelen)
{
	struct hostent *ptr = gethostbyaddr((const char *)&addr,
		sizeof(addr), AF_INET);
	if (ptr == NULL) {
		err_display("gethostbyaddr()");
		return false;
	}
	if (ptr->h_addrtype != AF_INET)
		return false;
	strncpy(name, ptr->h_name, namelen);
	return true;
}

// IPv4 �ּ� -> ������ �̸�
bool GetDomainInfo(struct in_addr addr, char* name, int namelen)
{
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_addr = addr;
	sa.sin_family = AF_INET;
	int status = getnameinfo((sockaddr *)&sa, sizeof(sa), name, namelen, NULL, 0, 0);
	if (status != 0) {
		err_display("getnameinfo()");
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	printf("������ �̸�(��ȯ ��) = %s\n", TESTNAME);

	// ������ �̸� -> IP �ּ�
	struct in_addr addr;
	if (GetIPInfo(TESTNAME, &addr)) {
		// �����̸� ��� ���
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		printf("IP �ּ�(��ȯ ��) = %s\n", str);

		// IP �ּ� -> ������ �̸�
		char name[256];
		if (GetDomainInfo(addr, name, sizeof(name))) {
			// �����̸� ��� ���
			printf("������ �̸�(�ٽ� ��ȯ ��) = %s\n", name);
		}
	}

	// ���� ����
	WSACleanup();
	return 0;
}
