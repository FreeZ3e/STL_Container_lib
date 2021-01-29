# 类STL的容器库

### 介绍
STL中容器和迭代器的简单实现



### 容器
1. 序列式容器：Container_Array,Container_Vector,Container_Deque,Container_List.
    
2. 关联式容器：Container_Map,Container_Set,Container_Multimap,Container_Multiset.

3. 无序容器: Container_Unordered_Map,Container_Unordered_Set,Container_Unordered_Multimap,Container_Unordered_Multiset.

4. 其他容器: RB_Tree,hash_table.

5. 其他:pair

### 迭代器
&emsp;input_iterator,forward_iterator,bidirectional_iterator,random_access_iterator. 

&emsp;list_iterator,RB_Tree_iterator,hash_table_iterator.

### 2020/11/8:
1. 目前迭代器只能通过使用range-base(C++11)的for循环来访问.
2. Container_Deque的内存模型通过一个指针来实现,并不和STL中的实现一致.

### 2021/1/10:
1. 更新了Rb_Tree

### 2021/1/14:
1. 对Rb_Tree的内存非法操作进行了修改,为关联式容器新增了"**比较准则(Compare)**":通过类模板和function obj来实现.
2. 新增了Set和Multiset两个关联式容器.
3. 新增了pair类型.
4. 对list容器调用析构函数的内存错误进行了修复.

### 2021/1/15:
1. 新增了Map和Multimap两个关联式容器.
2. 在pair类型中新增了make_pair函数(该函数返回一个pair类型的对象).

## **2021/1/22(1st edition)**:
1. 新增了以hash_table为底层的无序容器:Unordered_Set,Unordered_Multiset,Unordered_Map,Unordered_Multimap.
2. 新增了hash_table的迭代器.
3. 无序容器中部分方法还未实现(rehash等).

-----------------------------------------------------------------------------------------------------------

## 2021/1/29
对序列式容器进行了更新:
1. 重载=,==,!=,>,<,>=,<=,[]等操作符;新增了返回const迭代器的cbegin,cend函数.  
2. 新增了多项操作函数(swap,resize等). 

对迭代器进行了更新: 
1. 新增了对使用迭代器对象循环的支持.