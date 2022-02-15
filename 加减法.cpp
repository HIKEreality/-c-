#include <iostream>
#include <string>
using namespace std;
struct num
{
	int number;
	num* last;
	num* next;
};
num* a, * b, *pa, *pb, *tail;
num* creat();
void Lplay(), Nplay(), carrybit(), adjust(), show();
bool operation, ADjust, Bye;//operation用来判断是执行加法还是减法, adjust处理在无小数时不去除后置0, B判断是在小数前还是在小数后
int sign, t, first, sum, byte;//sign判断两个数的大小，t执行进位借位，first判断第一个数的符号, byte统计整数位
int main()
{
	int k;
	cin >> k;
	cin.ignore();//把第一个换行符吃掉
	while (k--)
	{
		char ch;
		cin >> ch;
		if (ch == '+') operation = true;
		else operation = false;
		cin.ignore();//再吃一个换行符
		sign = first = byte = 0;
		ADjust = Bye = false;
		pa = creat();//返回a的小数点位置，没有小数点就返回最后一位
		int BYTE = byte;
		byte = 0;
		Bye = false;
		pb = creat();//同上
		byte = byte > BYTE ? byte : BYTE;//统计最大位数
		a = pa, b = pb;
		Lplay();//小数点前运算
		a = pa, b = pb;
		Nplay();//小数点后运算
		carrybit();//进位借位
		adjust();//处理尾部的0
		show();//什么功能不用多说了吧
	}
	return 0;
}
num* creat()
{
	num* process, * point;
	process = point = NULL;
	char s;
	while (cin.get(s), s != '\n')//达到输入换行符就退出的目的（仔细斟酌题意还是决定不用string）
	{
		if (s == '.') ADjust = Bye = true;
		if (!Bye)//小数点前计算位数
		{
			if (s == ',') continue;
			else if (s != '-') byte++;
		}
		if (s == '-')//处理一下
		{
			if (!first) first = -1;
			operation = operation ? false : true;
			continue;
		}
		if (!first) first = 1;
		num* n = new num;
		n->next = NULL;
		if (s != '.') n->number = s - 48;
		else n->number = 999;//999表示小数点
		if (process == NULL)//连接
		{
			process = n;
			process->last = NULL;
		}
		else
		{
			process->next = n;
			n->last = process;
			process = n;
		}
		if (process->number == 999) point = process;
	}
	if (point == NULL) point = process;
	return point;//返回小数点
}
void Lplay()
{
	if (a->number == 999) a = a->last;
	if (b->number == 999) b = b->last;//保持在小数点前一位
	do
	{
		if (operation) a->number += b->number;
		else a->number -= b->number;//开算
		if (a->number < 0) sign = -1;
		if (a->number > 0) sign = 1;//过程中判断谁更大，位数越高优先级越高，所以可行，因为是从后往前的
		if (a->last != NULL && b->last != NULL)
		{
			a = a->last;
			b = b->last;
		}
		else break;
	} while (1);
	if (a->last == NULL && b->last != NULL)//如果b更长把b前面一段多的给a接上
	{
		if (!operation) sign = -1;//说明：1表示a更大，-1表示b更大
		a->last = b->last;
		b->last->next = a;
	}
	else if (a->last != NULL && b->last == NULL) sign = 1;
	if (sign == -1)
		while (a != NULL && a->number != 999)
			a->number *= sign, a = a->next;//如果b更大，那么之前减错了，乘个-1调整一下
}
void Nplay()
{
	if (a->number == 999) a = a->last;
	if (b->number == 999) b = b->last;//调整到小数点前一位，便于有小数的和无小数的进行计算所需要的连接
	while (a->next != NULL && b->next != NULL)
	{
		a = a->next;
		b = b->next;
		if (a->number == 999) continue;
		if (operation) a->number += b->number;
		else
		{
			a->number -= b->number;
			if (!sign)//整数部分可能都一样，这时从小数判断谁更大
			{
				if (a->number > 0) sign = 1;
				if (a->number < 0) sign = -1;
			}
			else a->number *= sign;
		}
	}
	if (a->next == NULL && b->next != NULL)
	{
		if (!sign) sign = -1;//b更长，多的给a连起来，顺便判判大小
		a->next = b->next;
		b->next->last = a;
	}
	else if (a->next != NULL && b->next == NULL && !sign) sign = 1;//前面都一样，判断大小
	while (a->next != NULL)
	{
		if (!operation && a->next->number  != 999) a->next->number *= -sign;//注意接起来后如果是减法的符号问题
		a = a->next;
	}
	tail = a;//得到最后面的位置
}
void carrybit()
{
	t = 0;
	while (1)
	{
		if (a->number == 999)//跳过小数点
		{
			a = a->last;
			continue;
		}
		a->number += t, t = 0;
		if (a->number < 0) a->number += 10, t = -1;
		if (a->number > 9) a->number -= 10, t = 1;
		if (a->last != NULL) a = a->last;
		else break;//简单的进位借位
	}
}
void adjust()
{
	if (ADjust)//有小数点再处理
	{
		while (tail->next == NULL || tail->next->number != 999)
		{
			if (tail->number > 0 && tail->number <= 9) break;
			else tail = tail->last;
		}//去除末置0
	}
	tail = tail->next;//有无小数点这步都是必需的
}
void show()
{
	bool head = false;
	if (operation && first == -1) cout << "-";
	if (!operation && sign * first == -1) cout << "-";//结果是否为负数的条件
	if (t == 1)
	{
		byte++;//位数加一
		cout << t;//多了一位先输出
	}
	while (a != tail)
	{
		if (a->number != 0) head = true;
		if (t || head)
		{
			if (a->number != 999) cout << a->number;//head和t同时可以用来去除前置0
			else cout << '.'; 
			if ((byte - 1) % 3 == 0 && (byte - 1 > 0)) cout << ',';//输出逗号，并且一定要在去除了前置0后
		}
		else if (a->next != NULL && a->next->number == 999) cout << a->number;
		byte--;
		a = a->next;
	}
	cout << endl;
}