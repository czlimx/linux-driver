## 测试

### 1 atomic案例

测试结果：
```
/sunny # insmod atomic.ko
[ 3303.256532] xxx_init
[ 3303.258750] atomic value :10
[ 3303.261762] atomic value :13
[ 3303.264653] atomic value :8
[ 3303.267455] atomic value :9
[ 3303.270256] atomic value :8
/sunny # rmmod atomic
[ 3331.469447] xxx_exit
```