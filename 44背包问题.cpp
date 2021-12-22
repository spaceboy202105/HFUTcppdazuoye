#include<iostream>
#include "44背包问题.h"
#include<algorithm>
#include<iomanip>
using namespace std;
int max_result[3] = { 0,0,0 };
struct Item
{
	int value = 0;
	int weight = 0;
};//创建物品类

void core_algorithm1(int, int, Item*, int**);
void printtable(int item_num, int bag_size, int** ptable, int*);
void init(int, int, Item*);
void findwhat(int& a, int** ptable, int& b, int* resultlist, Item* pitem);

int main() {
	int bag_size, item_num;
	cin >> bag_size >> item_num;
	Item* pitem = new Item[item_num + 1];//创建物品表
	int* resultlist = new int[item_num + 1];
	init(bag_size, item_num, pitem);

	int** ptable = new int* [item_num + 1];
	for (size_t i = 0; i < item_num + 1; i++)
	{
		ptable[i] = new int[bag_size + 1];
	}//创建规划表

	core_algorithm1(item_num, bag_size, pitem, ptable);//生成规划表

	printtable(item_num, bag_size, ptable, resultlist);//打印规划表

	int a = max_result[0], b = max_result[1];
	findwhat(a, ptable, b, resultlist, pitem);//回溯找到最优解

	for (size_t i = 1; i <= max_result[0]; i++)//打印物品使用情况
	{
		cout << "第" << i << "个物品的情况为：" << resultlist[i] << " (1：取了该物品，0：没有取该物品)" << endl;
	}
	cout << "最大价值为：" << max_result[2] << endl;
	for (size_t i = 0; i < item_num + 1; i++)//释放内存
	{
		delete[]ptable[i];
	}
	delete[]ptable;//释放内存
	delete[]pitem;
	delete[]resultlist;
	return 0;
}

void findwhat(int& a, int** ptable, int& b, int* resultlist, Item* pitem)
{
	while (a > 0)
	{
		if (ptable[a][b] == ptable[a - 1][b])
		{
			cout << "a: " << a << "b: " << b << endl;
			resultlist[a] = 0;
			a = a - 1;
		}
		else if ((b - pitem[a].weight >= 0) && (ptable[a][b] == ptable[a - 1][b - pitem[a].weight] + pitem[a].value))
		{
			cout << "a: " << a << "b: " << b << endl;
			resultlist[a] = 1;
			b = b - pitem[a].weight;
			a = a - 1;
		}
	}
}
void init(int bag_size, int item_num, Item* pitem)
{
	//创建一个背包类,需要多创建一个位置以存储骑兵点（0,0）
		//pitem[0] = { 0 };
	for (size_t i = 1; i < item_num + 1; i++)
	{

		cin >> pitem[i].weight >> pitem[i].value;//输入基本属性
	}
	//pitem = NULL;
}

void core_algorithm1(int item_num, int bag_size, Item* pitem, int** ptable)
{
	for (size_t i = 0; i < item_num + 1; i++)
	{
		for (size_t j = 0; j < bag_size + 1; j++)
		{
			ptable[i][j] = 0;
		}
	}
	//向前迭代：分以下几种情况
	//1.装不下第i个物品，复读上一个价值
	//2.能装第i个物品，有两种情况
	//a.装但是没必要，所以复读第个
	//b.装第i个，所以在第i-1个加第i个
	for (size_t i = 1; i < item_num + 1; i++)
	{
		for (size_t j = 1; j < bag_size + 1; j++)
		{
			if (j < pitem[i].weight)
			{
				ptable[i][j] = ptable[i - 1][j];
			}
			else
			{
				ptable[i][j] = max(ptable[i - 1][j], ptable[i - 1][j - pitem[i].weight] + pitem[i].value);//
			}
		}
	}
	//ptable = NULL;
}
void printtable(int item_num, int bag_size, int** ptable, int* r)
{
	cout << "动态规划表为: " << endl;
	for (int i = 0; i < item_num + 1; i++)
	{
		for (int j = 0; j < bag_size + 1; j++)
		{
			cout << setw(2) << ptable[i][j] << " ";
			if (ptable[i][j] >= max_result[2])
			{
				max_result[0] = i;
				max_result[1] = j;
				max_result[2] = ptable[i][j];
			}
		}
		cout << endl;
	}
}