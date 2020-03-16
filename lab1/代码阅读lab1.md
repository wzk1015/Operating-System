# Lab1代码阅读

wzk

## 文件树

```
├── boot
│   ├── Makefile
│   ├── start.o
│   └── start.S
├── drivers
│   ├── gxconsole
│   │   ├── console.c
│   │   ├── console.o
│   │   ├── dev_cons.h
│   │   └── Makefile
│   └── Makefile
├── gxemul
│   ├── elfinfo
│   ├── r3000
│   ├── r3000_test
│   ├── test
│   └── vmlinux
├── include
│   ├── asm
│   │   ├── asm.h
│   │   ├── cp0regdef.h
│   │   └── regdef.h
│   ├── asm-mips3k
│   │   ├── asm.h
│   │   ├── cp0regdef.h
│   │   └── regdef.h
│   ├── env.h
│   ├── error.h
│   ├── kclock.h
│   ├── mmu.h
│   ├── pmap.h
│   ├── printf.h
│   ├── print.h
│   ├── queue.h
│   ├── sched.h
│   ├── stackframe.h
│   ├── trap.h
│   └── types.h
├── include.mk
├── init
│   ├── init.c
│   ├── init.o
│   ├── main.c
│   ├── main.o
│   └── Makefile
├── lib
│   ├── Makefile
│   ├── print.c
│   ├── printf.c
│   ├── printf.o
│   └── print.o
├── Makefile
├── readelf
│   ├── kerelf.h
│   ├── main.c
│   ├── main.o
│   ├── Makefile
│   ├── readelf
│   ├── readelf.c
│   ├── readelf.o
│   ├── testELF
│   └── types.h
└── tools
    └── scse0_3.lds
```



## MakeFile

文件开头定义了模块modules（boot、drivers、init、lib等目录）以及对应的.o文件objects

首先对每个子文件夹（模块）执行make，然后使用linker script将所有.o文件链接起来生成vmlinux内核。

Clean：进入每个子目录调用make clean，并删去所有.o文件以及vmlinux文件



## include.mk

定义了交叉编译器gcc的路径和一些宏



## readelf

**types.h**：定义了数据类型（u_int8_t等）和一些运算（最小值、rounding、offset、static_assert）

**kerelf.h**：首先定义了Elf32_word等数据类型，然后定义了Elf32_Ehdr（ELF头）、Elf32_Shdr（section header）、Elf32_Phdr（program header）的结构、segment type的宏定义（pt_null等）

**readelf.c**：首先判断是不是ELF文件（检查幻数），然后根据大小端（lab1-extra）输出各个segment的序号、文件大小、空间大小（作业）

**main.c**：接受文件名作为参数，读取文件调用readelf函数

**Makefile**：交叉编译main.c readelf.c生成main.o和readelf.o，最后生成可执行文件readelf；clean清除.o文件和readelf



## tools

**scse0_3.lds**：即Linker Script，设定MIPS结构，设定程序入口为_start，设定.text、.data、.bss的地址（作业）



## boot

**start.S**：引用regdef.h、cp0regdef.h、asm.h三个头文件，定义了内核栈空间的地址，调用Leaf(\_start)函数，用.set设定汇编器，关闭中断，关闭监视异常，关闭内核态缓存，设定sp寄存器栈地址，跳转到main函数（作业），调用End(\_start)

**Makefile**：交叉编译start.S，clean清除start.o



## lib

**printf.c**：printf函数将接受的输出参数传递给print.c里的lp_Print函数，后者传递输出至myoutput；myoutput里调用printcharc（在gxconsole.c）；va_list，va_start，va_end用于接受可变个数参数，panic用于测试

**print.c**：扫描字符串，识别%及标识符时按照需要打印（作业）。其中用到了PrintChar、PrintNum、PrintString函数确定输出个数和缓冲区内容。

**Makefile**：交叉编译print.c printf.c，clean清除.o文件



## init

**main.c**：include pmap.h和printf.h。main函数调用printf函数输出，调用init.c中的mips_init()，出错时调用panic函数输出

**init.c**：include asm.h pmap.h env.h printf.h kclock.h trap.h。mips_init函数打印，调用FTEST、ENV_CREATE(PTEST)，输出”\^\^\^\^\^“

**Makefile**：交叉编译init.c main.c，clean清除.o文件



## gxemul

gexmul硬件模拟器组件及生成的vmlinux内核文件



## drivers

**gxconsole/console.c**：printcharc函数将待打印的字符放在PUTCHAR_ADDRESS，即可完成字符输出；printstr函数循环调用printcharc输出字符串；halt函数将HALT_ADDRESS地址的值设为0从而暂停

**gxconsole/dec_cons.h**：定义了gxemul模拟器的各个地址，用来计算PUTCHAR_ADDRESS等

**gxconsole/Makefile**：交叉编译console.o，clean清除.o文件

**Makefile**：进入gxconsole文件夹执行make或clean



## include

**asm/asm.h**：汇编器宏，增加可读性，包括LEAF（定义了不调用其他函数的叶子函数）、NESTED（声明嵌套路径）、END（定义函数尾部）、EXPORT（标签）、FEXPORT（函数标签）

**asm/regdef.h**：定义了32个寄存器的宏，s0、t1、sp等

**asm/cp0regdef.h**：定义了cp0的30个寄存器的宏

**env.h**：定义了创造环境、环境状态有关的宏和环境结构，包括一些Lab4、Lab6需要的内容

**error.h**：定义了一些异常的宏

**kclock.h**：定义时钟端口

**mmu.h**：先定义了MIPS概念（一页的字节数、虚拟地址的虚页号部分、页表标识），注释中表明了MIPS内存空间，然后是一些宏（内核栈顶、内核栈大小等）、帮助函数（实地址到虚地址的转换、断言等）

**pmap.h**：定义了页的结构、页 页号 虚拟地址物理地址的转换，声明了很多页相关的函数（以后完成？）

**printf.h**：定义panic函数（就是把stdargs标准库中文件、行这些参数传入_panic函数）

**print.h**：定义了printf的最大长度，声明了lp_Print函数（实体在print.c）

**queue.h**：定义了列表、尾队列、循环队列三种数据结构

**sched.h**：声明了几个sched（时间表？）有关的函数

**stackframe.h**：定义了栈帧的一些宏，用来操作sp栈指针

**trap.h**：定义了trap（陷入）的相关宏，如除零错误、断点、溢出、非法opcode、pagefault、系统调用，以及Trapframe初始化、Trapframe寄存器等

**types.h**：与readelf目录下的types.h一致，定义了数据类型（u_int8_t等）和一些运算（最小值、rounding、offset、static_assert）