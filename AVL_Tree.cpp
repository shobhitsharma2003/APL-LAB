#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

int getheight(Node *N)
{
    if (N == NULL)
        return 0;

    return N->height;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;

    return getheight(N->left) - getheight(N->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getheight(y->left), getheight(y->right));
    x->height = 1 + max(getheight(x->left), getheight(x->right));

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getheight(x->left), getheight(x->right));
    y->height = 1 + max(getheight(y->left), getheight(y->right));

    return y;
}

Node *insert(Node *node, int key)
{
    if (node == NULL)
        return new Node(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getheight(node->left),
                           getheight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    if (balance > 1 && key > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int findmin(Node *node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current->data;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {

        if (root->left == NULL || root->right == NULL)
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                delete root;
                return NULL;
            }

            else
            {
                Node *oldRoot = root;
                root = temp;
                delete oldRoot;
            }
        }
        else
        {

            int minValue = findmin(root->right);

            root->data = minValue;

            root->right = deleteNode(root->right, minValue);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getheight(root->left),
                           getheight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

bool search(Node *root, int key)
{
    if (root == NULL)
        return false;

    if (key == root->data)
        return true;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

void freeTree(Node *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    delete root;
}

int main()
{
    Node *root = NULL;

    int n, value;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter " << n << " node elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nInorder traversal: ";
    inorder(root);

    cout << "\nPreorder traversal: ";
    preorder(root);

    cout << "\nPostorder traversal: ";
    postorder(root);

    cout << "\n\nEnter value to search: ";
    cin >> value;

    if (search(root, value))
        cout << value << " is present in the AVL tree\n";
    else
        cout << value << " is not present in the AVL tree\n";

    cout << "\nEnter value to delete: ";
    cin >> value;

    root = deleteNode(root, value);

    cout << "Inorder traversal after deletion: ";
    inorder(root);

    cout << "\n";

    freeTree(root);

    return 0;
}
