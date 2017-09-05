#include "serial.h"
void *routine(void *arg)
{
	int fd = (int)arg;

	char *msg = calloc(1, 1024);
	int n;
	while(1)
	{
		bzero(msg, 1024);
		n = read(fd, msg, 1024);
		if(n <= 0)
		{
			perror("read() failed");
			break;
		}
		fprintf(stderr, "RX:%s\n\n", msg);
	}
	free(msg);
}

int main(int argc, char *argv[])
{
	int fd = init_tty();
	
	// ============ 独立线程读取串口信息 ============== //
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)fd);
	//=============循环发送========================//
	char *buf = calloc(1,1024);
	while(1)
	{
		bzero(buf,sizeof(buf));
		usleep(5000);
		printf("TX:");
		fgets(buf,1024,stdin);
		//scanf("%s",buf);
		write(fd,buf,strlen(buf));
		
	}
	return 0;
	
}