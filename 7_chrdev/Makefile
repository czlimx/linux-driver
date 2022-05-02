KERNEL_DIR := /home/czlimx/linux/linux-5.4/
PWD_DIR	:= $(shell pwd)

obj-m := chrdev.o chrdev_mknod.o chrdev_read_write.o

all:
	make -C $(KERNEL_DIR) M=$(PWD_DIR) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD_DIR) clean

copy:
	sudo cp *.ko ~/nfs/rootfs/sunny/
