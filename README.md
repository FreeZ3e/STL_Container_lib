# 类STL的容器库(**1.1.2-alpha**)

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


## 最近更新 : 2021/3/3
为algorithm新增了以下函数:
1. mismatch : 返回第一个不相同的元素的迭代器位置
2. copy : 将容器中的元素拷贝到另一个容器中(支持不同容器)
3. adjacent_find : 找到并返回容器或范围中相同的元素值
4. includes : 判断两个容器是否具有包含关系