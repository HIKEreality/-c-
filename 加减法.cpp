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
bool operation, ADjust, Bye;//operation�����ж���ִ�мӷ����Ǽ���, adjust��������С��ʱ��ȥ������0, B�ж�����С��ǰ������С����
int sign, t, first, sum, byte;//sign�ж��������Ĵ�С��tִ�н�λ��λ��first�жϵ�һ�����ķ���, byteͳ������λ
int main()
{
	int k;
	cin >> k;
	cin.ignore();//�ѵ�һ�����з��Ե�
	while (k--)
	{
		char ch;
		cin >> ch;
		if (ch == '+') operation = true;
		else operation = false;
		cin.ignore();//�ٳ�һ�����з�
		sign = first = byte = 0;
		ADjust = Bye = false;
		pa = creat();//����a��С����λ�ã�û��С����ͷ������һλ
		int BYTE = byte;
		byte = 0;
		Bye = false;
		pb = creat();//ͬ��
		byte = byte > BYTE ? byte : BYTE;//ͳ�����λ��
		a = pa, b = pb;
		Lplay();//С����ǰ����
		a = pa, b = pb;
		Nplay();//С���������
		carrybit();//��λ��λ
		adjust();//����β����0
		show();//ʲô���ܲ��ö�˵�˰�
	}
	return 0;
}
num* creat()
{
	num* process, * point;
	process = point = NULL;
	char s;
	while (cin.get(s), s != '\n')//�ﵽ���뻻�з����˳���Ŀ�ģ���ϸ�������⻹�Ǿ�������string��
	{
		if (s == '.') ADjust = Bye = true;
		if (!Bye)//С����ǰ����λ��
		{
			if (s == ',') continue;
			else if (s != '-') byte++;
		}
		if (s == '-')//����һ��
		{
			if (!first) first = -1;
			operation = operation ? false : true;
			continue;
		}
		if (!first) first = 1;
		num* n = new num;
		n->next = NULL;
		if (s != '.') n->number = s - 48;
		else n->number = 999;//999��ʾС����
		if (process == NULL)//����
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
	return point;//����С����
}
void Lplay()
{
	if (a->number == 999) a = a->last;
	if (b->number == 999) b = b->last;//������С����ǰһλ
	do
	{
		if (operation) a->number += b->number;
		else a->number -= b->number;//����
		if (a->number < 0) sign = -1;
		if (a->number > 0) sign = 1;//�������ж�˭����λ��Խ�����ȼ�Խ�ߣ����Կ��У���Ϊ�ǴӺ���ǰ��
		if (a->last != NULL && b->last != NULL)
		{
			a = a->last;
			b = b->last;
		}
		else break;
	} while (1);
	if (a->last == NULL && b->last != NULL)//���b������bǰ��һ�ζ�ĸ�a����
	{
		if (!operation) sign = -1;//˵����1��ʾa����-1��ʾb����
		a->last = b->last;
		b->last->next = a;
	}
	else if (a->last != NULL && b->last == NULL) sign = 1;
	if (sign == -1)
		while (a != NULL && a->number != 999)
			a->number *= sign, a = a->next;//���b������ô֮ǰ�����ˣ��˸�-1����һ��
}
void Nplay()
{
	if (a->number == 999) a = a->last;
	if (b->number == 999) b = b->last;//������С����ǰһλ��������С���ĺ���С���Ľ��м�������Ҫ������
	while (a->next != NULL && b->next != NULL)
	{
		a = a->next;
		b = b->next;
		if (a->number == 999) continue;
		if (operation) a->number += b->number;
		else
		{
			a->number -= b->number;
			if (!sign)//�������ֿ��ܶ�һ������ʱ��С���ж�˭����
			{
				if (a->number > 0) sign = 1;
				if (a->number < 0) sign = -1;
			}
			else a->number *= sign;
		}
	}
	if (a->next == NULL && b->next != NULL)
	{
		if (!sign) sign = -1;//b��������ĸ�a��������˳�����д�С
		a->next = b->next;
		b->next->last = a;
	}
	else if (a->next != NULL && b->next == NULL && !sign) sign = 1;//ǰ�涼һ�����жϴ�С
	while (a->next != NULL)
	{
		if (!operation && a->next->number  != 999) a->next->number *= -sign;//ע�������������Ǽ����ķ�������
		a = a->next;
	}
	tail = a;//�õ�������λ��
}
void carrybit()
{
	t = 0;
	while (1)
	{
		if (a->number == 999)//����С����
		{
			a = a->last;
			continue;
		}
		a->number += t, t = 0;
		if (a->number < 0) a->number += 10, t = -1;
		if (a->number > 9) a->number -= 10, t = 1;
		if (a->last != NULL) a = a->last;
		else break;//�򵥵Ľ�λ��λ
	}
}
void adjust()
{
	if (ADjust)//��С�����ٴ���
	{
		while (tail->next == NULL || tail->next->number != 999)
		{
			if (tail->number > 0 && tail->number <= 9) break;
			else tail = tail->last;
		}//ȥ��ĩ��0
	}
	tail = tail->next;//����С�����ⲽ���Ǳ����
}
void show()
{
	bool head = false;
	if (operation && first == -1) cout << "-";
	if (!operation && sign * first == -1) cout << "-";//����Ƿ�Ϊ����������
	if (t == 1)
	{
		byte++;//λ����һ
		cout << t;//����һλ�����
	}
	while (a != tail)
	{
		if (a->number != 0) head = true;
		if (t || head)
		{
			if (a->number != 999) cout << a->number;//head��tͬʱ��������ȥ��ǰ��0
			else cout << '.'; 
			if ((byte - 1) % 3 == 0 && (byte - 1 > 0)) cout << ',';//������ţ�����һ��Ҫ��ȥ����ǰ��0��
		}
		else if (a->next != NULL && a->next->number == 999) cout << a->number;
		byte--;
		a = a->next;
	}
	cout << endl;
}