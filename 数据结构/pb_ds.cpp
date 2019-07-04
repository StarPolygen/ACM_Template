#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

//优先队列-可并堆
typedef __gnu_pbds::priority_queue<int> heap; //默认从大到小
typedef __gnu_pbds::priority_queue<int,greater<int> > heap; //默认从小到大
heap q;
heap::point_iterator id;
//pb_ds库的push操作是有返回值的（与STL不同），返回的类型就是迭代器
//这样用一个迭代器数组保存所有push进优先队列的元素的迭代器，就可以随时修改优先队列内部元素了。

//合并  优先队列b内所有元素就被合并进优先队列a中，且优先队列b被清空
a.join(b);

//使用
while (!q.empty()) q.pop();             //弹出堆顶
for (int i=1;i<=10;i++) q.push(i);      //加入
auto it=q.push(11);                     //迭代器使用
q.modify(it,50);                        //利用迭代器修改堆内元素
cout<<q.top()<<endl;        
q.erase(it);                            //利用迭代器删除元素
cout<<q.top()<<endl; 
assert ( q. top () == 10); 
for (int i=10;i<=20;i++) qq.push(i);
q.join(qq);cout<<q.top();               //合并堆

----------------------------------------------------------------------------------



//平衡二叉树

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbtree;
rbtree q,qq;
//参数：键类型、值类型，null_type表示没有值，简单地理解就是表明这是set而不是map
//G++版本稍旧（4.3.2），需要写成null_mapped_type才可以
//第三个表示比较函数，默认为less<Type>；第四个为平衡二叉树的类型，默认为红黑树rb_tree_tag；
//第五个代表元素的维护策略，只有当使用tree_order_statistics_node_update时才可以求kth和rank

//插入（insert）、删除（erase）、求kth（find_by_order）、求rank（order_of_key）
//求kth（find_by_order）返回的是迭代器，求rank返回的是值，两者都是从0开始计算的

//合并（join）和分离（split）
tree<int,null_type> a,b;
a.join(b);          
//两棵树的key的取值范围不相交，否则会抛出一个异常；合并后平衡二叉树b被清空
a.split(v,b);       
//v与key类型相同，key小于等于v的元素属于a，其余属于b，此时后者已经存有的元素将被清空。

//使用
for (int i=1;i<=20;i+=2) q.insert(i);           // 插入        序列 1、3、5、7、9、11、13、15、17、19 
cout<<q.order_of_key(5)<<endl;                  // 求rank      小于5的个数  也是5的序数（0起）
auto x=q.find_by_order(6);                      // 求kth       查找第6大的数，0 为起点
rbtree::iterator it=q.find_by_order(6);  
cout<<*x<<endl;cout<<*it<<endl;                              
q.erase(it);                                    // 删除
x=q.find_by_order(6);
cout<<*x<<endl;q.insert(13);
auto z=q.lower_bound(16);cout<<*z<<endl;        //大于等于16的第一个数 
auto zz=q.upper_bound(17);cout<<*zz<<endl;      //大于16的第一个数 
for (int i=21;i<=40;i+=2) qq.insert(i);
q.join(qq);                                     //合并         注意合并的两颗树的值域的范围不能相交 
for (auto x:q) cout<<x<<' ';cout<<endl;         
q.split(29,qq);
for (auto x:q) cout<<x<<' ';cout<<endl;         //分离         小于等于29的元素在q，其余在qq   

----------------------------------------------------------------------------------




// Hash
gp_hash_table<int,bool>h;
//使用
h[1]=1;
cout<<h[1]<<endl;
for (auto x:h) cout<<x.second<<endl

----------------------------------------------------------------------------------