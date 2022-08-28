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

	const int& get_data()const
	{
		return Data;
	}
	Element* get_pNext()const
	{
		return pNext;
	}
};
int Element::count = 0;



class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ITConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ITDestructor:\t" << this << endl;
	}

	// Operators

	Iterator operator++()
	{
		Temp = Temp->get_pNext();
		return *this;
	}
	bool operator== (const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!= (const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->get_data();
	}
};




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
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other);
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
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	/////// Operator
	ForwardList& operator= (const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		return *this;
	}
	ForwardList& operator= (ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;

		other.Head = nullptr;
		other.size = 0;
		return *this;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	for (Element* Temp = right.get_head(); Temp; Temp = Temp->get_pNext())
		cat.push_back(Temp->get_data());
	return cat;
}
//#define BASE_CHECK
//#define RANGE_BESED_FOR_ARRAY
//#define PLUS_CHECK

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

#ifdef PLUS_CHECK
	ForwardList list5 = { 3,5,8,13,21 };
	list5.print();
	ForwardList list4 = { 3,5,8,13,21 };
	list4.print();
	ForwardList list20 = list4 + list5;
	list20.print();
#endif // PLUS_CHECK

	ForwardList list6 = { 3,5,8,13,21 };
	for (int i : list6)
	{
		cout << i << "\t";
	}
	cout << endl;
}
