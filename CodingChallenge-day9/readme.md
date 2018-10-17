# suffix array

后缀数组是由一个字符串的所有后缀排序之后生成的数组；

## example

对于字符串Banana\$ ,  $符号用于表示字符串的结尾。它的后缀包括有：

```
5. a$;
4. na$;
3. ana$;
2. nana$;
1. anana$;
0. banana$;
```

将上面的后缀列表进行排序，得到

```
5. a$;
3. ana$;
1. anana$;
0. banana$;
4. na$;
2. nana$;
```

这个新的列表就是‘banana$’的suffix array了



###	构建suffix array O(n^2Logn)

我们使用一个结构体来存储每个后缀的信息：

```c++
struct suffix{
    int index; //后缀的起始位置
    char *suff; //后缀字串的起始指针
}
// 得到一个suffix的数组
struct suffix suffixes = [n];//一般来说，不能使用变量名来初始化数组
char txt[] = 'banana';
for(int i = 0; i < n; i ++){
    suffixes[i].index = i;
    suffixes[i].suff = txt + i; //C++只需要将字符串的头指针往后移即可，*（txt+1）表示该位置的后缀
}

//排序
sort(suffixes, suffixes+n, cmp);

int cmp(struct suffix a, struct suffix b){
    return strcmp(a.suff, b.suff) < 0 ? 1:0;
}
```

上述算法主要是排序占用很多时间，如果我们考虑用于排序的算法时间复杂度是O（nLogn）,那么由于每次只能对两个字串排序，英雌需要排序n次。所以时间复杂度为O(n^2Logn)

### 构建Suffix Array O(nLognLogn)

因为我们能够看出，影响上述算法速度的原因就是字符串之间的比较非常耗费时间，那么有什么办法可以快速的比较两个字符串的大小呢?

我们不妨先根据每个后缀字符串的第一个字符进行比较排序，然后再根据前两个字符进行排序，然后再根据前4个字符排序，以此类推，具体思路如下：

我们先预留两个问题：

1. 字符数递增是2^i还是2*i？
2. 每次字符递增都需要对所有的字符串重新排序吗？



#### 思路：

1. 如何根据前两个字符串来排序并且尽可能的快呢？其实很简单，每个字符不都是有ASCII码吗，那为何不直接用一个字符和‘a’相减，得到的差作为该字符的等级呢，这样就直接变成了数字之间的比较了。所以，以banana为例，比较第一个字符：

   ```markdown
   index   Suffix     Rank
   0        banana     1
   1        anana      0 
   2        nana       13 
   3        ana        0
   4        na         13
   5        a          0 
   ```

2. 我们先别急着对上述排序，因为有几个字符串的首字符是一样的，急着排序也没什么效果，为了加快效率，我们每一次排序的时候，把前两个字符一起进行比较，所以我们可以有该字符当前的rank，该字符下一个字符的rank。当然，如果该字符已经是最后一个字符了，那么它的next rank就设为-1：

   ```markdown
   index   Suffix     Rank   Next Rank
   0        banana     1         0
   1        anana      0         13
   2        nana       13        0
   3        ana        0         13
   4        na         13        0
   5        a          0         -1
   ```

3. 排序，同样用结构体来存数据，代码会很简单：

   ```c++
   struct suffix {
       int index;  //current index
       int rank[2];//rank and next rank
   }
   struct suffix suffixes[n];
   sort(suffixes, suffixes+n, cmp);
   int cmp(struct suffix a, struct suffix b){
       return (a.rank[0] == b.rank[0]) ? 
           	(a.rank[1] < b.rank[1] ? 1:0)
           	:
       		(a.rank[0] < b.rank[0] ? 1:0)
   }
   ```

   结果：

   ```markdown
   Index    Suffix            Rank          Next Rank 
    5        a                  0              -1
    1        anana              0               13    
    3        ana                0               13
    0        banana             1               0
    2        nana               13              0
    4        na                 13              0  
   ```

4. 一次排序并不能得到最终的结果，我们还需要考虑前四个字符，如何比较前四个字符呢，因为前面已经得到前两个字符的比较结果了，所以需要在此基础上重新对rank和next rank进行取值。

   将每个字符串的（rank, next rank）作为等级对，第一个字符串的rank设为0，其余字符串和前一个字符串的等级对比较，如果一样，那么rank不变；如果不一样，那么rank++

   ```markdown
   Index       Suffix          Rank       
     5          a               0     [Assign 0 to first]        
     1          anana           1     (0, 13) is different 
     3          ana             1     (0, 13) is same as previous     
     0          banana          2     (1, 0) is different
     2          nana            3     (13, 0) is different
     4          na              3     (13, 0) is same as previous  
   ```

5. 对上表的每个suffix str[i]，获取它在str[i+k/2] (k =4; k<2n; k=k*2)的后缀的rank，因为i和i+1在前面已经算过了。

   ```markdown
   Index       Suffix          Rank     Next Rank
     5          a               0         -1
     1          anana           1         1 （1+2）就是index为3的rank
     3          ana             1         0  index为5的rank
     0          banana          2         3  index为2的rank
     2          nana            3         3  同理
     4          na              3         -1 同理
   ```

6. 再对上述排序，重复完成4、5、6，直到k>=2n;

7. 代码：

   ```c++
   // This is the main function that takes a string 'txt' of size n as an 
   // argument, builds and return the suffix array for the given string 
   int *buildSuffixArray(char *txt, int n) 
   { 
       // A structure to store suffixes and their indexes 
       struct suffix suffixes[n]; 
     
       // Store suffixes and their indexes in an array of structures. 
       // The structure is needed to sort the suffixes alphabatically 
       // and maintain their old indexes while sorting 
       for (int i = 0; i < n; i++) 
       { 
           suffixes[i].index = i; 
           suffixes[i].rank[0] = txt[i] - 'a'; 
           suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1; 
       } 
     
       // Sort the suffixes using the comparison function 
       // defined above. 
       sort(suffixes, suffixes+n, cmp); 
     
       // At this point, all suffixes are sorted according to first 
       // 2 characters.  Let us sort suffixes according to first 4 
       // characters, then first 8 and so on 
       int ind[n];  // This array is needed to get the index in suffixes[] 
                    // from original index.  This mapping is needed to get 
                    // next suffix. 
       for (int k = 4; k < 2*n; k = k*2) 
       { 
           // Assigning rank and index values to first suffix 
           int rank = 0; 
           int prev_rank = suffixes[0].rank[0]; 
           suffixes[0].rank[0] = rank; 
           ind[suffixes[0].index] = 0; 
     
           // Assigning rank to suffixes 
           for (int i = 1; i < n; i++) 
           { 
               // If first rank and next ranks are same as that of previous 
               // suffix in array, assign the same new rank to this suffix 
               if (suffixes[i].rank[0] == prev_rank && 
                       suffixes[i].rank[1] == suffixes[i-1].rank[1]) 
               { 
                   prev_rank = suffixes[i].rank[0]; 
                   suffixes[i].rank[0] = rank; 
               } 
               else // Otherwise increment rank and assign 
               { 
                   prev_rank = suffixes[i].rank[0]; 
                   suffixes[i].rank[0] = ++rank; 
               } 
               ind[suffixes[i].index] = i; 
           } 
           // Assign next rank to every suffix 
           for (int i = 0; i < n; i++) 
           { 
               int nextindex = suffixes[i].index + k/2; 
               suffixes[i].rank[1] = (nextindex < n)? 
                                     suffixes[ind[nextindex]].rank[0]: -1; 
           } 
     
           // Sort the suffixes according to first k characters 
           sort(suffixes, suffixes+n, cmp); 
       } 
     
       // Store indexes of all sorted suffixes in the suffix array 
       int *suffixArr = new int[n]; 
       for (int i = 0; i < n; i++) 
           suffixArr[i] = suffixes[i].index; 
     
       // Return the suffix array 
       return  suffixArr; 
   } 
   ```



### 总结：

回答前面的问题，每次都需要对整个队列重新排序，时间复杂度nLogn，一共需要排序Logn次，所以，时间复杂度为O(n*Logn*Logn); 对于需要重新分配rank的字符数，第一次k(k=2^1), 第二次k(k=2^2), 第n次k=2^n.