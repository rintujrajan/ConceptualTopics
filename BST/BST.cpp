
#include <iostream>
using namespace std;
struct Node
{
	int value;
	Node* left;
	Node* right;
	Node(int value)
	{
		this->value = value;
		this->left = this->right = nullptr;
	}
};

int i = 0, j = 0,height = 0;
int traverse(Node* root)
{
	// Base case: empty tree has height 0
	if (root == nullptr)
		return 0;
	cout << "i : " << ++i << endl;
	height = (i > height) ? i : height;
	cout << root->value << endl;
	traverse(root->left);
	traverse(root->right);
	cout << "j : " << ++j << endl;
	i--;
	return height;
}

//int valReq = 3;
//bool traverseToFindReqHeightExists(Node* root)
//{
//	// Base case: empty tree has height 0
//	if (root == nullptr)
//		return false;
//	cout << "i : " << ++i << endl;
//	j--;
//	cout << root->value << endl;
//	traverse(root->left);
//	traverse(root->right);
//	cout << "j : " << ++j << endl;
//	if (i == valReq)
//	{
//		cout << "Found when i =" << i << " j = " << j<<endl;
//		return true;
//	}
//	i--;
//}

bool valFound = false;
bool searchDFS(Node* root, int searchVal)
{
	// Base case: empty tree has height 0
	if (root == nullptr)
		return false;
	if(valFound) return valFound;
	cout << "i : " << ++i << endl;
	cout << root->value << endl;
	if (root->value == searchVal)
	{
		valFound = true;
		return valFound;
	}
	searchDFS(root->left, searchVal);
	searchDFS(root->right, searchVal);
	cout << "j : " << ++j << endl;
	i--;
	return valFound;
}

int main() {
	//print(3);
	Node* node = new Node(50);

	//50
	node->left = new Node(30);
	node->right = new Node(70);

	//30
	node->left->left = new Node(20);
	node->left->right = new Node(40);

	//20
	node->left->left->right = new Node(25);

	//70
	node->right->left = new Node(60);
	node->right->right = new Node(80);

	//80
	node->right->right->left = new Node(75);

	//75
	node->right->right->left->right = new Node(78);

	//cout << "height: "<<traverse(node);
	int searchVal = 20;
	bool res = searchDFS(node, searchVal);
	cout <<searchVal<< " exists : " <<res;
}