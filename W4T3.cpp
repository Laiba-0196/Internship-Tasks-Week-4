
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Item {
    int item_number;
    string description;
    int reserved_price;
    int no_of_bids;
    int highest_bid;
    bool sold;

    // Constructor to initialize members
    Item() : item_number(0), reserved_price(0), no_of_bids(0), highest_bid(0), sold(false) {}
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

class Buyer {
public:
    void viewItemDetails(Item items[]) {
        int item_number;
        cout << "Enter the item number you want to view: ";
        cin >> item_number;

        // Find the item
        int index = -1;
        for (int i = 0; i < 10; ++i) {
            if (items[i].item_number == item_number) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Item not found!" << endl;
            return;
        }

        // Display item details
        cout << "Item Number: " << items[index].item_number << endl;
        cout << "Description: " << items[index].description << endl;
        cout << "Reserved Price: " << items[index].reserved_price << endl;
        cout << "Current Highest Bid: " << items[index].highest_bid << endl;
    }

    void placeBid(Item items[]) {
        int item_number;
        cout << "Enter the item number you want to bid for: ";
        cin >> item_number;

        // Find the item
        int index = -1;
        for (int i = 0; i < 10; ++i) {
            if (items[i].item_number == item_number) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Item not found!" << endl;
            return;
        }

        // Enter buyer number and bid price
        int buyer_number, bid_price;
        cout << "Enter your buyer number: ";
        cin >> buyer_number;
        cout << "Enter your bid price: ";
        cin >> bid_price;

        // Check if bid is valid
        if (bid_price > items[index].highest_bid && bid_price > items[index].reserved_price) {
            items[index].highest_bid = bid_price;
            items[index].no_of_bids++;
            cout << "Bid accepted!" << endl;
        }
        else {
            cout << "Bid rejected. Your bid must be higher than the current highest bid and the reserved price." << endl;
        }
    }
};

void endAuction(Item items[]);

int main() {
    Seller seller;
    Buyer buyer;

    Item items[10]; // Array to hold items

    cout << "======================================" << endl;
    cout << "WELCOME TO THE ONLINE BIDDING SYSTEM" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << endl;

    cout << "======================================" << endl;
    cout << "\tAuction Setup" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << endl;

    seller.setvalues(items); // Pass items array to Seller

    cout << "======================================" << endl;
    cout << "\tBuyer Bid Setup" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << endl;

    int choice;
    do {
        cout << "1. View Item Details" << endl;
        cout << "2. Place Bid" << endl;
        cout << "3. End Auction" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            buyer.viewItemDetails(items);
            break;
        case 2:
            buyer.placeBid(items);
            break;
        case 3:
            cout << "Ending Auction..." << endl;
            endAuction(items);
            break;
        default:
            cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 3);

    return 0;
}

void endAuction(Item items[]) {
    int total_fee = 0;
    int sold_count = 0;
    int below_reserve_count = 0;
    int no_bid_count = 0;

    cout << "======================================" << endl;
    cout << "\tEnd of Auction Summary" << endl;
    cout << "======================================" << endl;
    cout << endl;

    for (int i = 0; i < 10; ++i) {
        if (items[i].sold) {
            sold_count++;
            total_fee += 0.1 * items[i].highest_bid; // Calculate 10% auction company fee
           
        }
        else {
            if (items[i].no_of_bids == 0) {
                cout << "Item Number " << items[i].item_number << " received no bids." << endl;
                no_bid_count++;
            }
            else if (items[i].highest_bid < items[i].reserved_price) {
                cout << "Item Number " << items[i].item_number << " did not meet the reserve price." << endl;
                below_reserve_count++;
            }
           
        }
    }

    cout << "Total Fee for Sold Items: $" << total_fee << endl;
    cout << "Items Sold: " << sold_count << endl;
    cout << "Items Not Meeting Reserve Price: " << below_reserve_count << endl;
    cout << "Items with No Bids: " << no_bid_count << endl;
}

