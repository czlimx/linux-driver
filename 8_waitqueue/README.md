## 测试

### 1 wait_queue案例

测试结果：
```
/sunny # insmod wait_queue.ko
[ 1436.420699] xxx_init
/sunny # ./app /dev/xxx0 &
/sunny # [ 1464.689635] xxx_open
current pid 170 
[ 1464.692743] pid: 170 goto sleep
/sunny # top
Mem: 21660K used, 485220K free, 0K shrd, 0K buff, 2740K cached
CPU:  0.0% usr  9.0% sys  0.0% nic 90.9% idle  0.0% io  0.0% irq  0.0% sirq
Load average: 0.00 0.00 0.00 1/42 171
  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND
    1     0 0        S     2656  0.5   0  0.0 init
  119     1 0        S     2656  0.5   0  0.0 -/bin/sh
  171   119 0        R     2656  0.5   0  0.0 top
  170   119 0        S     1380  0.2   0  0.0 ./app /dev/xxx0

/sunny # echo 12356 > /dev/xxx0
[ 1486.833462] xxx_open
[ 1486.835746] write data :12356
[ 1486.835746]
[ 1486.840231] pid: 170 wake up
[ 1486.843264] xxx_release
/sunny # [ 1486.846076] xxx_release
read data:12356

top
Mem: 21620K used, 485260K free, 0K shrd, 0K buff, 2740K cached
CPU:  0.0% usr  9.0% sys  0.0% nic 90.9% idle  0.0% io  0.0% irq  0.0% sirq
Load average: 0.00 0.00 0.00 1/41 172
  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND
    1     0 0        S     2656  0.5   0  0.0 init
  119     1 0        S     2656  0.5   0  0.0 -/bin/sh
  172   119 0        R     2656  0.5   0  0.0 top
...
[1]+  Done                       ./app /dev/xxx0

