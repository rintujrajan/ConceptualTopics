#include <iostream>
#include <stack>

using namespace std;

template <typename T>
struct Tree
{
    Tree(const T &v) : value(v), left(nullptr), right(nullptr) {}
    T value;
    Tree *left;
    Tree *right;
};
Tree<int> *createTreeNode(int value, Tree<int> *leftNode, Tree<int> *rightNode)
{
    Tree<int> *node = new Tree<int>(value);
    node->left = leftNode;
    node->right = rightNode;
    return node;
}

void printPreorder(Tree<int> *root)
{
    stack<Tree<int> *> stackOfNodes;
    if (root != nullptr)
    {
        stackOfNodes.push(root);

        while (!stackOfNodes.empty())
        {
            Tree<int> *cutTopNode = stackOfNodes.top();
            cout << cutTopNode->value << " ";
            stackOfNodes.pop();

            if (cutTopNode->right != nullptr)
            {
                stackOfNodes.push(cutTopNode->right);
            }
            if (cutTopNode->left != nullptr)
            {
                stackOfNodes.push(cutTopNode->left);
            }
        }
    }
}
void printInorder(Tree<int> *root)
{
    stack<Tree<int> *> stackOfNodes;
    if (root != nullptr)
    {
        stackOfNodes.push(root);

        while (!stackOfNodes.empty())
        {
            Tree<int> *cutTopNode = stackOfNodes.top();
            if (cutTopNode->left != nullptr && cutTopNode->left->value > 0) //check if left node exists and its value is not -ve(already visited)
            {
                stackOfNodes.push(cutTopNode->left);
            }
            else
            {
                cout << cutTopNode->value << " ";
                stackOfNodes.pop();
                cutTopNode->value = -cutTopNode->value; // we negate the value which we already visited and popped out
                if (cutTopNode->right != nullptr)
                {
                    stackOfNodes.push(cutTopNode->right);
                }
            }
        }
    }
}
void printInorderWithNoStack(Tree<int> *root) //Morris Traversal
{
    Tree<int> *curr = root; // to store the current node

    while (curr != NULL)
    {
        //  if current does not have left child we print it
        if (curr->left == NULL)
        {
            cout << curr->value << " ";

            // go to current's right child
            curr = curr->right;
        }
        else
        {
            // we create links to Inorder Successor
            Tree<int> *pre = curr->left;
            while (pre->right != NULL && pre->right != curr)
                pre = pre->right;

            // building links
            if (pre->right == NULL)
            {
                //link made to Inorder Successor
                pre->right = curr;
                curr = curr->left;
            }

            // While breaking the links in so made temporary threaded tree we will print the nodes value
            else
            {
                // Revert the changes made in if part (break link from the Inorder Successor)
                pre->right = NULL;

                cout << curr->value << " ";

                curr = curr->right;
            }
        }
    }
}
void printPostorder(Tree<int> *root)
{
    stack<Tree<int> *> stackOfNodes;
    if (root != nullptr)
    {
        stackOfNodes.push(root);

        while (!stackOfNodes.empty())
        {
            Tree<int> *cutTopNode = stackOfNodes.top();
            if (cutTopNode->left != nullptr && cutTopNode->left->value > 0)
            {
                stackOfNodes.push(cutTopNode->left);
            }
            else
            {
                //cutTopNode->value = -cutTopNode->value; // we negate the value which we already visited and popped out
                if (cutTopNode->right != nullptr && cutTopNode->right->value > 0)
                {
                    stackOfNodes.push(cutTopNode->right);
                }
                else
                {
                    cout << cutTopNode->value << " ";
                    stackOfNodes.pop();
                    cutTopNode->value = -cutTopNode->value; // we negate the value which we already visited and popped out
                }
            }
        }
    }
}
int main()
{
    /*
    
                    1
                /       \
              2           3
            /   \      /      \ 
           4     5    6        7
          /       \    \      /
         8         9    10   11

    */
    Tree<int> *rootLeftLeftLeft = createTreeNode(8, nullptr, nullptr);
    Tree<int> *rootLeftRightRight = createTreeNode(9, nullptr, nullptr);
    Tree<int> *rootRightLeftRight = createTreeNode(10, nullptr, nullptr);
    Tree<int> *rootRightRightLeft = createTreeNode(11, nullptr, nullptr);

    Tree<int> *rootLeftLeft = createTreeNode(4, rootLeftLeftLeft, nullptr);
    Tree<int> *rootLeftRight = createTreeNode(5, nullptr, rootLeftRightRight);
    Tree<int> *rootRightLeft = createTreeNode(6, nullptr, rootRightLeftRight);
    Tree<int> *rootRightRight = createTreeNode(7, rootRightRightLeft, nullptr);

    Tree<int> *rootLeft = createTreeNode(2, rootLeftLeft, rootLeftRight);
    Tree<int> *rootRight = createTreeNode(3, rootRightLeft, rootRightRight);

    Tree<int> *root = createTreeNode(1, rootLeft, rootRight);

    std::cout << "Preorder : ";
    printPreorder(root);
    std::cout << "\n";

    std::cout << "Inorder : ";
    printInorderWithNoStack(root);
    std::cout << "\n";

    std::cout << "PostOrder : ";
    printPostorder(root);
    std::cout << "\n";

    std::cin.get();
    return 0;
}
