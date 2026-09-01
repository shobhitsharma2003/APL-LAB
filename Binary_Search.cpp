#include <bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int n, int key, int &comparisons)
{
    int low = 0;
    int high = n - 1;

    comparisons = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        comparisons++;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    int n, key;
    int comparisons;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter " << n << " sorted elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter element to search: ";
    cin >> key;

    int result = binarySearch(arr, n, key, comparisons);

    if (result != -1)
    {
        cout << "\nElement found at position: " << result + 1;
        cout << "\nNumber of comparisons: " << comparisons;
    }
    else
    {
        cout << "\nElement not found.";
        cout << "\nNumber of comparisons: " << comparisons;
    }

    cout << "\n\nComplexity Analysis:";
    cout << "\nBest Case    : O(1)";
    cout << "\nAverage Case : O(log n)";
    cout << "\nWorst Case   : O(log n)";

    return 0;
}