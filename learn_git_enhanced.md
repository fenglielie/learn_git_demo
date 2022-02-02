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
git branch -v //列出分支，以及HEAD位置，还有分支附加信息，包括位于哪个提交结点

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

#### 分叉无冲突合并：

例如以下状态

![basic-merging-1](D:\coderoot\learn_git\learn_git_enhanced_images\basic-merging-1.png)

当前HEAD处于master分支位于**C4**，还有一个分支iss53**C5**，它们没有先后关系，但是存在一个公共祖先**C2**，这种情景下，我们希望两个分支可以合并。

它们涉及了三个提交结点，两个分支指针。

```
git checkout master
git merge iss53
```

![basic-merging-2](D:\coderoot\learn_git\learn_git_enhanced_images\basic-merging-2.png)

合并后，如果没有冲突，则自动创建一个新提交节点，提交结点自带一个merge标签，表明是那两个结点合并而来，不妨称作**merge提交结点**。



#### 分叉有冲突合并：

在上面的分叉合并中，如果产生冲突，则不会新建提交结点，而是把非冲突文件正常处理，冲突文件在内部按照特定格式展示冲突信息。例如

```
<<<<<<< HEAD
this is in main branch
=======
this is in testing_conflict branch
>>>>>>> testing_conflict
```

使用vimdiff等工具，或者直接修改冲突文件，把那些辅助行都删除后，继续提交

```
git add *
git commit -m "message"
```

则现在得到的仍然是**merge提交结点**。





除了合并，还有更高级的变基操作，[Git - 变基 (git-scm.com)](https://git-scm.com/book/zh/v2/Git-分支-变基)



### 2.4 分支管理

```
//列出当前所有分支
git branch 
git branch -v
```



```
//筛选出，已合并到当前分支的分支列表
//如果现在是主分支，则列出的都是”死分支“
git branch --merged

//筛选出，尚未合并到当前分支的分支列表
//如果现在是主分支，则列出的都是“活分支”
git branch --no-merged

//删除分支 (不能删除*分支，也就是HEAD所在的当前分支)
git branch -d test_branch
//注意，如果想要删除的分支未合并到当前分支，则删除意味着丢失信息，会报错
//但可以使用 -D 强制删除

```

上述操作都是基于当前分支的视角，如果不想移动，可以使用后缀去查看在那个分支视角下，哪些分支未合并等

```
git branch --no-merged main //相对于main主分支，哪些分支未合并
```



### 2.5 基于分支的开发流



风格一，长期分支，main标记稳定版，长期滞后于开发，只有在新版本稳定后让main跟上进度。

![lr-branches-1](D:\coderoot\learn_git\learn_git_enhanced_images\lr-branches-1.png)



风格二，主题分支，以问题或扩展功能为导向，在实现后合并到main中

![topic-branches-1](D:\coderoot\learn_git\learn_git_enhanced_images\topic-branches-1.png)



## 3. 远程仓库与分支

在远程仓库中，有远程分支，这是在本地无法移动的，在网络通信后，Git会适当移动它们以反映远程仓库状态。（相当于需要联网的书签）



例如origin/main分支，就是Github仓库的远程分支。

clone行为的本质：

用origin指代远程仓库，拉取所有数据到本地，默认与远程仓库的main分支一样创造一个本地的origin/main分支，同时在本地创造一个main分支，也就是我们所在的并且可以移动的分支。相对的origin/main我们不可以直接移动，只会在联网时基于网络信息发生更改。

![remote-branches-1](D:\coderoot\learn_git\learn_git_enhanced_images\remote-branches-1.png)

注意：

main是默认主分支，这个可以修改默认名。

origin是默认的远程仓库名称，可以在git clone时添加 -o选项指定远程仓库名不是origin而是其他的。



### 3.1 git fetch

```
//git fetch <remote> 具体即
git fetch origin
```

表示从远程仓库抓取信息，照着远程仓库的信息延申提交链表，origin/main随之移动。

![remote-branches-3](D:\coderoot\learn_git\learn_git_enhanced_images\remote-branches-3.png)

很自然的，如果远程仓库发送了别的修改提交，而本地也进行了提交，则会产生分叉。



除此之外，可以添加多个远程仓库，例如下图

![remote-branches-5](D:\coderoot\learn_git\learn_git_enhanced_images\remote-branches-5.png)



### 3.2 跟踪分支

远程跟踪分支，例如origin/main，我们有本地的分支“智能地”与之跟踪。

它们称之为“上游分支”和“跟踪分支”，例如origin/main和main。

使用git branch -vv 可以更详细地展示本地分支信息，其中就包括是否是跟踪分支及其上游分支。

```
$ git branch -vv
* main             87165d3 [origin/main: ahead 3] 分支冲突合并处理
  testing_conflict b97efa8 分支冲突测试testing_conflict
```



注：clone会自动基于origin/main创造本地分支main，并且设置main跟踪origin/main。

也可以手动设置跟踪分支，

```
git checkout -b serverfix_local origin/serverfix
```

这里表示，新建本地分支serverfix_local，用它跟踪远程分支origin/serverfix。

而且存在简写，表示新建本地分支（同名）跟踪这个远程分支。

```
git checkout --track origin/severfix
```

甚至更智能的，如果存在远程分支origin/pb，并且不存在本地分支pb，则下面命令自动建立本地分支pb，同时跟踪远程分支origin/pb

```
git checkout pb
```



不是新建本地分支，而是把已有的本地分支pb追踪远程分支origin/pb2，或者修改上游分支，则可以手动设置

```
git branch --set-upstream-to origin/pb2
//当前在pb本地分支
```



### 3.3 git push





### 3.4 git pull

等价于git fetch + git merge，也就是本身自带了合并，而git fetch不尝试合并，会把分叉留给你处理。

对于跟踪分支，它会fetch上游分支到本地，然后merge本地跟踪分支。

pull有些行为不太明确，因此建议单独使用git fetch和git merge





### 3.5 本地删除远程分支

```
git push origin --delete severfix
```

删除远程仓库的severfix分支











































