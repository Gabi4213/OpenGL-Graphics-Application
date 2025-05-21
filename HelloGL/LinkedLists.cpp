#include "LinkedLists.h"

LinkedLists::LinkedLists() //constructor
{

}

LinkedLists::~LinkedLists() //destructor
{

}

/* i started creating the linked lists, it works but i never ended up implementing it and just used arrays instead

ListNode* LinkedLists::MakeNode(ListNode** head, SceneObject** object)
{
	int count = 0;
	ListNode* newNode = new ListNode;
	ListNode* last = *head;
	newNode->object[count] = *object;
	newNode->next = nullptr;
	

	if (*head == nullptr)
	{
		*head = newNode;
		return newNode;
		count++;
	}
	while (last->next != nullptr)
	{
		last = last->next;
	}

	last->next = newNode;

	return newNode;
}

void LinkedLists::PrintList(ListNode* node)
{
	while (node != nullptr)
	{
		cout << setw(5) << "| " << node->object << " |-->";
		node = node->next;
	}

	if (node == nullptr)
	{
		std::cout << "| NULL |" << std::endl;
	}

	std::cout << std::endl;
}
*/