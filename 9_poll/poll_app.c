#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

// ./xxx dev/xxx0
int main(int argc, char **argv)
{
	char array[52] = {0};
	int fd, ret;
	struct pollfd fds;

	if (argc != 2)
		return -1;
	
	fd = open(argv[1], O_RDWR | O_NONBLOCK);
	if (fd < 0){
		printf("open %s failure\n", argv[1]);
		return -1;
	}

	fds.fd = fd;
	fds.events = POLLIN;

	while(1){

		ret = poll(&fds, 1, 1000);
		if (ret < 0)
			printf("poll error\n");
		else if (ret == 0)
			printf("poll timeout\n");
		else {
			
			ret = read(fd, array, 52);
			if (ret < 0){
				printf("read %s failure\n", argv[1]);
				return -1;
			}

			printf("read data:%s\n", array);
		}
		
	}

	close(fd);

	return 0;
}
