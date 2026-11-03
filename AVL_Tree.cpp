#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;

    Node(int x)
    {
        data = x;
        height = 1;
        left = right = NULL;
    }
};

int height(Node *p)
{
    return p ? p->height : 0;
}

int balance(Node *p)
{
    return p ? height(p->left) - height(p->right) : 0;
}

void update(Node *p)
{
    p->height = 1 + max(height(p->left), height(p->right));
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

Node *insert(Node *root, int key)
{
    if (!root)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root;

    update(root);
    int b = balance(root);

    if (b > 1 && key < root->left->data)
        return rightRotate(root); // LL

    if (b < -1 && key > root->right->data)
        return leftRotate(root); // RR

    if (b > 1 && key > root->left->data)
    { // LR
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && key < root->right->data)
    { // RL
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *minNode(Node *root)
{
    while (root->left)
        root = root->left;
    return root;
}

Node *deleteNode(Node *root, int key)
{
    if (!root)
        return NULL;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;

            if (!temp)
            {
                delete root;
                return NULL;
            }

            *root = *temp;
            delete temp;
        }
        else
        {
            Node *temp = minNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    update(root);
    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0)
        return rightRotate(root);

    if (b > 1 && balance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && balance(root->right) <= 0)
        return leftRotate(root);

    if (b < -1 && balance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool search(Node *root, int key)
{
    if (!root)
        return false;
    if (root->data == key)
        return true;

    return key < root->data
               ? search(root->left, key)
               : search(root->right, key);
}

void inorder(Node *root, ofstream &out)
{
    if (!root)
        return;

    inorder(root->left, out);
    out << root->data << " ";
    inorder(root->right, out);
}

// ---------- MAIN ----------

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    ofstream heightFile("height_data.csv");

    Node *avl = NULL;
    vector<int> a;
    int x;

    heightFile << "Nodes,Height\n";

    while (in >> x)
    {
        a.push_back(x);
        avl = insert(avl, x);
        heightFile << a.size() << "," << height(avl) << "\n";
    }

    cout << "AVL Height: " << height(avl) << endl;
    cout << "Root Balance Factor: " << balance(avl) << endl;

    cout << "Inorder: ";
    inorder(avl, out);

    // Deletion
    cout << "Enter value to delete: ";
    cin >> x;

    avl = deleteNode(avl, x);

    out << "\nAfter deletion: ";
    inorder(avl, out);

    cout << "Height after deletion: "
         << height(avl) << endl;

    cout << "Files created successfully.\n";
    cout << "Use height_data.csv to plot Height vs Nodes.\n";

    return 0;
}
