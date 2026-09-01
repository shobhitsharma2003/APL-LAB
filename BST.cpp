#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};

Node *insert(Node *root, int key)
{
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
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

Node *findMin(Node *root)
{
    Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return NULL;

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
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
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

    cout << "Enter " << n << " elements:\n";

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
        cout << value << " is present in the BST\n";
    else
        cout << value << " is not present in the BST\n";

    cout << "\nEnter value to delete: ";
    cin >> value;

    root = deleteNode(root, value);

    cout << "Inorder traversal after deletion: ";
    inorder(root);

    cout << "\n";

    freeTree(root);

    return 0;
}
