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
5. **mate functors(tmp)**


## 2021/5/5
1. 对sort函数进行了优化,为其内增了堆排序(heap_sort),且为quick_sort进行了优化.
2. 修正了hash_table中insert函数存在的错误.
3. 修正了RB_Tree中对内存的非法操作.