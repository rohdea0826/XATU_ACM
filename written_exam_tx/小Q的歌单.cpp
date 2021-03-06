#define _CRT_SECURE_NO_WARNINGS 1
//【题目描述】小Q有X首长度为A的不同的歌和Y首长度为B的不同的歌，
//现在小Q想用这些歌组成一个总长度正好为K的歌单，每首歌最多只能在歌单中出现一次，
//在不考虑歌单内歌曲的先后顺序的情况下，请问有多少种组成歌单的方法。
//
//输入描述：
//每个输入包含一个测试用例。
//每个测试用例的第一行包含一个整数，表示歌单的总长度K(1 <= K <= 1000)。
//接下来的一行包含四个正整数，
//分别表示歌的第一种长度A(A <= 10)和数量X(X <= 100)以及歌的第二种长度B(B <= 10)和数量Y(Y <= 100)。
//保证A不等于B。
//
//输出描述：
//输出一个整数，表示组成歌单的方法取模。
//因为答案可能会很大，输出对1000000007取模的结果。
//
//输入示例：
//5
//2 3 3 3
//输出示例：
//9

//解题思路：
//以输入示例为例：
//张三的歌时长均为2分钟，有3首不同的，
//李四的歌时长均为3分钟，也有3首不同的。
//要求组成歌单的长度为5分钟
//从取0首张三的歌开始 到取3首张三的歌结束，依次判断可以满足长度为5的组合
//1.取0首张三2分钟的歌，则歌单剩余5分钟-2分钟*0首==5分钟，5分钟/李四3分钟的歌无法满足
//2.取1首张三2分钟的歌，则歌单剩余5分钟-2分钟*1首==3分钟，3分钟/李四3分钟的歌满足，
//张三可以从3首歌中取1首，有三种可能；李四可以从三首歌中取1首，也有三种可能。
//因此张三李四各取一首歌组成5分钟歌单的不同可能有3*3 == 9种可能
//3.取2首张三2分钟的歌，则歌单剩余1分钟，1分钟/李四3分钟的歌无法满足条件；
//4.取3首张三2分钟的歌，超过歌单总数，退出判断。
//将所有的可能的个数加起来即为所求可能数

//问题就在于如何求解从张三的歌中取一首歌时的可能的个数

//初始化二维数组为杨辉三角
//排列组合的C(x,i)的值与杨辉三角对应位置的值相同，
//杨辉三角就是由杨辉整理贾宪的二项式系数而来
//其都有性质C(n, k) = C(n-1, k) + C(n-1, k-1)
//因此只需求出C(x,i)的值与C(y，(k-i)/b)的值，
//然后相乘即得总共的可能数
//取模运算的性质有：
//(a + b) % p == (a % p + b % p) % p
//(a * b) % p == (a % p * b % p) % p

#include <iostream>
#include <cstdio>
using namespace std;
long long c[101][101];
const int mod = 1000000007;
void init()
{
	c[0][0] = 1;
	for (int i = 1; i <= 100; i++)
	{
		c[i][0] = 1;
		for (int j = 1; j <= 100; j++)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
		}
	}
}
int main()
{
	int k, a, b, x, y;
	long long ans = 0;
	init();
	scanf("%d", &k);
	scanf("%d%d%d%d", &a, &x, &b, &y);
	for (int i = 0; i <= x; i++)
	{
		if (i * a <= k && (k - a * i) % b == 0 && (k - a * i) / b <= y)
			ans = (ans + (c[x][i] * c[y][(k - a * i) / b]) % mod) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}