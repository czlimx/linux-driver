## 测试

### 1 chrdev案例

测试结果：
```
/sunny # insmod chrdev.ko
[ 8142.493498] xxx_init
/sunny # cat /proc/devices
Character devices:
...
247 xxx
...
/sunny # mknod /dev/xxx c 247 0
/sunny # ls /dev/xxx -l
crw-r--r--    1 0        0         247,   0 Jan  1 02:17 /dev/xxx
/sunny # echo 0 > /dev/xxx
[ 8306.189049] xxx_open
[ 8306.191562] xxx_write
[ 8306.193870] xxx_release
/sunny # rmmod chrdev
[ 8329.021150] xxx_exit
```

### 2 chrdev_mknod案例
测试结果：
```
/sunny # insmod chrdev_mknod.ko
[ 9006.588703] xxx_init
/sunny # ls /dev/xxx0 -l
crw-rw----    1 0        0         247,   0 Jan  1 02:30 /dev/xxx0
/sunny # cat /sys/class/my_class/xxx0/dev
247:0
/sunny # echo 0 > /dev/xxx0
[ 9064.720260] xxx_open
[ 9064.722641] xxx_write
[ 9064.724941] xxx_release
/sunny # rmmod chrdev_mknod
[ 9081.732904] xxx_exit
```

### 3 chrdev_read_write案例
测试结果：
```
/sunny # insmod chrdev_read_write.ko
[10961.911674] xxx_init
/sunny # ./chrdev_read_write_app /dev/xxx0 hello
[10983.336638] xxx_open
[10983.338889] write data :hello
read data:hello
[10983.342627] xxx_release
/sunny # rmmod chrdev_read_write
[11025.556962] xxx_exit
```
