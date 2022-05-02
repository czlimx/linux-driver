#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static int fd;

static void sig_handler(int sig)
{
	int ret;
	char array[52] = {0};
	
	ret = read(fd, array, 52);
	if (ret < 0){
		printf("read failure\n");
		return ;
	}

	printf("read data:%s\n", array);
}


// ./xxx dev/xxx0
int main(int argc, char **argv)
{
	int oflags;

	if (argc != 2)
		return -1;
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0){
		printf("open %s failure\n", argv[1]);
		return -1;
	}

	signal(SIGIO, sig_handler);

	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	while(1){
		sleep(1000);
	}

	close(fd);

	return 0;
}
