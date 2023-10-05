#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>

template <class T>
class AVL
{
private:
	struct Node
	{
		Node* left;
		Node* right;
		T element;
		int height;
		Node(T element);
		~Node() {};
	};
	Node* root = nullptr;
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
public:
	void destructorHelp(Node* current);
	AVL() = default;
	~AVL();
	int findHeight(Node* current);
	Node* rightRotation(Node* root);
	Node* leftRotation(Node* root);
	int balancedNode(Node* current);
	Node* insertHelpFunktion(Node* node, T element);
	void insert(T element);
	Node* miniNode(Node* node);
	Node* removeNode(Node*& current, T element);
	void searchNode(Node*& current, T element, Node*& parent);
	void remove(T element);
	bool find(T element);
	void inOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> inOrderWalk();
	void preOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> preOrderWalk();
	void postOrder(struct Node* current, std::vector<T>& my_vector);
	std::vector<T> postOrderWalk();
	int find_h(Node* node);
	int getTreeHeight();
	T getMin();
	T getMax();
	std::string ToGraphviz();
};


template<typename T>
AVL<T>::Node::Node(T element) {
	this->element = element;
	this->left = nullptr;
	this->right = nullptr;
	this->height = 1;
}

template<class T>
void AVL<T>::destructorHelp(Node* current) {

	if (current != NULL) {
		destructorHelp(current->left);
		destructorHelp(current->right);
		delete current;
	}
}

template<class T>
inline AVL<T>::~AVL()
{
	destructorHelp(root);
}

template<class T>
int AVL<T>::findHeight(Node* current) {
	if (current == nullptr) {
		return 0;
	}
	return current->height;
}

template<class T>
typename AVL<T>::Node* AVL<T>::rightRotation(Node* root)
{
	Node* newRoot = root->left;
	Node* T2 = newRoot->right;
	newRoot->right = root;
	root->left = T2;
	if ((findHeight(root->left)) > findHeight(root->right)) {
		root->height = findHeight(root->left) + 1;
	}
	else {
		root->height = findHeight(root->right) + 1;
	}
	if ((findHeight(newRoot->left)) > findHeight(newRoot->right)) {
		newRoot->height = findHeight(newRoot->left) + 1;
	}
	else {
		newRoot->height = findHeight(newRoot->right) + 1;
	}
	return newRoot;
}

template<class T>
typename AVL<T>::Node* AVL<T>::leftRotation(Node* root)
{
	Node* newRoot = root->right;
	Node* T2 = newRoot->left;
	newRoot->left = root;
	root->right = T2;
	if ((findHeight(root->left)) > findHeight(root->right)) {
		root->height = findHeight(root->left) + 1;
	}
	else {
		root->height = findHeight(root->right) + 1;
	}
	if ((findHeight(newRoot->left)) > findHeight(newRoot->right)) {
		newRoot->height = findHeight(newRoot->left) + 1;
	}
	else {
		newRoot->height = findHeight(newRoot->right) + 1;
	}
	return newRoot;
}

template<class T>
int AVL<T>::balancedNode(Node* current) {
	if (current == nullptr) {
		return 0;
	}
	return findHeight(current->left) - findHeight(current->right);
}

template<class T>
typename  AVL<T>::Node* AVL<T>::insertHelpFunktion(Node* node, T element) {
	if (node == nullptr) {
		return(new Node(element));
	}

	if (node->element > element) {
		node->left = insertHelpFunktion(node->left, element);
	}
	else if (node->element < element) {
		node->right = insertHelpFunktion(node->right, element);
	}
	else {
		return node;
	}

	if (findHeight(node->left) > findHeight(node->right)) {
		node->height = 1 + findHeight(node->left);
	}
	else {
		node->height = 1 + findHeight(node->right);
	}
	int balance = balancedNode(node);

	if (balance > 1) {
		if (element < node->left->element) {
			return rightRotation(node);
		}
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}

	if (balance < -1) {
		if (element > node->right->element) {
			return leftRotation(node);
		}
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}

	return node;
}

template<class T>
void AVL<T>::insert(T element)
{

	root = insertHelpFunktion(root, element);
}

template<class T>
void AVL<T>::searchNode(Node*& current, T Element, Node*& parent) {
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
typename AVL<T>::Node* AVL<T>::miniNode(Node* node)
{
	Node* current = node;
	while (current->left != nullptr)
		current = current->left;
	return current;

}
template<class T>
typename AVL<T>::Node* AVL<T>::removeNode(Node*& start, T element) {
	if (start == nullptr) {
		return start;
	}

	if (start->element > element) {
		start->left = removeNode(start->left, element);
	}

	else if (start->element < element) {
		start->right = removeNode(start->right, element);
	}

	else
	{
		if (start->left == nullptr or start->right == nullptr) {
			Node* sub = start->left ?
				start->left :
				start->right;

			if (sub == nullptr) {
				sub = start;
				start = nullptr;
			}
			else {
				*start = *sub;
			}
			delete sub;
		}
		else
		{
			Node* sub = miniNode(start->right);

			start->element = sub->element;

			start->right = removeNode(start->right, sub->element);
		}
	}
	if (start == nullptr) {
		return start;
	}

	if (findHeight(start->left) > findHeight(start->right)) {
		start->height = 1 + findHeight(start->left);
	}
	else {
		start->height = 1 + findHeight(start->right);
	}
	int balance = balancedNode(start);

	if (balance > 1) {
		if (balancedNode(start->left) >= 0) {
			return rightRotation(start);
		}
		start->left = leftRotation(start->left);
		return rightRotation(start);
	}
	if (balance < -1) {
		if (balancedNode(start->right) > 0)
		{
			start->right = rightRotation(start->right);
			return leftRotation(start);
		}
		return leftRotation(start);
	}
	return start;

}

template<class T>
inline void AVL<T>::remove(T element)
{
	removeNode(root, element);
}

template<class T>
bool AVL<T>::find(T element)
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
void AVL<T>::inOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {

		inOrder(current->left, my_vector);
		my_vector.push_back(current->element);
		inOrder(current->right, my_vector);
	}
}

template<class T>
inline std::vector<T> AVL<T>::inOrderWalk()
{
	std::vector<T> my_vector;
	inOrder(root, my_vector);
	return my_vector;
}

template<class T>
void AVL<T>::preOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {
		my_vector.push_back(current->element);
		preOrder(current->left, my_vector);
		preOrder(current->right, my_vector);
	}
}

template<class T>
inline std::vector<T> AVL<T>::preOrderWalk()
{
	std::vector<T> my_vector;
	preOrder(root, my_vector);
	return my_vector;
}

template<class T>
void AVL<T>::postOrder(struct Node* current, std::vector<T>& my_vector)
{
	if (current != NULL) {
		postOrder(current->left, my_vector);
		postOrder(current->right, my_vector);
		my_vector.push_back(current->element);
	}
}

template<class T>
inline std::vector<T> AVL<T>::postOrderWalk()
{
	std::vector<T> my_vector;
	postOrder(root, my_vector);
	return my_vector;
}

template<class T>
inline int AVL<T>::find_h(Node* node)
{
	if (node == NULL) { return -1; }
	return node->height - 1;
}

template<class T>
inline int AVL<T>::getTreeHeight()
{
	return find_h(root);

}


template<class T>
inline T AVL<T>::getMin()
{
	Node* current = root;
	while (current->left != nullptr)
	{
		current = current->left;
	}
	return current->element;
}

template<class T>
inline T AVL<T>::getMax()
{
	Node* current = root;
	while (current->right != nullptr)
	{
		current = current->right;
	}
	return current->element;
}




template <class T>
std::string AVL<T>::ToGraphviz() // Member function of the AVLTree class
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
void AVL<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
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
#endif //AVL_H
