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
		friend class Itterator;

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
	size_t size;

public:

	class ReversItterator
	{
		Element* Temp;
	public:
		ReversItterator(Element* Temp = nullptr):Temp(Temp)
		{
			cout << "RITConstructor:\t" << this << endl;
		}
		~ReversItterator()
		{
			cout << "RITDestructor:\t" << this << endl;
		}

		//operators 
		ReversItterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReversItterator operator++(int)
		{
			ReversItterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReversItterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReversItterator operator--(int)
		{
			ReversItterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator== (const ReversItterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!= (const ReversItterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->get_data();
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	class Itterator
	{
		Element* Temp;
	public:
		Itterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ITConstructor:\t" << this << endl;
	}
		~Itterator()
	{
		cout << "ITDestructor:\t" << this << endl;
	}
	
		// Operators
	
		Itterator operator++()
	{
		Temp = Temp->get_pNext();
		return *this;
	}
		Itterator operator++(int)
		{
			Itterator old = *this;
			Temp = Temp->get_pNext();
			return old;
		}
		Itterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Itterator operator--(int)
		{
			Itterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator== (const Itterator& other)const
	{
		return this->Temp == other.Temp;
	}
		bool operator!= (const Itterator& other)const
	{
		return this->Temp != other.Temp;
	}
		const int& operator*()const
		{
		return Temp->get_data();
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		/*cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}*/
		for (int i : il)
		{
			push_back(i);
		}
	}
	List(const List& other) :List()
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
		  Head = Head->pPrev = new Element(Data, Head);
		
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			return push_front(Data);
		}
		//Element* New = new Element(Data);
		//New->pPrev = Tail;
		//Tail->pNext = New;
		//Tail = New;
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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
		//Element* New = new Element(Data);
		//New->pNext = Temp;
		//New->pPrev = Temp->pPrev;
		//Temp->pPrev->pNext = New;
		//Temp->pPrev = New;
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
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
	size_t get_Size()const
	{
		return size;
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

	Itterator begin()const
	{
		return Head;
	}
	Itterator end()const
	{
		return nullptr;
	}
	ReversItterator rbegin()
	{
		return Tail;
	}
	ReversItterator rend()
	{
		return nullptr;
	}
};


List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::Itterator it = right.begin(); it != right.end(); ++it)
	{
		cat.push_back(*it);
	}
	return cat;
}


void main()
{
	setlocale(LC_ALL, "RU");

	List list2 = { 5,6,2,6,8,12,5,125 };
	List list3 = { 12,663,15,65,183,5 };
	List list4 = List2 + List3;

	for (List::ReversItterator it = list2.rbegin(); it != list2.rend();++it)
	{
		cout << *it << "\t";
	}
	cout << endl;

}