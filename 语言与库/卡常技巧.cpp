卡常技巧总结：
序号	措施	                                                场合	                                备注
1	longlong 取模 传参 结构体方法调用		

2	简化模板 去除冗余部分	                                     模板TLE	

3	手写库函数 手动模拟数据结构 	                             调用库函数如max min极其频繁时
    unordered_map 可以用手写hash加速	

4	inline 	有时可以加速2倍	

5	减法取模尽量通过分数上下同乘或等式左右同乘除化为加法	        频繁取模	

6	vector改数组		

7	避免多次建树 离散化	主席树	

8	不要在循环语句中调用如strlen()方法	循环	                                                        strlen是O（n）的,反复调用会产生O(n^2)的复杂度

9	mod意义下const int  使用int将导致程序变得极慢	              取模	

10	前置++ 而非后置  反复更新值的变量添加register前缀	           循环	

11	bool改char		

12	三目运算符比if else快		

13	调换搜索和枚举顺序	                                         搜索 枚举	

14	IO优化 和取模优化	                                         输入输出庞大 取模频繁	

15	各类位运算	                                                运算较多	



附录：模板
1  取模优化
//设模数为 mod
inline int inc(int x,int v,int mod) {
    x+=v;
    return x >= mod ? x-mod : x;
} //代替取模+
inline int dec(int x,int v,int mod) {
    x-=v;
    return x < 0 ? x+mod : x;
} //代替取模-