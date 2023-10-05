#ifndef BST_H
#define BST_H

#include <vector>
#include <string>

template <class T>
class BST
{
private:
	struct Node
	{
		Node* left;
		Node* right;
		T element;
		Node(T element);
		~Node() {};
	};
	int find_h(Node* node);
	Node* root = nullptr;
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
public:
	void destructorHelp(Node* current);
	BST() = default;
	~BST();
	void insert(T element);
	void removeNode(Node*& current, T element);
	void searchNode(Node*& current, T element, Node*& parent);
	void remove(T element);
	bool find(T element);
	void inOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> inOrderWalk();
	void preOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> preOrderWalk();
	void postOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> postOrderWalk();
	int getTreeHeight();
	T getMin();
	T getMax();
	std::string ToGraphviz();
};

template<typename T>
BST<T>::Node::Node(T element) {
	this->element = element;
	this->left = nullptr;
	this->right = nullptr;
}

template<class T>
void BST<T>::destructorHelp(Node* current) {

	if (current != NULL) {
		destructorHelp(current->left);
		destructorHelp(current->right);
		delete current;
	}
}

template<class T>
inline BST<T>::~BST()
{
	destructorHelp(root);
}

template<class T>
void BST<T>::insert(T element)
{
	if (root == nullptr) {
		root = new Node(element);
	}
	else {
		Node* current = root;
		Node* parent = nullptr;
		while (current != nullptr)
		{
			parent = current;
			if (element < current->element) {
				current = current->left;
			}
			else if (element > current->element)
			{
				current = current->right;
			}
			else { current = nullptr; }
		}
		if (element < parent->element) {
			parent->left = new Node(element);
		}
		else if (element > parent->element)
		{
			parent->right = new Node(element);
		}
	}
}
template<class T>
void BST<T>::searchNode(Node*& current, T Element, Node*& parent) {
	while (current != nullptr && current->element != Element) {
		parent = current;
		if (Element < current->element) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
}
template<class T>
void BST<T>::removeNode(Node*& start, T element) {
	Node* current = start;
	Node* parent = nullptr;
	searchNode(current, element, parent);

	if (current == nullptr) {
		delete current;
		return;
	}

	if (current->left == nullptr && current->right == nullptr) {
		if (current != start) {
			if (parent->left == current) {
				delete current;
				parent->left = nullptr;
			}
			else {
				delete current;
				parent->right = nullptr;
			}
		}
		else {
			delete start;
			start = nullptr;
		}

	}
	else if (current->left == nullptr or current->right == nullptr) {
		Node* subNode = (current->left) ? current->left : current->right;
		if (current != start) {
			if (current == parent->left) {
				delete current;
				parent->left = subNode;
			}
			else {
				delete current;
				parent->right = subNode;
			}
		}
		else {
			delete start;
			start = subNode;
		}

	}
	else {

		Node* subNode = current->left;
		while (subNode->right != nullptr) {
			subNode = subNode->right;
		}
		T minValue = subNode->element;
		removeNode(start, subNode->element);
		current->element = minValue;
	}
}
template<class T>
inline void BST<T>::remove(T element)
{
	removeNode(root, element);
}

template<class T>
bool BST<T>::find(T element)
{
	bool return_value = false;
	Node* current = root;
	while (current != nullptr)
	{
		if (element < current->element) { current = current->left; }
		else if (element > current->element) { current = current->right; }
		else if (element == current->element) { return_value = true; current = nullptr; }
	}
	return return_value;
}

template<class T>
void BST<T>::inOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {

		inOrder(current->left, my_vector);
		my_vector.push_back(current->element);
		inOrder(current->right, my_vector);
	}
}
template<class T>
inline std::vector<T> BST<T>::inOrderWalk()
{
	std::vector<T> my_vector;
	inOrder(root, my_vector);
	return my_vector;
}

template<class T>
void BST<T>::preOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {
		my_vector.push_back(current->element);
		preOrder(current->left, my_vector);
		preOrder(current->right, my_vector);
	}
}

template<class T>
inline std::vector<T> BST<T>::preOrderWalk()
{
	std::vector<T> my_vector;
	preOrder(root, my_vector);
	return my_vector;
}

template<class T>
void BST<T>::postOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {
		postOrder(current->left, my_vector);
		postOrder(current->right, my_vector);
		my_vector.push_back(current->element);
	}
}

template<class T>
inline std::vector<T> BST<T>::postOrderWalk()
{
	std::vector<T> my_vector;
	postOrder(root, my_vector);
	return my_vector;
}

template<class T>
inline int BST<T>::find_h(Node* node)
{
	if (node == NULL) {
		return -1;
	}
	int h_left = find_h(node->left);
	int h_right = find_h(node->right);

	if (h_left > h_right) { return h_left + 1; }
	else { return h_right + 1; }
}
template<class T>
inline int BST<T>::getTreeHeight()
{
	return find_h(root);

}

template<class T>
inline T BST<T>::getMin()
{
	Node* current = root;
	while (current->left != nullptr)
	{
		current = current->left;
	}
	return current->element;
}

template<class T>
inline T BST<T>::getMax()
{
	Node* current = root;
	while (current->right != nullptr)
	{
		current = current->right;
	}
	return current->element;
}

template <class T>
std::string BST<T>::ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if (this->root) // root is a pointer to the root node of the tree
	{
		std::string listOfNodes;
		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
		toReturn += std::string("digraph {\n");
		size_t id = 0;
		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
		toReturn += listOfNodes;
		toReturn += listOfConnections;
		toReturn += std::string("}");
	}
	return toReturn;
}

template <class T>
void BST<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if (toWorkWith->left)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}

	if (toWorkWith->right)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->right, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}
#endif //BST_H
