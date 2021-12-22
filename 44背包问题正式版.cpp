#include<iostream>
#include "44背包问题.h"
#include<algorithm>
#include<iomanip>
using namespace std;
int max_result[3] = { 0,0,0 };//储存三元组的最大值
template<class T>
struct Item
{
	T value = 0;
	T weight = 0;
};//创建物品类

void core_algorithm1(int, int, Item<int>*, int**);
void core_algorithm1(int, int, Item<double>*, int**);
void printtable(int item_num, int bag_size, int** ptable, int*);
void init(int, int, Item<int>*);
void init(int, int, Item<double>*);
void findwhat(int& a, int** ptable, int& b, int* resultlist, Item<int>* pitem);
void findwhat(int& a, int** ptable, int& b, int* resultlist, Item<double>* pitem);
void printmeum();

int main() {
	while (true)
	{
		printmeum();
		int bag_size, item_num;
		cout << "输入背包大小：";
		cin >> bag_size;
		cout << "输入物品数量：";
		cin >> item_num;
		cout << "请问您的数据中是否有浮点数？（1：是/任意键：不是）" << endl;
		int k;
		cin >> k;
		if (k == 1)
		{
			cout << "抱歉，功能尚未开发完成" << endl;
		}
		else
		{
			Item<int>* pitem = new Item<int>[item_num + 1];//创建物品表
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
				cout << "第" << i << R"(个物品的情况为：)" << resultlist[i] << " (1：取了该物品，0：没有取该物品)" << endl;
			}
			cout << "最大价格为：" << max_result[2] << endl;
			for (size_t i = 0; i < item_num + 1; i++)//释放内存
			{
				delete[]ptable[i];
			}
			delete[]ptable;//释放内存
			delete[]pitem;
			delete[]resultlist;
			cout << "请问要不再来一题：（y|n）" << endl;
			char flag;
			cin >> flag;
			if (flag != 'y' && flag != 'Y')
			{
				return 0;
			}
		}
	}

	//return 0;
}
void printmeum()
{
	cout << "*********************************************************************" << endl;
	cout << "                          一个01背包问题                             " << endl;
	cout << "                  作者：吴靖宇	学号：2020211442                      " << endl;
	cout << "*********************************************************************" << endl;
}

void findwhat(int& a, int** ptable, int& b, int* resultlist, Item<int>* pitem)
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
			cout << "a: " << a << " b: " << b << endl;
			resultlist[a] = 1;
			b = b - pitem[a].weight;
			a = a - 1;
		}
	}
}
void init(int bag_size, int item_num, Item<int>* pitem)
{
	//创建一个背包类,需要多创建一个位置以存储骑兵点（0,0）
		//pitem[0] = { 0 };
	for (size_t i = 1; i < item_num + 1; i++)
	{
		cout << "请输入第" << i << "个物品的价值：" << endl;
		cin >> pitem[i].value;
		cout << "并输入它的重量：" << endl;
		cin >> pitem[i].weight;//输入基本属性
	}
	//for (size_t i = 1; i < item_num + 1; i++)
	//{
	//	if (i%1!=0)
	//	{
	//
	//	}
	//	for (size_t j = 1; j < item_num + 1; j++)
	//	{
	//	}
	//}
	//pitem = NULL;
}
void core_algorithm1(int item_num, int bag_size, Item<int>* pitem, int** ptable)
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
			if (ptable[i][j] >= max_result[2]) //寻找最优结果
			{
				max_result[0] = i;
				max_result[1] = j;
				max_result[2] = ptable[i][j];
			}
		}
		cout << endl;
	}
}