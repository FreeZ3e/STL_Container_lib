# 类STL的容器库

#### 介绍
    STL中容器和迭代器的简单实现



#### 容器
    序列式容器：Container_Array,Container_Vector,Container_Deque,Container_List.
    
    关联式容器：Container_Map,Container_Set.

    其他容器:RB_Tree.

#### 迭代器
    input_iterator,forward_iterator,bidirectional_iterator,random_access_iterator.

#### 2020/11/8:
    目前迭代器只能通过使用range-base(C++11)的for循环来访问.
    Container_Deque的内存模型通过一个指针来实现,并不和STL中的实现一致.

#### 2021/1/10:
    更新了Rb_Tree