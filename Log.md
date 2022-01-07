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

## 2021/3/18:
1. 对list中构造函数的隐式转换进行了限制.
2. 对list中的swap函数进行了重写.

## 2021/3/26:
1. 对deque进行重写,使用了新的数据结构:通过二级指针实现的动态数组(与SGI STL中的map_ptr一致).
2. 新增了deque的迭代器:deque_iterator.
3. 对type_traits进行了更新:新增了is_pod用于判断类型是否为普通的旧类型.
4. 对algorithm进行了更新:新增了find_if,count_if,remove_if用于条件触发的函数.

## 2021/3/30:
1. 对关联式和无序容器及其底层构造函数的隐式转换进行了限制,重写其swap函数.

## 2021/4/1:
1. 对Rb_Tree中的InsertFixup函数存在的错误进行了修正.
2. 对List中的alloc函数存在的错误进行了修正.
3. 对iterator的构造函数的隐式转换进行了限制,新增了拷贝构造函数.

## 2021/4/3:
1. 新增了insert_iterator,back_insert_iterator,front_insert_iterator.上述迭代器用于元素的插入,属于input_iterator. 
同时为其添加了不同的inserter函数用于生成迭代器对象.
2. 新增了reverse_iterator反向迭代器.同时为其添加了生成迭代器对象的reverser函数.

## 2021/4/8(1.2.0-alpha):
1. 新增了functor adapters,实现在functional.hpp文件下,详细信息请阅读该文件下的README.
2. 对各容器的运算符进行了const修饰,校对了各容器的型别定义标签.
3. 在type_traits.hpp下新增了type_traits,用于对容器型别标签的萃取.
4. 重写了algorithm下的swap函数,针对不同情况选择不同方式,提升了其运行效率.

### 2021/4/13:
1. 新增了编译期运行的元函数(mate functors).实现在tmp.hpp下,作用与functional.hpp下的仿函数类似.

### 2021/4/22:
1. 对algorithm中的sort函数进行了重写:使用以insert sort和quick sort为基础的intro sort.
2. 对list_iterator中step_count的计数错误进行了修正.

### 2021/4/23:
1. 重写了copy函数,对各种情况及是否pod类型做细分处理.

### 2021/5/5:
1. 对sort函数进行了优化,为其内增了堆排序(heap_sort),且为quick_sort进行了优化.
2. 修正了hash_table中insert函数存在的错误.
3. 修正了RB_Tree中对内存的非法操作.

### 2021/5/7:
1. 对以下函数进行了修改:
- 将mismatch函数更名为mismatch_element
- 将min和max函数更名为min_element和max_element
- 将adjacent_find修改为迭代器类型
2. 新增以下函数:
- mismatch:对两个容器或范围中的元素进行比对,返回第一个不同的元素的迭代器.
- max,min:用于比较两个容器的大小,也可指定比较准则comp(仿函数).
- merge:用于合并两个容器或范围中的元素;与STL不同,支持不同类型容器的合并,合并后的容器也可与前者类型不同.
- search_n:指定一个值,返回指向容器或范围中连续出现该值n次的序列开头的迭代器.

### 2021/5/8:
1. 对quick sort中的bug进行了修改.

### 2021/5/21(1.2.1 -alpha):
1. 新增了对容器元素进行回收处理的elem_destory函数,在memory.hpp下实现.
2. 添加了对容器操作和成员函数调用的防御性设计.
3. 现在const 容器也可使用普通的迭代器.

### 2021/5/25:
1. 新增了防御性的报错提示,实现在errors.hpp下.
2. 将map容器的pair中key类型改为const key.
3. 为unordered_map新增了operator[],返回pair的value值.

### 2021/6/15(1.3.0 -alpha)
1. 新增了内存分配器,实现在memory_allocator.hpp下,其中包含三类分配器:
- malloc_allocator:直接调用malloc & free.
- default_allocator:通过freelist进行内存管理与分配,各容器默认使用此分配器.
- buddy_allocator:使用伙伴分配算法,便于向系统归还内存.

上述三种分配器都通过simple_alloc进行包装使用.

2. 分配计数器(alloc_count):对simple_alloc的分配和归还操作进行计数,若计数不匹配则报错提示,对于容器只适用于部分序列式容器.

### 2021/6/18:
- 在trait_type中添加了便于使用的变量模板.

### 2021/6/19:
- 增加了便于traits classes使用的类型别名模板
- 其中变量模板在enableIfV中不可用:
        
        template<typename t>
        enableIfV<isInt<t>> func(t n)
        {
            //..
        }

在使用中会报错

### 2021/6/26:
- 在type_traits下新增判断类是否有默认构造函数的is_trivial以及ifThenElse.

### 2021/7/13:
- 修复了容器中操作符对分配器模板参数的依赖.

### 2021/7/27:
- 新增了针对容器的线程锁thread_lock类,该类对传入的容器进行加锁包装.实现在container_lock.hpp下.

------------------------------------------------------------------------------------------------------
# v1.0.0

## v1.0.1:重写了sort函数

# v1.1.0

### 2021/11/12:
- 修改了算法中的search及search_n;为迭代器增加了越界检测.

### 2022/1/17:
- 修改了queue及stack的模板参数,使其支持除deque外的其他容器.