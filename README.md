# 类STL的容器库(**v1.1.0**)

### 介绍
1. 该容器库为STL中容器和迭代器的简单实现.
2. 更新日志见Log.md.



### 容器
1. 序列式容器：array,vector,deque,list.
    
2. 关联式容器：map,set,multimap,multiset.

3. 无序容器: unordered_map,unordered_set,unordered_multimap,unordered_multiset.

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
9. **container lock**



### 最近更新 
### 2022/4/10:
- 修复了各容器中begin()/end()函数在const对象中的返回迭代器类型.