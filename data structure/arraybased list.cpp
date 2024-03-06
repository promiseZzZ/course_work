#include<iostream>
#include<assert.h>
using namespace std;
template <typename E> class List
{
private:
	void operator =(const List&)
	{
	}
	//保护复制构造函数
	List(const List&)
	{
	}
public:
	//默认构造函数
	List() 
	{}
	//基类析构函数
	virtual ~List() 
	{}
	//清除掉list中的内容，使其成为空表
	virtual void clear()= 0;//"=0"将函数设置为pure virtual
	//在List的当前位置插入元素item
	virtual void insert(const E& item) = 0;
	//在表尾增加元素item
	virtual void append(const E& item) = 0;
	//移除当前位置的元素，并返回其值
	virtual E remove() = 0;
	//将当前位置移动到表头
	virtual void moveToStart() = 0;
	//将当前位置移动到表尾
	virtual void moveToEnd() = 0;
	//将当前位置左移一位（如果在表头则不移动）
	virtual void previous() = 0;
	//将当前位置右移一位（如果在表尾则不移动）
	virtual void next() = 0;
	//返回当前线性表元素个数
	virtual int length() const = 0;
	//返回当前元素的位置
	virtual int currPosition()const = 0;
	//设置当前位置至Pos
	virtual void moveToPosition(int Pos) = 0;
	//返回当前元素
	virtual const E& getValue() const = 0;

};

template <typename E> class AList : public List<E> {
private:
	int maxSize;//list的最大size
	int listSize;//当前list中元素数目
	int curr;//当前元素的位置
	E* listArray;//容纳list元素的数组
public:
	AList(int size)//构造函数（若没给出任何参数，则取值DefaultSize）
	{
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}
	~AList()//析构函数
	{
		delete[] listArray;
	}
	void clear()//重新初始化list
	{
		delete[] listArray;//删除数组
		listSize = curr = 0;//重新设置size
		listArray = new E[maxSize];//重新创建数组
	}
	void insert(const E& it) //在当前位置插入it
	{
		assert(listSize < maxSize, "List capacity exceeded");//判断listSize是否超出限制
		for (int i = listSize; i > curr; i--)//将插入位置后的所有元素后移，腾出空间
		{
			listArray[i] = listArray[i - 1];
		}
		listArray[curr] = it;
		listSize++;//将listSize增大
	}
	void append(const E& it)//在表尾增加元素it
	{
		assert(listSize < maxSize, "List capacity exceeded");
		listArray[listSize] = it;
		listSize++;//先增加元素，再将listSize增大
	}
	E remove()//移除当前位置的元素，并返回其值
	{
		assert((curr >= 0) && (curr < listSize), "No element");//判断当前位置是否在数组中
		E it = listArray[curr];
		for (int i = curr; i < listSize - 1; i++)//将插入位置后的所有元素后移
		{
			listArray[i] = listArray[i + 1];
		}
		listSize--;//将listSize减小
		return it;
	}
	void moveToStart()
	{
		curr = 0;
	}
	void moveToEnd()
	{
		curr = listSize;
	}
	void previous()
	{
		if (curr != 0)
		{
			curr--;
		}
	}
	void next()
	{
		if (curr < listSize)
		{
			curr++;
		}
	}
	int length() const
	{
		return listSize;
	}
	int currPosition()const
	{
		return curr;
	}
	void moveToPosition(int Pos)
	{
		assert((Pos >= 0) && (Pos <= listSize), "Pos out of range");
		curr = Pos;
	}
	const E& getValue() const
	{
		assert((curr >= 0) && (curr <= listSize), "No current element");
		return listArray[curr];
	}
	void swap()
	{
		assert((curr >= 0) && (curr < listSize), "No two elements on the right");
		int temp = listArray[curr];
		listArray[curr] = listArray[curr + 1];
		listArray[curr + 1] = temp;
	}
};
template<typename E>class Link
{
public:
	E element;
	Link* next;
	Link(const E& elemval, Link* nextval = NULL)
	{
		element = elemval;
		next = nextval;
	}
	Link(Link* nextval = NULL)
	{
		next = nextval;
	}

};
template<typename E> class LList :public List<E>
{
private:
	Link<E>* head;//指向表头的指针
	Link<E>* tail;//指向表尾的指针
	Link<E>* curr;//指向当前位置的指针
	int cnt;//list的size
	void init()//初始化list
	{
		curr = tail = head = new Link<E>;
		cnt = 0;
	}
	void removeall()
	{
		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	LList(int size = 100)

	{
		init();
	}
	~LList()
	{
		removeall();
	}
	void print() 
	{	
		curr = head->next;
		while (curr!=NULL)
		{
			cout << curr->element << " ";
			curr = curr->next;
		}
	}//输出list内容
	void clear()//清除list
	{
		removeall();
		init();
	}
	void insert(const E& it)
	{
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr)
		{
			tail = curr->next;//新tail
			cnt++;
		}
	}
	void append(const E& it)
	{
		tail = tail->next = new Link<E>(it, NULL);
		cnt++;
	}
	E remove()
	{
		assert(curr->next != NULL, "No element");
		E it = curr->next->element;//记住值
		Link<E>* ltemp = curr->next;//记住link node
		if (tail == curr->next)//重新设置tail
		{
			tail = curr;
		}
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}
	void moveToStart()
	{
		curr = head;
	}
	void moveToEnd()
	{
		curr = tail;
	}
	void previous()
	{
		if (curr == head)//前面没有元素
		{
			return;
		}
		Link<E>* temp = head;
		while (temp->next != curr)
		{
			temp = temp->next;
			curr = temp;
		}
	}
	void next()
	{
		if (curr != tail)
		{
			curr = curr->next;
		}
	}
	int length() const
	{
		return cnt;
	}
	int currPosition() const
	{
		Link<E>* temp = head;
		int i;
		for (i = 0; curr != temp; i++)
		{
			temp = temp->next;
		}
		return i;
	}
	void moveToPosition(int Pos)
	{
		assert((Pos >= 0) && (Pos <= cnt), "position out of range");
		curr = head;
		for (int i = 0; i < Pos; i++)
		{
			curr = curr->next;
		}
	}
	const E& getValue() const
	{
		assert(curr->next != NULL, "No value");
		return curr->next->element;
	}
	
};



void function1()
{
	AList<int> L1(20);
	L1.append(2);
	L1.append(23);
	L1.append(15);
	L1.append(5);
	L1.append(9);
	L1.moveToStart();
	L1.next();
	L1.next();
	L1.remove();
	for (L1.moveToStart(); L1.currPosition() < L1.length(); L1.next())
	{
		int it = L1.getValue();
		cout << it << " ";
	}
}
void function2()
{
	AList<int> L2(20);
	L2.append(2);
	L2.append(23);
	L2.append(15);
	L2.append(5);
	L2.append(9);
	for (L2.moveToStart(); L2.currPosition() < L2.length(); L2.next())
	{
		int it = L2.getValue();
		cout << it << " ";
	}
}
void function3(int position)
{
	AList<int> L3(20);
	L3.append(2);
	L3.append(23);
	L3.append(15);
	L3.append(5);
	L3.append(9);
	L3.moveToPosition(position);
	L3.swap();
	for (L3.moveToStart(); L3.currPosition() < L3.length(); L3.next())
	{
		int it = L3.getValue();
		cout << it << " ";
	}
}
void merge(LList<int>& list1, LList<int>& list2)
{
	LList<int> list3(list1.length() + list2.length());
	list1.moveToStart();
	list2.moveToStart();
	list3.moveToStart();
	while (list1.currPosition() < list1.length() && list2.currPosition() < list2.length())
	{
		if (list1.getValue() <= list2.getValue())
		{
			list3.append(list1.getValue());
			list1.next();
		}
		else
		{
			list3.append(list2.getValue());
			list2.next();
		}
	}
	while (list1.currPosition()<list1.length())
	{
		list3.append(list1.getValue());
		list1.next();
	}
	while (list2.currPosition() < list2.length())
	{
		list3.append(list2.getValue());
		list2.next();
	}
	list3.print();
}
void function4()
{
	LList<int> test1(3);
	test1.append(0);
	test1.append(2);
	test1.append(4);
	for (test1.moveToStart() ; test1.currPosition() <test1.length(); test1.next())
	{
		cout << test1.getValue() << " ";
	}
	cout << endl;
	LList<int> test2(3);
	test2.append(1);
	test2.append(3);
	test2.append(5);
	for (test2.moveToStart(); test2.currPosition() < test2.length(); test2.next())
	{
		cout << test2.getValue() << " ";
	}
	cout << endl;
	merge(test1, test2);
}


int main(void)
{
	//function1();
	//function2();
	//function3(2);
	function4();
	system("pause");
	return 0;
}