# lab1实验报告

18231047 王肇凯



## 思考题

### Thinking 1.1

因为内核文件是big endian存储的，而我们的readelf程序读取的是little endian文件，故不能解析。

### Thinking 1.2

内核入口在start.S文件。

main函数在`init/main.c`。

内核进入main函数是通过在linker script链接时指定entry point，然后在入口start.S中调用jal main

跨文件调用函数是通过交叉编译并链接start.o，main.o……文件实现的。



## 实验难点图示

**vmlinux启动过程**

```mermaid
graph LR
	A(交叉编译) --> B(链接, 指定代码段 数据段 内核入口) --> C(start.o中初始化堆栈等, 跳转至main函数)
```

**printf函数**

``` mermaid
graph LR
	A(识别'%',否则加入缓冲区) --> B(输出此前的序列,清空缓存区) --> C(检查ladjust,padc,width,prec)
	
```

```mermaid
graph LR
D(检查标识符,negFlag,longFlag) --> E(调用PrintNum等返回length) --> F(调用OUTPUT输出)
```



## 体会与感想

lab1整体来说难度也不高，Boot部分主要是结合理论知识理解操作系统的启动过程，以阅读代码为主，填写部分较为基础。printf部分则是实现对于标识符的识别和处理，也是printf函数的核心，难度稍高，不过理解已提供的相关函数后也能够很快完成。

感觉C语言的指针知识有些遗忘，对于完成c程序有一些影响，需要复习。而且vim的界面也是十分难受，printf时我将代码复制到本地用CLion编写，感觉清爽多了。

## 指导书反馈

指针的理解有些困难（尤其是数据类型比较复杂时，如自定义的ELF32），希望在解读代码时对于相关部分稍微多解释一些；

希望对于Exercise可以适当提示一下（比如printf中的注释就非常有帮助）。

## 残留难点

ELF还是一知半解；

MIPS汇编程序中的很多伪指令不太理解；

内核的很多代码都没有阅读，阅读过的也没有完全理解（不知道后续实验是否会逐步解析？）

vim如何调试c程序？在运行时如何进行输入?（scanf?）

