#include <iostream>
using namespace std;


template <typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		 Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		friend class List;
		friend class ConstIterator;

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
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "CBIConstructor:\t" << this << endl;
		}
		~ConstBaseIterator()
		{
			cout << "CBIDestructor:\t" << this << endl;
		}

		//operators

		bool operator== (const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!= (const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*()const
		{
			return Temp->get_data();
		}
	};
public:

	class ConstReversIterator:public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp):ConstBaseIterator(Temp)
		{
			cout << "RITConstructor:\t" << this << endl;
		}
		~ConstReversIterator()
		{
			cout << "RITDestructor:\t" << this << endl;
		}

		//operators 

		ConstReversIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReversIterator operator++(int)
		{
			ConstReversIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReversIterator operator--(int)
		{
			ConstReversIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp) {}
		~ReversIterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	class ConstIterator:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp):ConstBaseIterator(Temp)
		{
			cout << "ITConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ITDestructor:\t" << this << endl;
		}
	
		// Operators
	
		ConstIterator operator++()
	{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->get_pNext();
		return *this;
	}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->get_pNext();
			return old;
		}
		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp):ConstIterator(Temp){}
		~Iterator() {}

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};


	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		/*cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}*/
		for (T i : il)
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
	void push_front(T Data)
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
	void push_back(T Data)
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
	void insert(T Data, int Index)
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
		cout << "���������� ��������� � ������: " << size << endl;
	}
	void revers_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "���������� ��������� � ������: " << size << endl;
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

	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}
	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}
	ConstReversIterator crbegin()const
	{
		return Tail;
	}
	ConstReversIterator crend()const
	{
		return nullptr;
	}
};

template <typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		cat.push_back(*it);
	}
	return cat;
}


//#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "RU");

#ifdef OPERATOR_PLUS_CHECK
	List<int> list2 = { 5,6,2 };
	List<int> list3 = { 12,663 };
	List<int> list = list2 + list3;

	for (int i : list)cout << i << "\t";cout << endl;
	for (List<int>::ReversIterator it = list2.rbegin(); it != list2.rend(); ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;
	for (List<int>::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;
#endif // OPERATOR_PLUS_CHECK

	List<int> i_list = { 3,5,12 };
	for (int i : i_list) cout << i << "\t";cout << endl;

	List<double> d_list = { 3.4,12.7, 5.2 };
	for (double i : d_list) cout << i << "\t";cout << endl;
}