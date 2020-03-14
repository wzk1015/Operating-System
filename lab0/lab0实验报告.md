## 一、思考题

### 思考0.1 

CLI Shell优势：效率较高；使用资源较少；方便进行批处理任务。

CLI Shell劣势：不够直观；学习难度较高。

GUI Shell优势：直观；易于非技术人员学习。

GUI Shell劣势：效率低；资源消耗大；难以批量执行任务。



### 思考0.2

command文件：

<img src="C:\Users\ThinkPad\AppData\Roaming\Typora\typora-user-images\image-20200302152135658.png" alt="image-20200302152135658" style="zoom:67%;" />

result文件：

<img src="C:\Users\ThinkPad\AppData\Roaming\Typora\typora-user-images\image-20200302153755821.png" alt="image-20200302153755821" style="zoom:67%;" />

说明：command文件将test中的第一行通过'>'重定向到test文件，此后每一行通过'>>'追加在test文件后；result文件则是执行test文件中每一行的命令后的结果（将echo后面的字符串输入进result，再分别将file1~3的内容追加至file4，最后将file4的内容追加到result)

echo echo Shell Start 与  echo 'echo Shell Start' 效果一致；

echo echo \\\$c>file1 与 echo 'echo \\\$c>file1' 效果不同，前者是将'echo \$c'重定向到file1中，后者是将‘echo \$c>file1’输出到控制台。

### 思考题0.3

add the file: 		git add

stage the file: 	 git add

commit:			   git commit

### 思考题0.4

1、git checkout --printf.c 撤销还没加入暂存区的修改

2、git reset HEAD printf.c 放弃暂存区修改，然后git checkout（同1）

3、git reset --hard HEAD^ 将仓库回退到前一个版本，然后git reset HEAD清除暂存区修改

### 思考题0.5 

1、只克隆了master分支；错误，没有检出分支，需要使用git checkout检出分支

2、正确，上述操作均为本地仓库、暂存区的修改

3、正确，默认克隆远程库HEAD分支

4、正确，克隆后工作区处于master分支

## 实验难点图示

难点主要在于Makefile文件编写、git知识。

Makefile图示：

```mermaid
graph LR
	A(编写fibo.c) --> B(gcc -c生成.o文件) --> C(gcc -o 链接多个.o文件生成可执行文件)
```

git图示：

![git stream](http://misaka-oss.oss-cn-beijing.aliyuncs.com/cs/oo_assistant_files/git-guide/git-structure.png)

## 体会与感想

本次实验主要学习了linux的基础命令，gcc、vim、git的操作，shell脚本和Makefile文件的编写。整体来说学习难度不高，一整天时间基本可以完成。不过只是起步阶段，后期自己搭建OS时恐怕任务量会很重，因此现在需要先将基础知识学好。

## 指导书反馈

建议可以在**附录**中提供一些**速查表**，如shell命令(多罗列一些可能用到的参数)、git命令、vim操作等，附在指导书最后方便查阅，不然使用时要花一段时间从指导书/网上找到对应资源。

一些没有提到或可以补充的：

- git reflog；
- git reset --hard不必输入完整哈希值（前几位即可）；

## 残留难点

- git撤销的几个指令练习不多还不太会用；

- git merge没有讲到（也可能是不太需要）
- tmux练习不多不太会使用
- gxemul没有过多练习（可能是后序会讲？）

