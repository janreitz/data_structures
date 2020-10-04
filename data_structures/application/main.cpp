#include "../dancing_list/dancing_list.h"

#include <iostream>
#include <string>

using namespace std;

void printList(const DancingList<string>& list)
{
	cout << "Dancing List: head";
	int i = 0;
	auto element = list.begin();
	while (element != list.end())
	{
		element = element->right();
		i++;
		cout << " <-> (" << to_string(i) << ", " << element->value() << ")";
	}
	cout << "\n";
}

int main()
{
	DancingList<string> dancingList;

	auto element = dancingList.begin();
	for (int i = 0; i < 10; i++)
	{
		dancingList.insertAfter(element, to_string(i));
		element = element->right();
	}
	printList(dancingList);

	for (int i = 0; i < 5; i++)
	{
		dancingList.undo();
	}
	printList(dancingList);
	return 0;
}