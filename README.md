# 类STL的容器库(**1.2.0-alpha**)

### 介绍
1. 该容器库为STL中容器和迭代器的简单实现.
2. 在使用前请阅读test下的QuickStart以及各容器文件下的README.
3. 更新日志见Log.md.



### 容器
1. 序列式容器：Container_Array,Container_Vector,Container_Deque,Container_List.
    
2. 关联式容器：Container_Map,Container_Set,Container_Multimap,Container_Multiset.

3. 无序容器: Container_Unordered_Map,Container_Unordered_Set,Container_Unordered_Multimap,Container_Unordered_Multiset.

4. 底层容器: RB_Tree,hash_table.

5. 其他容器: self_string,queue,stack.


### 迭代器(包含const与非const)
&emsp;input_iterator,forward_iterator,bid_iterator,random_iterator. 

&emsp;list_iterator,RB_Tree_iterator,hash_table_iterator.

### 其他
1. pair类型
2. **type_traits**
3. **algorithm**
4. **functional**


##  2021/4/8(1.2.0-alpha)
1. 新增了functor adapters,实现在functional.hpp文件下,详细信息请阅读该文件下的README.
2. 对各容器的运算符进行了const修饰,校对了各容器的型别定义标签.
3. 在type_traits.hpp下新增了type_traits,用于对容器型别标签的萃取.
4. 重写了algorithm下的swap函数,针对不同情况选择不同方式,提升了其运行效率.