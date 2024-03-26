#include <iostream>
#include <algorithm>

using namespace std;

class Item {
public:
    int quantity;
    int whole_price;

    Item() {
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter whole price: ";
        cin >> whole_price;
    }

    int* calculateArray() {
        int* array = new int[quantity];
        for (int i = 0; i < quantity; ++i) {
            array[i] = whole_price / quantity;
        }
        return array;
    }
};

class Main {
public:
    int weight;

    Main() {
        cout << "Enter weight: ";
        cin >> weight;
    }

    int calculateMaxSum(Item& item1, Item& item2, Item& item3) {
        int* array1 = item1.calculateArray();
        int* array2 = item2.calculateArray();
        int* array3 = item3.calculateArray();

        int* combinedArray = new int[item1.quantity + item2.quantity + item3.quantity];
        int index = 0;

        for (int i = 0; i < item1.quantity; i++)
            combinedArray[index++] = array1[i];
        for (int i = 0; i < item2.quantity; i++)
            combinedArray[index++] = array2[i];
        for (int i = 0; i < item3.quantity; i++)
            combinedArray[index++] = array3[i];

        sort(combinedArray, combinedArray + (item1.quantity + item2.quantity + item3.quantity), greater<int>());

        int maxSum = 0;
        for (int i = 0; i < weight; ++i) {
            maxSum += combinedArray[i];
        }
        
        for (int i = 0; i <= sizeof(combinedArray); i++) {
            maxSum = maxSum - combinedArray[i - 1] + combinedArray[i + weight - 1];
        }

        delete[] array1;
        delete[] array2;
        delete[] array3;
        delete[] combinedArray;

        return maxSum;
    }
};

int main() {
    Item item1;
    Item item2;
    Item item3;

    Main ves;

    int maxSum = ves.calculateMaxSum(item1, item2, item3);
    cout << "Maximum sum: " << maxSum << endl;

    return 0;
}

