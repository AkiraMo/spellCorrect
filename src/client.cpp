#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"unistd.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"arpa/inet.h"
#include"netinet/in.h"
#include"errno.h"

#include <iostream>

using std::cout;
using std::endl;
int main()
{
	int fd=socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	inet_aton("192.168.44.128", &addr.sin_addr);
	connect(fd,(struct sockaddr *)&addr,sizeof(addr));
	char sen[1024];
	while(1)
	{
	
//		memset(sen,0,sizeof(sen));
//		recv(fd,sen, sizeof(sen), 0);
//		cout << "recv:" << sen;

		memset(sen, 0 ,sizeof(sen));
		read(STDIN_FILENO, sen, sizeof(sen));
		send(fd, sen, strlen(sen), 0);
		memset(sen,0,sizeof(sen));
		recv(fd,sen, sizeof(sen), 0);
		cout << endl << "recv:" << endl << sen << endl;

	}
	
}
