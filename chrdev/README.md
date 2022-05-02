## 测试

### 1 hello案例

测试结果：
```
/sunny # insmod xxx.ko
[  184.959027] xxx_init
/sunny # rmmod xxx.ko
[  190.860104] xxx_exit
```

### 2 module_param案例
测试结果：
```
/sunny # rmmod hello.ko
[  348.672510] xxx_exit
/sunny # insmod module_param.ko sender="hello" base=10,20,30,40
[ 1112.297974] xxx_init
[ 1112.300193] base[0] :10
[ 1112.302757] base[1] :20
[ 1112.305213] base[2] :30
[ 1112.307665] base[3] :40
[ 1112.310118] sender :hello
```