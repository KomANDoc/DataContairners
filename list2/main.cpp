#include"List.cpp"


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