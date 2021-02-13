//单文件include
//#include"Container_(container name).hpp;
//#include"Container_Vector.hpp";

//全文件include
//#include"lib.h";

//------------------------------------------------------------------------


//容器通用操作:

//声明:
//container name<typename> obj name(ctor args)
//vector<int> obj();


//插入操作:
//obj name.insert(elem)
//obj.insert(0);

//删除操作:
//obj name.pop_back()----------------------vector,list,deque
//obj name.pop_front()---------------------list,deque
//obj name.erase(iterator position)
//obj name.erase(iteartor range)
//obj name.remove(elem)--------------------list

//清空操作:
//obj name.clear()

//访问操作:
//
//使用迭代器:
//container name<typename>::iterator/const_iterator obj name;
//for(obj name = begin();obj name != end();obj name++)
//cout<<(*obj name);
//
//vector<int>::iterator p;
//for(p = obj.begin(); p != obj.end();++p)
//cout<<(*p);
//
//基于范围的for循环:
//for(auto p:obj name)
//  cout<<p;
//


//其他操作请阅读各容器文件下的DEADME说明.