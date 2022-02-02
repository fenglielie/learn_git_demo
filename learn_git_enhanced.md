# Git/GitHub 学习笔记 进阶版

这篇笔记的重点内容就是分支模型，也就是Git的精髓。

参考[Git - 分支简介 (git-scm.com)](https://git-scm.com/book/zh/v2/Git-分支-分支简介)



## 1. 分支基础

Git基于文件快照，来创建轻量级的分支管理系统。



首先，缓存操作：Git对于缓存区的每个文件计算哈希值，根据文件创建一个以哈希值命名的blob对象，存储在.git中。

第二步，提交操作：Git把现在的blob对象整理，对应于真实的目录结构，创造各级的树对象指向文件夹中blob对象，然后创造提交对象，提交对象指向根目录的树对象。如下图，从左到右，依次是"提交对象"，”树对象“，“blob对象”。

![](learn_git_enhanced_images/commit-and-tree.png)



版本更新是基于“提交对象”的，提交对象不仅指向自己的根目录树对象，也指向上一次提交的“提交对象”。如下图

![](learn_git_enhanced_images/commits-and-parents.png)



分支对象（默认的一个为master/main）：本质上是指向提交对象的可移动指针。

HEAD：当前状态，本质上是一个指向分支对象的更高级的可移动指针.如下图

![branch-and-history](learn_git_enhanced_images/branch-and-history.png)





## 2. 分支操作



### 2.1 创建新分支

```
git branch testing 

git branch //列出所有分支，以及当前HEAD所处的分支
git log 也会附带分支信息
```



本质上是在当前位置HEAD所对应的提交链表位置，创建了新的指针testing指向它。

下图中，HEAD指向master，说明当前所在的分支是master分支，新建了一个testing分支

![head-to-master](learn_git_enhanced_images/head-to-master.png)





### 2.2 切换分支

切换分支，本质上就是把HEAD指针移动，

```
git checkout testing
```

此时，HEAD指向testing，而不再指向默认分支master



如果此时我们进行一次提交，则提交链表随之延长。

**HEAD指针以及testing分支指针随之移动，而master分支指针仍然留在了原地！**

![advance-testing](learn_git_enhanced_images/advance-testing.png)

可以使用如下命令把HEAD拨回到master分支指针

```
git checkout master
```



使用-b参数可以新建分支并且直接把HEAD指向它

```
git branch new_branch
git checkout new_branch

//上述两条等价于 创建与切换一步搞定
git checkout -b new_branch
```



### 2.3 分支分叉



