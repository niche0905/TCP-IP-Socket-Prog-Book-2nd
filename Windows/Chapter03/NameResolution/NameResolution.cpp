#include "..\..\Common.h"

#define TESTNAME "www.google.com"

// 도메인 이름 -> IPv4 주소
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

// 도메인 이름 -> IPv4 주소
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

// IPv4 주소 -> 도메인 이름
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

// IPv4 주소 -> 도메인 이름
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
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	printf("도메인 이름(변환 전) = %s\n", TESTNAME);

	// 도메인 이름 -> IP 주소
	struct in_addr addr;
	if (GetIPInfo(TESTNAME, &addr)) {
		// 성공이면 결과 출력
		char str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr, str, sizeof(str));
		printf("IP 주소(변환 후) = %s\n", str);

		// IP 주소 -> 도메인 이름
		char name[256];
		if (GetDomainInfo(addr, name, sizeof(name))) {
			// 성공이면 결과 출력
			printf("도메인 이름(다시 변환 후) = %s\n", name);
		}
	}

	// 윈속 종료
	WSACleanup();
	return 0;
}
