#include<iostream>
#include "44��������.h"
#include<algorithm>
#include<iomanip>
using namespace std;
int max_result[3] = { 0,0,0 };
struct Item
{
	int value = 0;
	int weight = 0;
};//������Ʒ��

void core_algorithm1(int, int, Item*, int**);
void printtable(int item_num, int bag_size, int** ptable, int*);
void init(int, int, Item*);
void findwhat(int& a, int** ptable, int& b, int* resultlist, Item* pitem);

int main() {
	int bag_size, item_num;
	cin >> bag_size >> item_num;
	Item* pitem = new Item[item_num + 1];//������Ʒ��
	int* resultlist = new int[item_num + 1];
	init(bag_size, item_num, pitem);

	int** ptable = new int* [item_num + 1];
	for (size_t i = 0; i < item_num + 1; i++)
	{
		ptable[i] = new int[bag_size + 1];
	}//�����滮��

	core_algorithm1(item_num, bag_size, pitem, ptable);//���ɹ滮��

	printtable(item_num, bag_size, ptable, resultlist);//��ӡ�滮��

	int a = max_result[0], b = max_result[1];
	findwhat(a, ptable, b, resultlist, pitem);//�����ҵ����Ž�

	for (size_t i = 1; i <= max_result[0]; i++)//��ӡ��Ʒʹ�����
	{
		cout << "��" << i << "����Ʒ�����Ϊ��" << resultlist[i] << " (1��ȡ�˸���Ʒ��0��û��ȡ����Ʒ)" << endl;
	}
	cout << "����ֵΪ��" << max_result[2] << endl;
	for (size_t i = 0; i < item_num + 1; i++)//�ͷ��ڴ�
	{
		delete[]ptable[i];
	}
	delete[]ptable;//�ͷ��ڴ�
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
	//����һ��������,��Ҫ�ഴ��һ��λ���Դ洢����㣨0,0��
		//pitem[0] = { 0 };
	for (size_t i = 1; i < item_num + 1; i++)
	{

		cin >> pitem[i].weight >> pitem[i].value;//�����������
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
	//��ǰ�����������¼������
	//1.װ���µ�i����Ʒ��������һ����ֵ
	//2.��װ��i����Ʒ�����������
	//a.װ����û��Ҫ�����Ը����ڸ�
	//b.װ��i���������ڵ�i-1���ӵ�i��
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
	cout << "��̬�滮��Ϊ: " << endl;
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