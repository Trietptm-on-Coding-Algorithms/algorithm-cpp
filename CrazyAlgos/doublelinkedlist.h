#include "linkedlist.h"
#include "node.h"
#include <cassert>

template <typename T>
class DoubleLinkedList
{
private:
protected:
	DoubleNode<T>* lhs; //leftmost node
	DoubleNode<T>* rhs; //rightmost node
	int length;
public:
	DoubleLinkedList<T>()
	{
		lhs = NULL;
		rhs = NULL;
		length = 0;
	}
	DoubleLinkedList<T>(const DoubleNode<T>* head, const bool isLeftHead)
	{
		DoubleNode<T> place;
		length = 0;
		if(head != null)
			++length;
		else if(isLeftHead)
		{
			lhs = head;
			for(place = lhs;place != NULL && place->right != NULL; place = place->right, ++length);
			rhs = place;
		}
		else
		{
			rhs = head
			for(place = rhs;place != NULL && place->left != NULL; place = place->left, ++length);
			lhs = place
		}
	}
	DoubleLinkedList<T>(std::vector<T>& input)
	{
		DoubleNode<T>* prev;
		DoubleNode<T>* now;
		lhs = new DoubleNode(input[0]);
		prev = lhs;
		const int n = input.size();
		for(int i = 1; i < n; ++i)
		{
			now = new DoubleNode<T>(input[i]);
			prev->right = now;
			now->left = prev;
			prev = now;
		}
		rhs = now;
		length = n;
	}

	DoubleLinkedList<T>(const T[] data)
	{
		const int n = sizeof(data)/sizeof(T);
		DoubleNode<T>* prev;
		DoubleNode<T>* now;
		lhs = new DoubleNode(data[0]);
		prev = lhs;

		for(int i = 1; i < n; ++i)
		{
			now = new DoubleNode<T>(data[i]);
			prev->right = now;
			now->left = prev;
			prev = now;
		}
		rhs = now;
		length = n;
	}

	DoubleLinkedList<T>(const T* data, const int size)
	{
		DoubleNode<T>* prev;
		DoubleNode<T>* now;
		if(size < 0)
			throw std::exception("Size has to be greater than 0");

		lhs = new DoubleNode(data[0]);
		prev = lhs;

		for(int i = 1; i < size; ++i)
		{
			now = new DoubleNode<T>(data[i]);
			prev->right = now;
			now->left = prev;
			prev = now;
		}
		rhs = now;
		length = n;
	}

	DoubleLinkedList<T>(LinkedList<T>& input)
	{
		DoubleNode<T> *prev, *now;
		if(input.length < 0)
			throw std::exception("Size has to be greater than 0");

		lhs;
		//TODO: FINISH THE CLASS
		
	}
};