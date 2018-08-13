#include "list.h"
 
void test()
{
	int array[] = { 0, 1, 2, 3, 4 };
	List<int> l(array, sizeof(array) / sizeof(array[0]));
 
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
 
	l.PopFront();
	it = l.Begin();
	while (it != l.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
	l.PopBack();
	it = l.Begin();
	while (it != l.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
	l.PopFront();
	it = l.Begin();
	while (it != l.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
 
	
}
void test2()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(1);
	l.PushBack(1);
	l.PushBack(1);
	l.PushBack(1);
 
	List<int> L1(l);
 
	List<int>::Iterator it = L1.Begin();
	while (it != L1.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
 
	List<int> L2 = L1;
	it = L1.Begin();
	while (it != L1.End())
	{
		cout << *it << "->";
		++it;
	}
	cout << endl;
 
}
 
int main()
{
	test2();
	system("pause:");
	return 0;
}
