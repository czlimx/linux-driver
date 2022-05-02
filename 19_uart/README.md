## 测试

### 1 fasync案例

测试结果：
```
/sunny # insmod fasync.ko
/sunny # ./app /dev/xxx0 &
/sunny # echo 12356 > /dev/xxx0
read data:12356
/sunny # top
Mem: 21768K used, 485112K free, 0K shrd, 0K buff, 2812K cached
CPU:  0.0% usr  0.0% sys  0.0% nic  100% idle  0.0% io  0.0% irq  0.0% sirq
Load average: 0.00 0.00 0.00 1/42 159
  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND
    1     0 0        S     2656  0.5   0  0.0 init
   83     1 0        S     2656  0.5   0  0.0 -/bin/sh
  159    83 0        R     2656  0.5   0  0.0 top
  156    83 0        S     1380  0.2   0  0.0 ./app /dev/xxx0
...

/sunny # kill -9 156
[1]+  Killed                     ./app /dev/xxx0
/sunny # rmmod fasync
```

- 当你重复以上实验时请注意以下为变量：(不同内核栈不相同，故作为全局变量)
```
static char array[52];
static struct fasync_struct *async_queue;
```