# Git/GitHub 学习笔记

在这篇笔记中，Git的部分主要参考以下教程，第一个比较硬核：

1. [Git - 关于版本控制 (git-scm.com)](https://git-scm.com/book/zh/v2/起步-关于版本控制)

2. [Git 基础_w3cschool](https://www.w3cschool.cn/isrekq/5vgsrozt.html)

我们省略了一些最基础的介绍，包括分布式和集中式版本控制的区别，以及Git的优势。



## 1. Git 文件状态

在版本控制中，Git 记录的是文件快照，也就是在.git/objects里面的那些哈希值生成的文件夹和文件，如果未修改，则新版本中只会直接指向旧的。并且与集中式版本控制不同，Git不纠结于具体细节的变化。

![snapshots](learn_git_images/snapshots.png)



这是在git中，文件的四种状态，

![](learn_git_images/git_lifecycle.png)

文件分为四种状态：

1. untracked：未被跟踪的，可能是新发现的文件，
2. unmodified：已提交的（未修改的），也就是现在Git已经完全记录了这个版本的文件，只能从缓存文件commit 得到
3. modified：修改的，指的是对已经记录的版本文件，进行了新的修改
4. staged：缓存的，可以把新文件或者修改后文件使用git add 增加到缓冲区



对于实践操作中，则主要分成三个区域：

1. 工作区域：也就是真实的目录文件
2. 缓存区域
3. 仓库区域



基本的本地仓库工作流程：

* 在本地目录新建文件（变成未跟踪的），添加到缓存区域（变成缓存的），正式提交到仓库区域（变成已提交的）

* 对于现有的文件（已提交的），在本地目录上对文件直接进行修改（变成修改的），添加到缓存区域（变成缓存的），正式提交到仓库（变成新版本的已提交的）





## 2. Git 初始化配置

配置目录包括三级，越具体的配置优先级越高，

* 系统级配置，在安装目录；

* 用户级配置，在~/.gitconfig；
* 仓库级配置，在.git/config。



一般在用户级配置中，配置用户名和邮箱

```
git config --global user.name "fenglielie"
git config --global user.email fenglielie@qq.com
```

注意，在提交到Github后，只会关注emali，不会关注前面的名称，因此可以用fenglielie(local)，fenglielie(tc)，fenglielie区分我的不同的提交来源。



提交信息的文本编辑器，建议使用 vim

```
git config --global core.editor vim
```

默认的主分支名称，为了和GitHub一致，使用main

```
git config --global init.defaultbranch main
```

检查配置，重复可能是多级配置文件中的重复项。

```
git config --list
```

获取帮助

```
git help <sth>
git sth --help
```





## 3. Git 建立本地仓库

我们首先不涉及远程操作，针对已有若干文件的非空文件夹project，初始化。

```
cd project
git init
git add *
git commit -m "initial project"
```

命令解释：

* git init 初始化，会得到.git隐藏目录
* git add \* 把所有文件（未追踪的）添加到缓存区（变成缓存的）
* git commit -m “sth” 把缓存区域的所有文件正式提交（变成已提交的），并且随之附上提交的信息，自动附上提交者的签名（名字，邮箱）



### 3.1 基本操作

仓库初始化

```
git init 
```

检查当前的本地的状态

```
git status
```

跟踪新文件（未被跟踪的）到缓存区域（变成缓存的）

```
git add filename
git add *
```

修改文件（已提交的->修改的），放置到缓存区域（变成缓存的）

```
git add filename
```

注意：

如果修改文件存在缓存区域中，又继续进行了修改，则现在由三个版本同时存在：

1. 本地目录实在的：第二次修改后的（修改的）
2. 缓存区域的：第一次修改后的（缓存的）
3. 仓库区域的：（已提交的）

此时如果直接git commit会把第一次修改后的提交；如果git add 会用第二次修改后的覆盖第一次修改后的，出现在缓存区，再进行git commit提交即可。

提交文件

```
git commit
git commit -m "message" //附带message
git commit -a //自动首先进行git add，从而跳过这一步
```





### 3.2 忽略文件

在本地目录下，使用.gitignore文件配置忽略文件，建议在仓库初始化以后立刻添加该文件。

可以设置用户级的默认 ignore 文件，用户级配置中添加下列选项，并且在对应位置新建 ignore 格式文件即可。

```
core.excludesfile = "~/.gitignore_global"
```



例如，这是一个仓库级的 ignore 配置目标

```
# 使用井号进行注释
# 具体的可以复制这个文件到仓库中，这是一个可用的仓库级模板

# 忽略所有test开头的.exe文件
test*.exe

# 忽略任何目录下的ignore文件夹
ignore/
# build/

# 忽略当前目录下的TODO文件，不会忽略其他位置的TODO
/TODO

# 忽略doc目录下的所有.txt文件，但不包括它子目录下的.txt文件
doc/*.txt

# 忽略dox目录下的所有.pdf文件，以及它的子目录下的.pdf文件
doc/**/*.pdf
```



### 3.3 提交历史

```
git log //输出日志

git log -2 //只输出最近的2个commit日志

git log --since=2.weeks //只输出最近两周的日志
git log --since="2022-02-02" //只输出指定日期之后的
//类似的，还有指定日期之前的 --until="2022-02-20"

//可以按照下列单行格式，进行输出日志
git log --pretty=format:"%h - [%cn,%ce] %ar : %s"
```

更多的提交历史格式信息，可以参考 [Git - 查看提交历史 (git-scm.com)](https://git-scm.com/book/zh/v2/Git-基础-查看提交历史)



### 3.4 删除文件

[Git - 记录每次更新到仓库 (git-scm.com)](https://git-scm.com/book/zh/v2/Git-基础-记录每次更新到仓库)





### 3.5 移动文件

由于Git基于文件内容的哈希值去索引文件，重命名文件会被智能识别出来。

```
git mv file_from file_to

//等价于下面三条命令
mv file_from file_to
git rm file_from
git add file_to
```



## 4. Git 撤销操作

### 4.1 修正上一次提交

如果刚刚进行了提交，但是有几个文件没有进行修改补充，或者提交信息写错了，则可以使用下列命令补丁

```
git commit --amend
```

此时，会把现在的缓存区内容也加上去提交，并且重新调出编辑器，修改message







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



