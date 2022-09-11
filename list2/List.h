#pragma once
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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();

		friend class List;
		friend class ConstIterator;

		const int& get_data()const;
		Element* get_pNext()const;
		Element* get_pPrev()const;
	}*Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();

		//operators

		bool operator== (const ConstBaseIterator& other)const;
		bool operator!= (const ConstBaseIterator& other)const;

		const T& operator*()const;
	};
public:

	class ConstReversIterator :public ConstBaseIterator
	{
	public:
		ConstReversIterator(Element* Temp);
		~ConstReversIterator();

		//operators 

		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp);
		~ReversIterator();

		T& operator*();
	};

	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();

		// Operators

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();

		T& operator*();
	};


	List();
	List(const std::initializer_list<T>& il);
	List(const List& other);
	List(List&& other);
	~List();
	// adding
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);
	// removing methods
	void pop_front();
	void pop_back();
	void erase(int Index);
	//get methods

	Element* get_Head()const;
	Element* get_Tail()const;
	size_t get_Size()const;

	// methods
	void print()const;
	void revers_print()const;

	//operators
	List& operator= (const List& other);
	List& operator= (List&& other);

	Iterator begin()const;
	Iterator end()const;
	ReversIterator rbegin();
	ReversIterator rend();
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReversIterator crbegin()const;
	ConstReversIterator crend()const;
};
