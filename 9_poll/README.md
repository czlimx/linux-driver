## 测试

### 1 poll_app案例

测试结果：
```
/sunny # insmod poll.ko
[  113.877357] poll: loading out-of-tree module taints kernel.
/sunny # ./poll_app /dev/xxx0 &
/sunny # poll timeout
poll timeout
/sunny # cd sunny/poll timeout
/sunny # echo 12356 > /dev/xxx0
[  128.431728] write arraysize :6
/sunny # [  128.435202] read arraysize :0
read data:12356

poll timeout
/sunny # insmod poll.kopoll timeout
/sunny # echo 12356 > /dev/xxx0 poll timeout

[  132.285423] write arraysize :6
/sunny # [  132.288756] read arraysize :0
read data:12356
```

### 2 select_app 案例
测试结果：
```
/sunny # ./select_app /dev/xxx0 &select timeout
/sunny # topselect timeout
/sunny # echo 12356 > /dev/xxx0 select timeout

[  334.529874] write arraysize :6
[  334.533140] read arraysize :0
read data:12356

/sunny # select timeout
select timeout
/sunny # ./select_app /dev/xxx0 &select timeout
/sunny # kill -9 88select timeout
/sunny # yopselect timeout
/sunny # echo 12356 > /dev/xxx0
[  340.356954] write arraysize :6
/sunny # [  340.360299] read arraysize :0
read data:12356

select timeout
select timeout
```

- 当你重复以上实验时请注意以下为变量：(不同内核栈不相同，故作为全局变量)
```
static atomic_t arraysize;
static char array[52];
static wait_queue_head_t head;
```