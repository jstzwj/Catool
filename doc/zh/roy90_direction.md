﻿为什么rot90是默认逆时针旋转矩阵？
因为矩阵是列优先表示，[cos,sin;-sin,cos]旋转矩阵使得坐标顺时针旋转，而列优先
。。。想错了。。。


====================


正文
如何做矩阵旋转，
答：使用 初等旋转矩阵（Givens矩阵）加上坐标偏移修正。