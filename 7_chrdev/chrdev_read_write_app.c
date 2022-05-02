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

	if (argc != 3)
		return -1;
	
	fd = open(argv[1], O_RDWR);
	if (fd < 0){
		printf("open %s failure\n", argv[1]);
		return -1;
	}

	ret = write(fd, argv[2], strlen(argv[2]));
	if (ret < 0){
		printf("write %s failure\n", argv[1]);
		return -1;
	}

	ret = read(fd, array, strlen(argv[2]));
	if (ret < 0){
		printf("read %s failure\n", argv[1]);
		return -1;
	}

	printf("read data:%s\n", array);

	close(fd);

	return 0;
}
