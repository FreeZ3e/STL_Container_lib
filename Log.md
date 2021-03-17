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

## **2021/1/22(1.0.0-alpha)**:
1. 新增了以hash_table为底层的无序容器:Unordered_Set,Unordered_Multiset,Unordered_Map,Unordered_Multimap.
2. 新增了hash_table的迭代器.
3. 无序容器中部分方法还未实现(rehash等).

-----------------------------------------------------------------------------------------------------------

## 2021/1/29(1.0.1-alpha)
对序列式容器进行了更新:
1. 重载=,==,!=,>,<,>=,<=,[]等操作符;新增了返回const迭代器的cbegin,cend函数.  
2. 新增了多项操作函数(swap,resize,erase等). 

对迭代器进行了更新: 
1. 新增了对使用迭代器对象循环的支持.

## 2021/2/1(1.0.2-alpha)
1. 对序列式容器的const_iterator进行了修复.
 
2. 对序列式容器的迭代器进行了重构.

## 2021/2/3(1.0.3-alpha)
对关联式容器进行了更新:
1. 重载=,==,!=,>,<,>=,<=,[]等操作符;新增了返回const迭代器的cbegin,cend函数.  
2. 新增了多项操作函数(swap,resize,erase等). 

对RB_Tree的迭代器进行了更新:
1. 重载==,>,<,>=,<=,操作符;新增了step_count计数符来对遍历操作进行计数,可通过**step**函数返回其值.

## 2021/2/4(1.0.4-alpha)
1. 对序列式容器及关联式容器新增了基于迭代器范围(range-of-iterator)的erase函数.
2. 对list_iterator和基本迭代器(input,forward,bid,random)重载了==,>,<,>=,<=,操作符;新增了step_count计数符来对遍历操作进行计数,可通过**step**函数返回其值.

## 2021/2/10(1.1.0-alpha)
1. 为hash_table新增了const_iterator;并新增了多项操作函数及操作符重载.
2. 对无序容器新增了多项操作函数及操作符重载;新增了返回const_iterator的cbegin,cend函数.

## 2021/2/16(1.1.1-alpha)
1. 对序列式容器中隐含的错误做出修改.
2. 增加了对self_string(即将上传)的支持.

## 2021/2/17
1. 新增了以deque为底层的queue和stack容器.

## 2021/2/19
1. 新增了type_traits.

## 2021/2/21
1. 对list中clear函数未进行内存重分配的bug进行修复.

## 2021/2/23
1. 为deque与vector新增了empty函数.
2. 为序列式容器新增了insert函数,该函数调用push_back函数.
3. 新增算法库algorithm.

## 2021/2/26(1.1.2-alpha)
1. 修复了algorithm中sort算法的错误,并为其增加了"**比较准则(compare函数)**"模板.
2. 为迭代器添加了表示数据类型的TypeValue标签.
3. 为List,RB_Tree,HashTable的节点类型添加了表示数据类型的TypeValue标签.

## 2021/3/1
1. 为list添加了传入元素的erase函数.
2. 为algorithm新增了replace,unique函数;优化了sort对模板的依赖.

## 2021/3/3
为algorithm新增了以下函数:
1. mismatch : 返回第一个不相同的元素的迭代器位置
2. copy : 将容器中的元素拷贝到另一个容器中(支持不同容器)
3. adjacent_find : 找到并返回容器或范围中相同的元素值
4. includes : 判断两个容器是否具有包含关系

## 2021/3/4:
1. 对algorithm中的各算法进行空间优化.
2. 在algorithm中新增了for_each函数.
该函数接受一个容器和带返回值的自定义函数参数,可将容器中的元素通过函数进行处理.

## 2021/3/6:
1. 对algorithm中的sort算法进行了重写.
2. 对各迭代器的递增操作符进行了修改.
3. 为HashTable新增了rehash函数;该函数接受一个新的hash函数,并进行rehash操作.
4. 对RB_Tree中的insert函数潜在的错误进行了修改.

## 2021/3/7:
1. 对algorithm中的for_each函数进行了修改.

## 2021/3/15:
1. 对array中的构造函数的隐式转换进行了限制.
2. 对array中的swap函数进行了重写.

## 2021/3/16:
1. 对vector中的构造函数的隐式转换进行了限制.
2. 对vector中的swap函数进行了重写.

## 2021/3/17:
1. 对deque中构造函数的隐式转换进行了限制.
2. 对deque中的swap函数进行了重写.