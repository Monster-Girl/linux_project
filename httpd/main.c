#include"httpd.h"
#include<pthread.h>

static void* usage(const char* proc)
{
	printf("%s [local_ip][loacl_port]",proc);
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		usage(argv[0]);
		exit(1);
	}

	int listen_sock=startup(argv[1],atoi(argv[2]));
	while(1)
	{
		struct sockaddr_in client;
		socklen_t len=sizeof(client);
		int new_fd=accept(listen_sock,(struct sockaddr*)&client,&len);
		if(new_fd<0)
		{
			print_log(strerror(errno),NOTICE);
			continue;
		}

		printf("get client[%s:%d]\n",inet_ntoa(client.sin_addr),\
				ntohs(client.sin_port));

		pthread_t id; 
		int ret=pthread_create(&id,NULL,handler_request,(void*)new_fd);
		if(ret!=0)
		{
			print_log(strerror(errno),FATAL);
			close(new_fd);
		}
		else
		{
			pthread_detach(id);
		}
	}
	close(listen_sock);
	return 0;
}
