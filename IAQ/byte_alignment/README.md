# 字节对齐
不同硬件平台对存储空间的处理是不同的。 一些平台对某些特定类型的数据只能从某些特定地址开始存取。 某些架构的CPU在访问一个没有进行对齐的变量的时候会发生错误。

常见的如果不按照适合其平台要求对数据存放进行对齐， 会在存取效率上带来损失。 如有些平台每次读都是从偶数地址开始， 如果在32位CPU中一个int型存放在偶地址开始的地方， 那么一个读周期就可以读出32bit， 而如果存放在奇数地址， 就需要读取两个周期， 并进行拼凑才能得到数据， 导致数据读取效率变差。

## 基本规则
结构体成员对齐规则: 以成员类型所占字节数对齐

有效对齐值：
- 每个成员自然边界与系统对齐值中的最小值

结构体整体对齐规则:
- 为结构体成员自然边界值的最大值与系统对齐值**两者的最小值**

> 结构体大小为结构体对齐值的整数倍， 对于每个成员的存放地址，以上一个成员地址结尾处为起点，偏移地址为能被有效对齐值整除的地址。(整除即余数也为0)

如以下结构体:
```c
struct Struct6{
    char ch;
    int integer;
    short shorttype;
    char *point;
    double doubletype;
};

// 环境为x64 CPU
```

其真实地址结构如下:
---- 
|  |
---- 0x18 > doubletype
|  |
---- 0x10 > point
|  |
---- 0x08 > shorttype
|  | 
---- 0x04 > integer
|  |
---- 0x00 > ch

对齐大致如下:
[x] [x] [x] [x] [x] [x] [x] [x]   doubletype
[x] [x] [ ] [ ] [ ] [ ] [ ] [ ]   point 2byte
[x] [x] [x] [x] [x] [x] [x] [x]   shorttype & point 6byte
[x] [ ] [ ] [ ] [x] [x] [x] [x]   ch & integer


## 编译指令修改对齐规则


## 术语
- 机器字长： 即CPU一次能处理数据的位数。 也称系统对齐值。 
- 自然边界: 也称自身对齐值， 与自身数据类型大小的值一样
- 指定对齐值: 即修改后的机器字长
- 结构体整体对齐:
- 有效对齐值:

## 参考链接
https://blog.51cto.com/u_9291927/1790295
https://blog.csdn.net/cclethe/article/details/79659590
https://blog.csdn.net/piaoliangjinjin/article/details/82971746
https://www.pianshen.com/article/9169436305/