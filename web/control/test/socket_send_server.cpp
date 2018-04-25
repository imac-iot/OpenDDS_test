/*
 * socket_server.cpp
 */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{	
	int server_sockfd;
	int client_sockfd;
	int len;
	int i;
	const int port = 9808;
	const int BUFSIZE = 1024;
	struct sockaddr_in my_addr;
	struct sockaddr_in remote_addr;
	char buf[BUFSIZE];
	memset(&my_addr ,0 ,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_addr.s_addr=INADDR_ANY;
	my_addr.sin_port=htons(port);
	std::cout << "port " << port << std::endl;
	server_sockfd = socket(PF_INET ,SOCK_STREAM ,0);
	if( server_sockfd < 0)
	{
		std::cout << "socket err" << std::endl;
		return 1;
	}
	if(bind(server_sockfd,(struct sockaddr *)&my_addr ,sizeof(struct sockaddr)) < 0)
	{
		std::cout << "bind err" << std::endl;
		return 1;	
	}
	if(listen(server_sockfd ,5) <0)
	{
		std::cout << "listen err" << std::endl;
		return 1;	
	}
	socklen_t sin_size;
	sin_size = sizeof(struct sockaddr_in);
	if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr, &sin_size))<0)
	{
		std::cout << "listen err" << std::endl;
		return 1;	
	}
	std::cout <<"accept client " <<  inet_ntoa(remote_addr.sin_addr) << std::endl;
	std::string s;
	while(1)
	{
		//std::cin >> s;
		//std::cout << s << std::endl;
		s = "test";
		strcpy(buf,s.c_str());
		if(strcmp(buf,"exit")==0)
		{
			send(client_sockfd,buf,s.length(),0);
			break;
		}
		else
		{
			send(client_sockfd,buf,s.length(),0);
		}
		memset(&buf, 0, BUFSIZE);
		if(read(client_sockfd, buf, BUFSIZE))
		{
			std::cout << "read datai " << buf << std::endl;
			memset(&buf, 0, BUFSIZE);
		}
		sleep(2);

	}
	close(client_sockfd);
	close(server_sockfd);
	return 0;
}
