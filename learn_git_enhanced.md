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



注意到，切换分支会直接更改本地文件夹，也就是会丢失本地所有未提交的修改信息，直接恢复到HEAD指向的提交状态。

在移动分支前，建议完成提交。



### 2.3 分支合并

上述情景中，可能实现提交链表分叉的情形

1. 在”提交1“处，有HEAD->master，新建一个分支testing
2. HEAD->testing，在此分支上，提交一个新的结点“提交2”

3. 从而 HEAD->testing 随之移动到了“提交2”，而master仍然留在"提交1"
4. HEAD->master，回到主分支，提交一个新的结点"提交3"
5. HEAD->testing随之移动到了"提交3"

现在，”提交2“和”提交3“都是直接基于”提交1“的，两者没有明确的继承关系，提交链表产生分叉。

![advance-master](D:\coderoot\learn_git\learn_git_enhanced_images\advance-master.png)

适用情景

master指向现在的成熟版本，新建一个分支isss53，在iss53分支处理这个问题，也就是下一版的更新内容，如果没有处理好，就不把master移动过去。

正在处理的时候，遇到加急的问题hotfix，和iss53相互独立，则回退过去，新建一个分叉hotfix/iss53，解决完成后，可以回退到master->iss53这条路线，这是主要工作。

![basic-branching-4](D:\coderoot\learn_git\learn_git_enhanced_images\basic-branching-4.png)



#### 前后合并：

如果hotfix分支解决的很好，则master分支可以随之移动过去，由于这里是先后继承关系，合并是“快进”的

```
git checkout master
git merge hotfix
```





![basic-branching-5](D:\coderoot\learn_git\learn_git_enhanced_images\basic-branching-5.png)

#### 分叉合并：

例如以下状态

![basic-merging-1](D:\coderoot\learn_git\learn_git_enhanced_images\basic-merging-1.png)

当前HEAD处于master分支位于**C4**，还有一个分支iss53**C5**，它们没有先后关系，但是存在一个公共祖先**C2**，这种情景下，我们希望两个分支可以合并。

它们涉及了三个提交结点，两个分支指针。

```
git checkout master
git merge iss53
```

![basic-merging-2](D:\coderoot\learn_git\learn_git_enhanced_images\basic-merging-2.png)













