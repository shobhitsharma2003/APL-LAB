#include <bits/stdc++.h>
using namespace std;

enum Color
{
    RED,
    BLACK
};

string colorName(Color c)
{
    return c == RED ? "RED" : "BLACK";
}

struct Node
{
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int k = 0, Color c = BLACK)
    {
        key = k;
        color = c;
        left = right = parent = nullptr;
    }
};

class RedBlackTree
{
    Node *root, *NIL;

    void setColor(Node *n, Color c, string reason)
    {
        if (n == NIL || n->color == c)
            return;

        cout << reason << ": Node " << n->key
             << " changes from " << colorName(n->color)
             << " to " << colorName(c) << endl;

        n->color = c;
    }

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        cout << "Left rotation at node " << x->key << endl;

        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y)
    {
        Node *x = y->left;
        cout << "Right rotation at node " << y->key << endl;

        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;

        x->parent = y->parent;

        if (y->parent == NIL)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    void insertFix(Node *z)
    {
        while (z->parent->color == RED)
        {
            Node *p = z->parent;
            Node *g = p->parent;

            if (p == g->left)
            {
                Node *u = g->right;

                if (u->color == RED)
                {
                    cout << "Recoloring (parent and uncle are RED)\n";
                    setColor(p, BLACK, "Recoloring");
                    setColor(u, BLACK, "Recoloring");
                    setColor(g, RED, "Recoloring");
                    z = g;
                }
                else
                {
                    if (z == p->right)
                    {
                        z = p;
                        leftRotate(z);
                    }

                    setColor(z->parent, BLACK, "Recoloring");
                    setColor(z->parent->parent, RED, "Recoloring");
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                Node *u = g->left;

                if (u->color == RED)
                {
                    cout << "Recoloring (parent and uncle are RED)\n";
                    setColor(p, BLACK, "Recoloring");
                    setColor(u, BLACK, "Recoloring");
                    setColor(g, RED, "Recoloring");
                    z = g;
                }
                else
                {
                    if (z == p->left)
                    {
                        z = p;
                        rightRotate(z);
                    }

                    setColor(z->parent, BLACK, "Recoloring");
                    setColor(z->parent->parent, RED, "Recoloring");
                    leftRotate(z->parent->parent);
                }
            }
        }

        setColor(root, BLACK, "Root must be BLACK");
    }

    void transplant(Node *u, Node *v)
    {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    Node *minimum(Node *n)
    {
        while (n->left != NIL)
            n = n->left;
        return n;
    }

    void deleteFix(Node *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node *s = x->parent->right;

                if (s->color == RED)
                {
                    setColor(s, BLACK, "Deletion fix");
                    setColor(x->parent, RED, "Deletion fix");
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK &&
                    s->right->color == BLACK)
                {
                    setColor(s, RED, "Deletion fix");
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        setColor(s->left, BLACK, "Deletion fix");
                        setColor(s, RED, "Deletion fix");
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    setColor(s, x->parent->color, "Deletion fix");
                    setColor(x->parent, BLACK, "Deletion fix");
                    setColor(s->right, BLACK, "Deletion fix");

                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node *s = x->parent->left;

                if (s->color == RED)
                {
                    setColor(s, BLACK, "Deletion fix");
                    setColor(x->parent, RED, "Deletion fix");
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK &&
                    s->left->color == BLACK)
                {
                    setColor(s, RED, "Deletion fix");
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        setColor(s->right, BLACK, "Deletion fix");
                        setColor(s, RED, "Deletion fix");
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    setColor(s, x->parent->color, "Deletion fix");
                    setColor(x->parent, BLACK, "Deletion fix");
                    setColor(s->left, BLACK, "Deletion fix");

                    rightRotate(x->parent);
                    x = root;
                }
            }
        }

        setColor(x, BLACK, "Final deletion fix");
    }

    void inorder(Node *n, ostream &out, char sep)
    {
        if (n == NIL)
            return;
        inorder(n->left, out, sep);
        out << n->key << "(" << colorName(n->color) << ")" << sep;
        inorder(n->right, out, sep);
    }

    void clear(Node *n)
    {
        if (n == NIL)
            return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

public:
    RedBlackTree()
    {
        NIL = new Node();
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    ~RedBlackTree()
    {
        clear(root);
        delete NIL;
    }

    void insert(int key)
    {
        Node *z = new Node(key, RED);
        z->left = z->right = z->parent = NIL;

        Node *p = NIL, *n = root;

        while (n != NIL)
        {
            p = n;

            if (key == n->key)
            {
                cout << "Duplicate value " << key << " ignored.\n";
                delete z;
                return;
            }

            n = key < n->key ? n->left : n->right;
        }

        z->parent = p;

        if (p == NIL)
            root = z;
        else if (key < p->key)
            p->left = z;
        else
            p->right = z;

        cout << "\nInserting node " << key << endl;
        cout << "Node " << key << " initially becomes RED.\n";

        insertFix(z);

        cout << "Tree after inserting " << key << ":\n";
        display();
    }

    bool remove(int key)
    {
        Node *z = root;

        while (z != NIL && z->key != key)
            z = key < z->key ? z->left : z->right;

        if (z == NIL)
        {
            cout << "Node " << key << " not found.\n";
            return false;
        }

        cout << "\nDeleting node " << key
             << " (" << colorName(z->color) << ")\n";

        Node *y = z, *x;
        Color original = y->color;

        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            original = y->color;
            x = y->right;

            cout << "Successor node: " << y->key << endl;

            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (original == BLACK)
        {
            cout << "Deleted node was BLACK. Fixing tree...\n";
            deleteFix(x);
        }
        else
        {
            cout << "Deleted node was RED. No color correction needed.\n";
        }

        if (root != NIL)
            setColor(root, BLACK, "Root correction");

        cout << "Deletion completed.\n";
        return true;
    }

    void display()
    {
        cout << "Node(Color): ";
        inorder(root, cout, ' ');
        cout << endl;
    }

    void save()
    {
        ofstream txt("output.txt"), csv("output.csv");

        if (!txt || !csv)
        {
            cout << "Error creating output files!\n";
            return;
        }

        inorder(root, txt, ' ');
        inorder(root, csv, ',');
        txt << endl;
        csv << endl;

        cout << "Output saved in output.txt and output.csv\n";
    }
};

vector<int> readFile(string filename, char delimiter)
{
    vector<int> data;
    ifstream file(filename);
    string line;

    if (!file)
    {
        cout << "Cannot open " << filename << endl;
        return data;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;

        if (delimiter == ' ')
        {
            int x;
            while (ss >> x)
                data.push_back(x);
        }
        else
        {
            while (getline(ss, value, delimiter))
            {
                try
                {
                    size_t pos;
                    int x = stoi(value, &pos);

                    if (value.find_first_not_of(" \t\r\n", pos) == string::npos)
                        data.push_back(x);
                }
                catch (...)
                {
                    cout << "Invalid CSV value: " << value << endl;
                }
            }
        }
    }

    return data;
}

int main()
{
    RedBlackTree tree;

    vector<int> a = readFile("input.txt", ' ');
    vector<int> b = readFile("input.csv", ',');

    cout << "========== INSERTION PROCESS ==========\n";

    for (int x : a)
        tree.insert(x);
    for (int x : b)
        tree.insert(x);

    cout << "\n========== FINAL TREE AFTER INSERTION ==========\n";
    tree.display();

    int key;
    cout << "\nEnter value to delete: ";
    cin >> key;

    cout << "\n========== DELETION PROCESS ==========\n";
    tree.remove(key);

    cout << "\n========== FINAL TREE AFTER DELETION ==========\n";
    tree.display();

    tree.save();

    return 0;
}