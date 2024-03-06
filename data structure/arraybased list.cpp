#include<iostream>
#include<assert.h>
using namespace std;
template <typename E> class List
{
private:
	void operator =(const List&)
	{
	}
	//�������ƹ��캯��
	List(const List&)
	{
	}
public:
	//Ĭ�Ϲ��캯��
	List() 
	{}
	//������������
	virtual ~List() 
	{}
	//�����list�е����ݣ�ʹ���Ϊ�ձ�
	virtual void clear()= 0;//"=0"����������Ϊpure virtual
	//��List�ĵ�ǰλ�ò���Ԫ��item
	virtual void insert(const E& item) = 0;
	//�ڱ�β����Ԫ��item
	virtual void append(const E& item) = 0;
	//�Ƴ���ǰλ�õ�Ԫ�أ���������ֵ
	virtual E remove() = 0;
	//����ǰλ���ƶ�����ͷ
	virtual void moveToStart() = 0;
	//����ǰλ���ƶ�����β
	virtual void moveToEnd() = 0;
	//����ǰλ������һλ������ڱ�ͷ���ƶ���
	virtual void previous() = 0;
	//����ǰλ������һλ������ڱ�β���ƶ���
	virtual void next() = 0;
	//���ص�ǰ���Ա�Ԫ�ظ���
	virtual int length() const = 0;
	//���ص�ǰԪ�ص�λ��
	virtual int currPosition()const = 0;
	//���õ�ǰλ����Pos
	virtual void moveToPosition(int Pos) = 0;
	//���ص�ǰԪ��
	virtual const E& getValue() const = 0;

};

template <typename E> class AList : public List<E> {
private:
	int maxSize;//list�����size
	int listSize;//��ǰlist��Ԫ����Ŀ
	int curr;//��ǰԪ�ص�λ��
	E* listArray;//����listԪ�ص�����
public:
	AList(int size)//���캯������û�����κβ�������ȡֵDefaultSize��
	{
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}
	~AList()//��������
	{
		delete[] listArray;
	}
	void clear()//���³�ʼ��list
	{
		delete[] listArray;//ɾ������
		listSize = curr = 0;//��������size
		listArray = new E[maxSize];//���´�������
	}
	void insert(const E& it) //�ڵ�ǰλ�ò���it
	{
		assert(listSize < maxSize, "List capacity exceeded");//�ж�listSize�Ƿ񳬳�����
		for (int i = listSize; i > curr; i--)//������λ�ú������Ԫ�غ��ƣ��ڳ��ռ�
		{
			listArray[i] = listArray[i - 1];
		}
		listArray[curr] = it;
		listSize++;//��listSize����
	}
	void append(const E& it)//�ڱ�β����Ԫ��it
	{
		assert(listSize < maxSize, "List capacity exceeded");
		listArray[listSize] = it;
		listSize++;//������Ԫ�أ��ٽ�listSize����
	}
	E remove()//�Ƴ���ǰλ�õ�Ԫ�أ���������ֵ
	{
		assert((curr >= 0) && (curr < listSize), "No element");//�жϵ�ǰλ���Ƿ���������
		E it = listArray[curr];
		for (int i = curr; i < listSize - 1; i++)//������λ�ú������Ԫ�غ���
		{
			listArray[i] = listArray[i + 1];
		}
		listSize--;//��listSize��С
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
	Link<E>* head;//ָ���ͷ��ָ��
	Link<E>* tail;//ָ���β��ָ��
	Link<E>* curr;//ָ��ǰλ�õ�ָ��
	int cnt;//list��size
	void init()//��ʼ��list
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
	}//���list����
	void clear()//���list
	{
		removeall();
		init();
	}
	void insert(const E& it)
	{
		curr->next = new Link<E>(it, curr->next);
		if (tail == curr)
		{
			tail = curr->next;//��tail
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
		E it = curr->next->element;//��סֵ
		Link<E>* ltemp = curr->next;//��סlink node
		if (tail == curr->next)//��������tail
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
		if (curr == head)//ǰ��û��Ԫ��
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