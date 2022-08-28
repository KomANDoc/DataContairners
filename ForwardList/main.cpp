#include <iostream>
using namespace std;

class ForwardList;

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;

	int get_data()const
	{
		return Data;
	}
};
int Element::count = 0;





class ForwardList
{
	Element* Head;//голова списка указывает на его начальный элемент 
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr; //Если список пуст, то голова указывает на 0
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	/////// get-method
	
	Element* get_head()const
	{
		return Head;
	}


	/////// Adding elements:
	void push_front(int Data)
	{
		//Element* New = new Element(Data);
		//New->pNext = Head;
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//Element* New = ;
		Element* Temp = Head;
		while (Temp->pNext!= nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		//Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1;i++) Temp = Temp->pNext;
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	/////// Erasing elements
	
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1;i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}
	/////// Methods
	void print()const
	{
		/*
		Element* Temp = Head;	//Temp - итератор
		while (Temp)			//Итератор - указатель, при помощи которого 
		{						//можно получить доступ к элементам структур данных
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	/////// Operator
	ForwardList operator= (const ForwardList other)
	{
		int* arr = new int[other.size];
		Element* Temp = other.Head;
		for (int i = 0; i < size;i++)
		{
			arr[i] = Temp->Data;
			Temp = Temp->pNext;
			this->push_front(arr[i]);
		}
		delete[] arr;
	}
};


//#define BASE_CHECK
//#define RANGE_BESED_FOR_ARRAY

void main()
{
	setlocale(LC_ALL, "RU");
#ifdef BASE_CHECK
	int n;
	cout << "Ввудите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
#endif // BASE_CHECK

#ifdef RANGE_BESED_FOR_ARRAY


	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;


	//Range-based for - фор для контейнеров
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // 

	ForwardList list5 = { 3,5,8,13,21 };
	list5.print();
}
