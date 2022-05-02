## 测试

### 1 semaphore案例

测试结果：
```
/sunny # insmod semaphore.ko
[ 5021.117077] xxx_init
[ 5021.119296] down interrupt:0
[ 5021.122310] try get lock:0
/sunny # rmmod semaphore
[ 5031.984354] xxx_exit
```