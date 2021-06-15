# 类STL的容器库(**1.3.0-alpha**)

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
6. **memory(elem_destory)**
7. **errors**
8. **memory allocator**



### 最近更新 
#### 2021/6/15(1.3.0 -alpha)
1. 新增了内存分配器,实现在memory_allocator.hpp下,其中包含三类分配器:
- malloc_allocator:直接调用malloc & free.
- default_allocator:通过freelist进行内存管理与分配,各容器默认使用此分配器.
- buddy_allocator:使用伙伴分配算法,便于向系统归还内存.

上述三种分配器都通过simple_alloc进行包装使用.

2. 分配计数器(alloc_count):对simple_alloc的分配和归还操作进行计数,若计数不匹配则报错提示,对于容器只适用于部分序列式容器.