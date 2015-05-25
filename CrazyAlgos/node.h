template<typename T>
class Node
{
private:
protected:
	Node<T>* next;
	T data;
public:
	Node<T>();
	Node<T>(const T& dat): data(dat){};
	Node<T>(const T& dat,const Node<T>* nex): data(dat), next(nex){};
	Node<T>(const Node<T>& that): data(that.data), next(that.next){};
	Node<T>(const Node<T>* that): data(that->data), next(that->next){};
	Node<T>(const DoubleNode<T>& that): data(that.data), next(that.right){};
	virtual ~Node<T>()
	{
	}
};

template <typename T>
class DoubleNode
{
private:
protected:
	DoubleNode<T>* left;
	DoubleNode<T>* right;
	T data;
public:
	DoubleNode<T>(): left(NULL), right(NULL), data(NULL);
	DoubleNode<T>(const T& dat): left(NULL), right(NULL), data(dat){};
	DoubleNode<T>(const T& dat,const DoubleNode<T>* lhs,const DoubleNode<T>* rhs): data(dat), left(lhs), right(rhs){};
	DoubleNode<T>(const DoubleNode<T>* lhs,const DoubleNode<T>* rhs): data(NULL), left(lhs), right(rhs){};
	DoubleNode<T>(const DoubleNode<T>& that): data(that.data), left(that.left), right(that.right){};
	DoubleNode<T>(const DoubleNode<T>* that): data(that->data), left(that->left), right(that->right){};
	DoubleNode<T>(const Node<T>& that): left(NULL), data(that.data), right(that.right){};
	virtual ~DoubleNode<T>()
	{
	}
};