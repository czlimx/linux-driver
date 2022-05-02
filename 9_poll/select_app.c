#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

// ./xxx dev/xxx0
int main(int argc, char **argv)
{
	char array[52] = {0};
	int fd, ret;
	fd_set readfds;
	struct timeval timeout;

	if (argc != 2)
		return -1;
	
	fd = open(argv[1], O_RDWR | O_NONBLOCK);
	if (fd < 0){
		printf("open %s failure\n", argv[1]);
		return -1;
	}

	while(1){

		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
		if (ret < 0)
			printf("select error\n");
		else if (ret == 0)
			printf("select timeout\n");
		else {
			if (!FD_ISSET(fd, &readfds))
				break;
		
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
