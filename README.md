- [SIMD OverView](#overview)
- [Code](#code)
- [Compare](#compare)
- [Perf](#Perf)

#Overview
指令集并行，主要有SSE跟AVX两个指令集来做这个数据并行处理
SSE可以同时处理128bit的数据，AVX可以同时处理512bit的数据
在编译的时候需要加上`-msse -mavx`

#Code
一共实现了两个指令集的矩阵乘法，分别针对`float`跟`double`两种数据类型

#Compare
在保证乘积结果正确的情况下，跟最原始的矩阵乘法比起来是快了大概:
1. float: 30~40倍
2. double: 12~15倍

但是跟numpy里面的`dot`函数比起来，`dot`函数是自己写的17~22倍
不知道为什么这么快

#Perf


