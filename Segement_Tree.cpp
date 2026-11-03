
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int minimum;
    int maximum;
};

class SegmentTree
{
    int n;
    vector<Node> tree;
    vector<int> arr;

    // Merge two nodes
    Node merge(const Node &left, const Node &right)
    {
        return {
            min(left.minimum, right.minimum),
            max(left.maximum, right.maximum)};
    }

    // Build segment tree
    void build(int idx, int start, int end)
    {
        if (start == end)
        {
            tree[idx] = {arr[start], arr[start]};
            return;
        }

        int mid = (start + end) / 2;

        build(idx * 2, start, mid);
        build(idx * 2 + 1, mid + 1, end);

        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    // Range query
    Node query(int idx, int start, int end, int L, int R)
    {
        if (R < start || L > end)
            return {INT_MAX, INT_MIN};

        if (L <= start && end <= R)
            return tree[idx];

        int mid = (start + end) / 2;

        Node left = query(idx * 2, start, mid, L, R);
        Node right = query(idx * 2 + 1, mid + 1, end, L, R);

        return merge(left, right);
    }

    // Update one element
    void update(int idx, int start, int end, int pos, int val)
    {
        if (start == end)
        {
            arr[pos] = val;
            tree[idx] = {val, val};
            return;
        }

        int mid = (start + end) / 2;

        if (pos <= mid)
            update(idx * 2, start, mid, pos, val);
        else
            update(idx * 2 + 1, mid + 1, end, pos, val);

        tree[idx] = merge(tree[idx * 2], tree[idx * 2 + 1]);
    }

    // Export CSV recursively
    void exportCSVRecursive(ofstream &csv, int idx, int start, int end)
    {
        csv << idx << ","
            << start << ","
            << end << ","
            << tree[idx].minimum << ","
            << tree[idx].maximum << "\n";

        if (start == end)
            return;

        int mid = (start + end) / 2;

        exportCSVRecursive(csv, idx * 2, start, mid);
        exportCSVRecursive(csv, idx * 2 + 1, mid + 1, end);
    }

public:
    // Constructor
    SegmentTree(const vector<int> &input)
    {
        arr = input;
        n = arr.size();

        tree.resize(4 * n);

        build(1, 0, n - 1);
    }

    // Public query
    Node query(int L, int R)
    {
        if (L < 0 || R >= n || L > R)
            return {INT_MAX, INT_MIN};

        return query(1, 0, n - 1, L, R);
    }

    // Public update
    void update(int pos, int val)
    {
        if (pos < 0 || pos >= n)
            return;

        update(1, 0, n - 1, pos, val);
    }

    // Print array
    void printArray(ostream &out)
    {
        out << "\nArray:\n";

        for (int v : arr)
            out << v << " ";

        out << "\n";
    }

    // Print segment tree
    void printSegmentTree(ostream &out)
    {
        out << "\nSegment Tree nodes (index: min, max):\n";

        for (int i = 1; i < 4 * n; i++)
        {
            if (tree[i].minimum != 0 || tree[i].maximum != 0)
            {
                out << i << ": ("
                    << tree[i].minimum << ", "
                    << tree[i].maximum << ")\n";
            }
        }
    }

    // Generate CSV file
    void exportCSV()
    {
        ofstream csv("segment_tree.csv");

        if (!csv.is_open())
        {
            cerr << "Error creating CSV file.\n";
            return;
        }

        csv << "Node Index,Segment Start,Segment End,Minimum,Maximum\n";

        exportCSVRecursive(csv, 1, 0, n - 1);

        csv.close();

        cout << "\nCSV file generated: segment_tree.csv\n";
    }
};

int main()
{
    // Open input file
    ifstream fin("input.txt");

    if (!fin.is_open())
    {
        cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    // Open output file
    ofstream fout("output.txt");

    if (!fout.is_open())
    {
        cerr << "Error: Could not create output.txt\n";
        return 1;
    }

    // Read array from first line
    vector<int> arr;
    int val;
    string line;

    if (!getline(fin, line))
    {
        cerr << "Error reading array.\n";
        return 1;
    }

    stringstream ss(line);

    while (ss >> val)
        arr.push_back(val);

    if (arr.empty())
    {
        cerr << "Error: Array is empty.\n";
        return 1;
    }

    cout << "Input file opened successfully.\n";
    fout << "Input file opened successfully.\n";

    // Build segment tree
    SegmentTree seg(arr);

    // Display original array
    seg.printArray(cout);
    seg.printArray(fout);

    // Display segment tree
    seg.printSegmentTree(cout);
    seg.printSegmentTree(fout);

    // Generate initial CSV
    seg.exportCSV();

    // Read number of queries
    int q;

    if (!(fin >> q) || q < 0)
    {
        cerr << "Invalid number of queries.\n";
        return 1;
    }

    cout << "\nNumber of queries: " << q << "\n";
    fout << "\nNumber of queries: " << q << "\n";

    // Process range queries
    for (int i = 0; i < q; i++)
    {
        int L, R;

        if (!(fin >> L >> R))
        {
            cerr << "Error reading query " << i + 1 << "\n";
            return 1;
        }

        cout << "\nQuery [" << L << ", " << R << "]\n";
        fout << "\nQuery [" << L << ", " << R << "]\n";

        if (L < 0 || R >= (int)arr.size() || L > R)
        {
            cout << "Invalid query range.\n";
            fout << "Invalid query range.\n";
            continue;
        }

        Node res = seg.query(L, R);

        cout << "Minimum = " << res.minimum << "\n";
        cout << "Maximum = " << res.maximum << "\n";

        fout << "Minimum = " << res.minimum << "\n";
        fout << "Maximum = " << res.maximum << "\n";
    }

    // Optional point update
    int updatePos, updateValue;

    if (fin >> updatePos >> updateValue)
    {
        cout << "\nUpdate:\n";
        fout << "\nUpdate:\n";

        cout << "Index = " << updatePos << "\n";
        cout << "New Value = " << updateValue << "\n";

        fout << "Index = " << updatePos << "\n";
        fout << "New Value = " << updateValue << "\n";

        if (updatePos >= 0 && updatePos < (int)arr.size())
        {
            seg.update(updatePos, updateValue);

            // Display updated array
            seg.printArray(cout);
            seg.printArray(fout);

            // Query entire array after update
            Node res = seg.query(0, (int)arr.size() - 1);

            cout << "\nAfter update:\n";
            cout << "Minimum = " << res.minimum << "\n";
            cout << "Maximum = " << res.maximum << "\n";

            fout << "\nAfter update:\n";
            fout << "Minimum = " << res.minimum << "\n";
            fout << "Maximum = " << res.maximum << "\n";

            // Regenerate CSV with updated values
            seg.exportCSV();
        }
        else
        {
            cout << "Invalid update index.\n";
            fout << "Invalid update index.\n";
        }
    }

    cout << "\nOutput saved to output.txt\n";

    fout << "\nOutput saved to output.txt\n";

    fin.close();
    fout.close();

    return 0;
}
