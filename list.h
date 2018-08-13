#include <iostream>
using namespace std;
 
template<class T>
struct ListNode
{
	ListNode(const T& data = T())
	: _pPre(0)
	, _pNext(0)
	, _data(data)
	{}
 
	ListNode* _pPre;
	ListNode* _pNext;
	T _data;
};
 
//迭代器
template <class T,class Ref,class Pointer>
class ListIterator
{
	typedef ListIterator Self;
public:
	ListIterator()
		: _pCur(0)
	{}
 
	ListIterator(ListNode<T>* pCur)
		: _pCur(pCur)
	{}
 
	ListIterator(const Self& s)
		: _pCur(s._pCur)
	{}
 
	Ref operator*()
	{
		return _pCur->_data;
	}
 
	Ref operator->()
	{
		/*return &(operator*());*/
		return &(_pCur->_data); 
	}
 
	Self& operator++()//前置++
	{
		_pCur = _pCur->_pNext;
		return*this;
	}
 
	Self operator++(int)//后置++
	{
		Self temp(*this);
		_pCur = _pCur->_pNext;
		return temp;
	}
 
	Self& operator--()//前置--
	{
		_pCur = _pCur->_pPre;
		return*this;
	}
 
	Self operator--(int)//后置--
	{
		Self temp(*this);
		_pCur = _pCur->_pPre;
		return temp;
	}
 
	bool operator!=(const Self& s)
	{
		return _pCur != s._pCur;
	}
 
	bool operator==(const Self& s)
	{
		return _pCur == s._pCur;
	}
 
	ListNode<T>* _pCur;
};
 
template <class T>
class List
{
public:
	typedef ListIterator<T,T&,T*> Iterator;
	typedef ListNode<T>* Node;
public:
	List()
		: _pHead(new ListNode<T>)
	{
		_pHead->_pNext = _pHead;//头结点
		_pHead->_pPre = _pHead;
	}
 
	List(const T* array, size_t size)
		:_pHead(new ListNode<T>)
	{
		_pHead->_pNext = _pHead;//头结点
		_pHead->_pPre = _pHead;
 
		for (size_t i = 0; i < size; ++i)
		{
			PushBack(array[i]);
		}
	}
	List(const List& l)//拷贝构造
		:_pHead(new ListNode<T>)
	{
		_pHead->_pNext = _pHead;//头结点
		_pHead->_pPre = _pHead;
		Node first = l._pHead->_pNext;
	
		while (first != l._pHead->_pPre)
		{
			PushBack(first->_data);
			first = first->_pNext;
		}
	}
	List& operator=(const List& l)
	{
		if (this != &l)
		{
			_pHead = l._pHead;
			Iterator it = Begin();
			while (it != End())
			{
				Insert(it);
				it++;
			}
		}
	}
	~List()
	{
		Clear();
		delete _pHead;
		_pHead = NULL;
	}
 
	///////////////////////////////////////////////////////
	Iterator Begin()
	{
		return Iterator(_pHead->_pNext);
	}
 
	Iterator End()
	{
		return Iterator(_pHead);
	}
	/////////////////////Modify////////////////////////// 
	void PushBack(const T& data)
	{
		Node pTail = _pHead->_pPre;//尾指针
		Node pNewNode = new ListNode<T>(data);
		if (Empty())//空链表
		{
			_pHead->_pNext = pNewNode;
			pNewNode->_pNext = _pHead;
			_pHead->_pPre = pNewNode;
			pNewNode->_pPre = _pHead;
		}
		else//链表非空
		{
			Node pTail = _pHead->_pPre;//尾指针
 
			pTail->_pNext = pNewNode;
			pNewNode->_pPre = pTail;
			_pHead->_pPre = pNewNode;
			pNewNode->_pNext = _pHead;
		}
 
	}
	void PopBack()
	{
		if (Empty())
			return;
		else
		{
			Node pTail = _pHead->_pPre;//尾指针
			pTail = _pHead->_pPre->_pPre;
			delete pTail->_pNext;
			pTail->_pNext = _pHead;
			_pHead->_pPre = pTail;
 		}
	}
	void PushFront(const T& data)
	{
		Node pTail = _pHead->_pPre;//尾指针
		Node pNewNode = new ListNode<T>(data);
		pNewNode->_pNext = _pHead->_pNext;
		pNewNode->_pPre = _pHead;
		_pHead->_pNext->_pPre = pNewNode;
		_pHead->_pNext = pNewNode;
	}
	void PopFront()
	{
		if (Empty())
			return;
		else
		{
			Node tmp = _pHead->_pNext;
			_pHead->_pNext = tmp->_pNext;
			tmp->_pNext->_pPre = _pHead;
			delete tmp;
		}
	}
	Iterator Insert(Iterator pos, const T& data)
	{
		Node pNewNode = new ListNode<T>(data);
		pNewNode->_pNext = pos._pCur;
		pNewNode->_pPre = pos._pCur->_pPre;
		pos._pCur->_pPre->_pNext = pNewNode;
		pos._pCur->_pPre = pNewNode;
		return Iterator(pNewNode);
	}
	Iterator Erase(Iterator pos)
	{
		Node next = pos._pCur->_pNext;
		pos._pCur->_pPre->_pNext = pos._pCur->_pNext;
		pos._pCur->_pNext->_pPre = pos._pCur->_pPre;
		delete pos._pCur;
 
		return Iterator(next);
	}
	bool Empty()const
	{
		if (_pHead->_pNext == _pHead)
			return true;
		else
			return false;
	}
	size_t Size()const
	{
		int cout = 0;
		Node pnext = _pHead;
		Node pTail = _pHead->_pPre;
		while (pnext != pTail)
		{
			cout++;
			pnext = pnext->_pNext;
		}
	}
	T& Front()
	{
		return _pHead->_pNext->_data;
	}
	const T& Front()const
	{
		return _pHead->_pNext->_data;
	}
	T& Back()
	{
		return _pHead->_pPre->_data;
	}
	const T& Back()const
	{
		return _pHead->_pPre->_data;
	}
	void Clear()
	{
		Iterator it = Begin();
 
		while (it != End())
		{
			it = Erase(it);
		}
		_pHead->_pNext = _pHead;
		_pHead->_pPre = _pHead;
	}
private:
	ListNode<T>* _pHead;
};
