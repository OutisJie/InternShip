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

### 构建Suffix Array O(nLogn)

