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


## 2021/5/7:
1. 对以下函数进行了修改:
- 将mismatch函数更名为mismatch_element
- 将min和max函数更名为min_element和max_element
- 将adjacent_find修改为迭代器类型
2. 新增以下函数:
- mismatch:对两个容器或范围中的元素进行比对,返回第一个不同的元素的迭代器.
- max,min:用于比较两个容器的大小,也可指定比较准则comp(仿函数).
- merge:用于合并两个容器或范围中的元素;与STL不同,支持不同类型容器的合并,合并后的容器也可与前者类型不同.
- search_n:指定一个值,返回指向容器或范围中连续出现该值n次的序列开头的迭代器.