#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// ./xxx dev/xxx0 hello
int main(int argc, char **argv)
{
	char array[52] = {0};
	int fd, ret;

	if (argc != 2)
		return -1;
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0){
		printf("open %s failure\n", argv[1]);
		return -1;
	}

	printf("current pid %d \n", getpid());

	ret = read(fd, array, 52);
	if (ret < 0){
		printf("read %s failure\n", argv[1]);
		return -1;
	}

	printf("read data:%s\n", array);

	close(fd);

	return 0;
}
