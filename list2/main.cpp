#include <iostream>
using namespace std;

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		friend class List;
		friend class Iterator;

		const int& get_data()const
		{
			return Data;
		}
		Element* get_pNext()const
		{
			return pNext;
		}
		Element* get_pPrev()const
		{
			return pPrev;
		}
	}*Head, *Tail;
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
	size_t size;

public:
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other)
	{
		*this = other;
	}
	List(List&& other) : List()
	{
		*this = std::move(other);
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	// adding
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Element* New = new Element(Data);
		//New->pNext = Head;
		//Head->pPrev = New;
		//Head = New;
		  Head = new Element(Data, Head);
		
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			return push_front(Data);
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == size) return push_back(Data);
		if (Index == 0) return push_front(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	// removing methods
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			return pop_front();
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == size-1) return pop_back();
		if (Index == 0) return pop_front();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	//get methods

	Element* get_Head()const
	{
		return Head;
	}
	Element* get_Tail()const
	{
		return Tail;
	}

	// methods
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
	void revers_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}

	//operators
	List& operator= (const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		return *this;
	}
	List& operator= (List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		return *this;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
};





void main()
{
	setlocale(LC_ALL, "RU");

	int n;
	cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	list.print();


	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

	//задание с выводом в main

	//for (List::Element* Temp = list.get_Tail(); Temp; Temp = Temp->get_pPrev())
	//{
	//	
	//}
	//
}