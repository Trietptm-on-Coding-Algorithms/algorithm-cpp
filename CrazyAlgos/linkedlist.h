#include <vector>
#include "node.h"

template<typename T>
class LinkedList
{
protected:
	Node<T>* head;
	int length;
public:
	LinkedList<T>()
	{
		head = NULL;
		length = 0;
	}

	LinkedList<T>(Node<T>* hed)
	{
		head = hed;
		length = NULL;
	}

	LinkedList<T>(std::vector<T> dat)
	{
		Node<T>* now;
		Node<T>* prev = NULL;
		for(int i = in.size()-1; i >= 0; --i)
		{
			now = new Node<T>(in[i], prev);
			prev = now;
		}
		head = now;
		length = dat.size();
	}

	LinkedList<T>(T dat[])
	{
		const int n = sizeof(dat)/sizeof(T);
		Node<T>* now;
		Node<T>* prev = NULL;
		for(int i = n-1; i >= 0; --i)
		{
			now = new Node<T>(dat[i], prev);
			prev = now;
		}
		head = now;
		length = n;
	}

	LinkedList<T>(T* dat, const int size)
	{
		Node<T>* now;
		Node<T>* prev = NULL;
		for(int i = size-1; i >= 0; --i)
		{
			now = new Node<T>(dat[i], prev);
			prev = now;
		}
		head = now;
		length = size;
	}

	LinkedList<T>(const LinkedList<T>& that): 
		head(that.head), data(that.data){};

	virtual ~LinkedList<T>()
	{
		Node<T>* mid;
		for(Node<T>* a = head; a != NULL; a = mid)
		{
			mid = a->next;
			delete a;
		}
	}

	T& operator[] (const int n) const
	{
		int count = 0;
		for(Node<T>* a = head; a != NULL; a = a->next, count++)
		{
			if(count == n)
				return a->data;
		}
	}

	Node<T>& operator() (const int n) const
	{
		int count = 0;
		for(Node<T>* a = head; a != NULL; a = a->next, count++)
		{
			if(count == n)
				return *a;
		}
	}

	LinkedList<T>& operator= (const LinkedList<T>& rhs)
	{
		if(&rhs == this)
		{
			return *this;
		}
		else
		{

			return *this;
		}
	}

	bool operator== (const LinkedList<T>& rhs)
	{
		if(&rhs == this)
			return true;
		Node<T>* b = rhs.head;
		for(Node<T>* a = head; a != NULL || b != NULL; a = a->next, b = b->next)
		{
			if(a->data != b->data)
				return false;
		}
		if(a == NULL && b == NULL)
			return true;
		else
			return false;
	}

	void printForward(FILE* stream) const
	{
		for(Node<T>* a = head; a != NULL; a = a->next)
		{
			stream<<a->data<<" ";
		}
		stream<<"\n";
	}

	void printBackward(FILE* stream, Node<T>* head) const
	{
		if(head == NULL)
			return;
		else
		{
			printBackward(stream, head->next);
			stream<<head->data<<" ";
		}
	}

	void printBackward(FILE* stream) const
	{
		printBackward(stream, head);
	}


	const int insert(const T& data, const int place)
	{
		Node<T>* ne = new Node<T>(data);
		++length;
		if(head == NULL)
			return -1;
		if(place < 0)
		{
			return place;
		}
		else if(place == 0)
		{
			ne->next = head;
			head = ne;
			return place;
		}
		else if(place > length-1)
		{
			Node<T>* he = &(*this(length-1));
			he->next = ne;
			return place;
		}
		int count = 0;
		for(Node<T> a = head; a != NULL; a=a->next, ++count)
		{
			if(count+1 == place)
			{
				ne->next = a->next;
				a->next = ne;
				return place;
			}
		}
	}

	const int insert(const Node<T>& rhs, const int place)
	{
		++length;
		if(head == NULL)
			return -1;
		if(place < 0)
		{
			return place;
		}
		else if(place == 0)
		{
			rhs.next = head;
			head = &rhs;
			return place;
		}
		else if(place > length-1)
		{
			Node<T>* he = &(*this(length-1));
			he->next = &rhs;
			return place;
		}
		int count = 0;
		for(Node<T> a = head; a != NULL; a=a->next, ++count)
		{
			if(count+1 == place)
			{
				rhs.next = a->next;
				a->next = &rhs;
				return place;
			}
		}
	}

	const int insert(const Node<T>* rhs, int& place)
	{
		++length;
		if(head == NULL)
			return -1;
		if(place < 0)
		{
			return place;
		}
		else if(place == 0)
		{
			rhs->next = head;
			head = rhs;
			return place;
		}
		else if(place > length-1)
		{
			Node<T>* he = &(*this(length-1));
			he->next = rhs;
			return place;
		}
		int count = 0;
		for(Node<T> a = head; a != NULL; a=a->next, ++count)
		{
			if(count+1 == place)
			{
				rhs->next = a->next;
				a->next = rhs;
				return place;
			}
		}
	}

	const bool deleteNode(const T& data)
	{
		--length;
		Node<T>* mid;
		if(head == NULL)
			return false;
		if(head->data == data)
		{
			mid = head->next;
			delete head;
			head = mid;
			return true;
		}
		for(Node<T>* a = head; a->next != NULL; a = a->next)
		{
			if(a->next->data == data)
			{
				mid = a->next;
				a->next = a->next->next;
				delete mid;
				return true
			}
		}
		return false;
	}

	const bool deleteNode(const Node<T>& rhs)
	{
		--length;
		Node<T>* mid;
		if(head == NULL)
			return false;
		if(head->data == rhs.data)
		{
			mid = head->next;
			delete head;
			head = mid;
			return true;
		}
		for(Node<T>* a = head; a->next != NULL; a = a->next)
		{
			if(a->next->data == rhs.data)
			{
				mid = a->next;
				a->next = a->next->next;
				delete mid;
				return true
			}
		}
		return false;
	}

	const bool deleteNode(const Node<T>* rhs)
	{
		--length;
		Node<T>* mid;
		if(head == NULL)
			return false;
		if(head->data == rhs->data)
		{
			mid = head->next;
			delete head;
			head = mid;
			return true;
		}
		for(Node<T>* a = head; a->next != NULL; a = a->next)
		{
			if(a->next->data == rhs->data)
			{
				mid = a->next;
				a->next = a->next->next;
				delete mid;
				return true
			}
		}
		return false;
	}

	const bool deleteNodePlace(const int place)
	{
		--length;
		Node<T>* mid;
		if(head == NULL)
			return false;
		if(place == 0)
		{
			mid = head->next;
			delete head;
			head = mid;
			return true;
		}
		int count = 0;
		for(Node<T>* a = head; a->next != NULL; a = a->next, ++count)
		{
			if(count == place-1)
			{
				mid = a->next;
				a->next = a->next->next;
				delete mid;
				return true
			}
		}
		return false;
	}

	Node<T>& getNode(T& data) const
	{
		for(Node<T>* a = head; a != NULL; a = a->next)
		{
			if(a->data == data)
				return *a;
		}
		return NULL;
	}

	int getIndex(T& data) const
	{
		int i = 0;
		for(Node<T>* a = head; a != NULL; a = a->next, ++i)
		{
			if(a->data == data)
				return i;
		}
		return -1;
	}
	
	Node<T>* getHead() const
	{
		return head;
	}

	int getLength() const
	{
		return length;
	}
};

template<typename T>
static Node<T>* createList(std::vector<T> in)
{
	Node<T>* now;
	Node<T>* prev = NULL;
	for(int i = in.size()-1; i >= 0; --i)
	{
		now = new Node<T>(in[i], prev);
		prev = now;
	}
	return now;
}

template<typename T>
int hasLoop(Node<T>* head)
{
	Node<T>* slowNode = head;
	Node<T>* fastNode1 = head;
	Node<T>* fastNode2 = head;
	int index = 0;
	while(slowNode && fastNode1 = fastNode2->next && fastNode2 = fastNode1->next)
	{
		if(slowNode == fastNode1 || slowNode = fastNode2) 
			return index;
		slowNode = slowNode->next;
		++index;
	}
	return -1;
}