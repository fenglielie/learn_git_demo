# Git 学习笔记

省略了一些最基础的介绍，包括分布式和集中式版本控制的区别，以及Git的优势。





## Git 文件状态



这是在git中，文件的四种状态，

![](learn_git_images/git_lifecycle.png)





## Git 初始化设置

配置目录包括三级，越具体的配置优先级越高，

* 系统级配置，在安装目录；

* 用户级配置，在~/.gitconfig；
* 仓库级配置，在.git/config。

一般在用户级配置中，配置用户名和邮箱

```
git config --global user.name "fenglielie"
git config --global user.email fenglielie@qq.com
```

注意，在提交到Github后，只会关注emali，不会关注前面的名称，因此可以用fenglielie(local),fenglielie(tc),fenglielie区分我的不同的提交来源（机器）。



提交信息的文本编辑器，建议使用vim

```
git config --global core.editor vim
```

默认的主分支名称，为了和GitHub一致，使用main

```
git config --global init.defaultbranch main
```



查看配置，重复可能是多级配置文件中的重复项。

```
git config --list
```



## 建立仓库，与远程仓库对应

建立本地仓库

```
git init
git add *
git commit -m "init this project"
```



在GitHub建立远程仓库，略。

将本地仓库对应到远程仓库，

```
git remote //查看现在关联的远程仓库
git remote -v //更详细，包括链接

// 把Github的新仓库关联到本地仓库，习惯上把远程分支名称记作origin
git remote add origin git@github.com:fenglielie/learn_git_demo.git

```



将远程已有仓库直接克隆到本地，新建本地仓库，也可以使用一个新名字

```
git clone git@github.com:fenglielie/learn_git_demo.git
git clone git@github.com:fenglielie/learn_git_demo.git new_name
```







## 最基本，无分支操作



```
git add file //把file添加到暂存区，包括更改后的和新的文件
git add *

git commit //提交，会跳转到文本编辑器，书写message
git commit -m "message" //提交，附带message

git log //输出日志
git log -2 //只输出最近的2个commit日志
//可以按照下列单行格式，进行输出日志
git log --pretty=format:"%h - [%cn,%ce] %ar : %s"

git status //查看当前三个分区的状态
```

注意，更多的日志格式细节可以参考https://www.w3cschool.cn/isrekq/rigk5ozt.html。



### 撤销操作







### 本地与远程的互动



```
git fetch
```



如果本地的当前分支和远程仓库的分支绑定，则可以使用下面的命令互动

```
git pull //拉取远程
git push //推送到远程
```

它们默认执行的信息为

```
$ git remote show origin
* remote origin
  Fetch URL: git@github.com:fenglielie/learn_git_demo.git
  Push  URL: git@github.com:fenglielie/learn_git_demo.git
  HEAD branch: main
  Remote branch:
    main tracked
  Local branch configured for 'git pull': // git pull 缩写针对的两个分支
    main merges with remote main
  Local ref configured for 'git push': // git push 缩写针对的两个分支
    main pushes to main (up to date)
```



更改远程仓库的简称，从pb1变成pb2

```
git remote rename pb1 pb2
```

移除远程仓库

```
git remote rm pb
```





## 标签

```
git tag //列出现有的标签
git tag -l 'v1.*' 
```



