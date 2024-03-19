//This task is for the implementation of the acution setup

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Item {
    int item_number;
    string description;
    int reserved_price;
    int no_of_bids;
   
  
};

class Seller {
public:
    void setvalues(Item items[]) {
        ofstream outFile("items.txt");
        if (!outFile) {
            cerr << "Error: Unable to open file for writing." << endl;
            exit(1);
        }

        for (int i = 0; i < 10; ++i) {
            cout << "Enter the item number: ";
            cin >> items[i].item_number;
            outFile << items[i].item_number << endl;

            cout << "Enter the reserved price of item: ";
            cin >> items[i].reserved_price;
            outFile << items[i].reserved_price << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the description of Item: ";
            getline(cin, items[i].description);
            outFile << items[i].description << endl;

            cout << endl;
        }

        outFile.close();
    }
};


int main() {
    Seller seller;
   

    Item items[10]; // Array to hold items

    cout << "======================================" << endl;
    cout << "WELCOME TO THE ONLINE BIDDING SYSTEM" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << endl;

    cout << "======================================" << endl;
    cout << "\tAcution Setup" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << endl;
    seller.setvalues(items); // Pass items array to Seller
    return 0;
}
