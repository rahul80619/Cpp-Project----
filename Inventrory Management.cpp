#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

void saveInventory(const vector<Item>& items) {
    ofstream file("inventory.txt");
    for (auto &item : items) {
        file << item.id << " " << item.name << " " 
             << item.quantity << " " << item.price << "\n";
    }
}

vector<Item> loadInventory() {
    vector<Item> items;
    ifstream file("inventory.txt");
    Item item;
    while (file >> item.id >> item.name >> item.quantity >> item.price) {
        items.push_back(item);
    }
    return items;
}

void displayInventory(const vector<Item>& items) {
    cout << "\n=== Inventory ===\n";
    cout << left << setw(5) << "ID" << setw(15) << "Name" 
         << setw(10) << "Qty" << setw(10) << "Price\n";
    for (auto &item : items) {
        cout << left << setw(5) << item.id
             << setw(15) << item.name
             << setw(10) << item.quantity
             << setw(10) << item.price << "\n";
    }
}

void addItem(vector<Item>& items) {
    Item item;
    cout << "Enter ID: ";
    cin >> item.id;
    cout << "Enter Name: ";
    cin >> item.name;
    cout << "Enter Quantity: ";
    cin >> item.quantity;
    cout << "Enter Price: ";
    cin >> item.price;
    items.push_back(item);
    saveInventory(items);
    cout << "Item added!\n";
}

void updateItem(vector<Item>& items) {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;
    for (auto &item : items) {
        if (item.id == id) {
            cout << "Enter new quantity: ";
            cin >> item.quantity;
            cout << "Enter new price: ";
            cin >> item.price;
            saveInventory(items);
            cout << "Item updated!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

void deleteItem(vector<Item>& items) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].id == id) {
            items.erase(items.begin() + i);
            saveInventory(items);
            cout << "Item deleted!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

int main() {
    vector<Item> items = loadInventory();
    int choice;
    do {
        cout << "\n=== Inventory Management ===\n";
        cout << "1. Display Inventory\n";
        cout << "2. Add Item\n";
        cout << "3. Update Item\n";
        cout << "4. Delete Item\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayInventory(items); break;
            case 2: addItem(items); break;
            case 3: updateItem(items); break;
            case 4: deleteItem(items); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
