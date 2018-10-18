# Suffix Tree

之前研究过suffix array, suffix array和suffix tree基本上是一样的作用，任何可以用suffix tree解决的办法都能用suffix array来解决。但是suffix array在时间复杂度上要比suffix tree多得多，而且我觉得真的不如直接用后缀树来解决。

为什么呢？因为构建一个后缀树所需要的时间复杂度仅为O(n)，而且也便于理解。

### 概念

**一个给定的字符串text，它的后缀树其实是它的所有后缀的Compressed Tries（压缩特里结构）**。我们先理解一下什么是Compressed Tries：

对于一个文本的集合：

```markdown
{bear, bell, bid, bull, buy, sell, stock, stop}
```

这个集合的Standard Tries如下图：

![suffixtree1](.\img\suffixtree1.png)

可以看到每条从根节点到叶子节点的路径都表示一个字符串。Compressed Tries就是将Standard Tries压缩之后得到的结果，压缩就是指将之后一个节点的链路合并起来，如下图：

![suffixtree2](./img/suffixtree2.png)

那么这和后缀树有什么关系呢？又怎样构建一个后缀树呢？

其实，对于一个字符串‘banana’，它的所有后缀构成了一个集合（\0表示字符串的结尾）：

```markdown
{banana$, anana$, nana$, ana$, na$, a$, $}
```

那么这个集合的Standard Tries就是：

![suffixtree3](./img/suffixtree3.png)

我们把这个树压缩：

![suffixtree4](./img/suffixtree4.png)

得到的这个树就是传说中的后缀树了。



### 定义

对于一个长度为n的字符串S，有这样一颗树：

- 这棵树恰好有n个叶子节点；
- 除了根节点以外，每个内部节点至少有两个以上的子节点；
- 每条边都有S的某个非空字串标记；
- **从某一个节点出发的两条边，它们的其实字符不可能一样**；
- 每条从根节点到叶子节点i的路径构成了S的一个后缀S[i, n]；



### 实现

#### 原始办法



#### Ukkonen's Suffix Tree Construction

