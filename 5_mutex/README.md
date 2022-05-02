## 测试

### 1 mutex案例

测试结果：
```
/sunny # insmod mutex.ko
[ 5547.883974] xxx_init
[ 5547.886193] mutex lock interruptible :0
[ 5547.890042] mutex trylock :failure
/sunny # rmmod mutex
[ 5554.468175] xxx_exit
```
