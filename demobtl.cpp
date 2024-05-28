#include <iostream>
#include <string.h>
using namespace std;
//Cau truc cua mat hang
struct Item {
    int id;
    char name[50];
    int quantity;
    double price;
    Item* next;
};

//Them mat hang moi
void addItem(Item*& head, int id, const char* name, int quantity, double price) {
    Item* newItem = new Item;
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;

    if (!head) {
        head = newItem;
    } else {
        Item* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newItem;
    }
}
//Sua thong tin mat hang
bool updateItem(Item* head, int id, const char* name, int quantity, double price) {
    Item* temp = head;
    while (temp) {
        if (temp->id == id) {
            strcpy(temp->name, name);
            temp->quantity = quantity;
            temp->price = price;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
//Xoa mat hang
bool deleteItem(Item*& head, int id) {
    if (!head) return false;
    if (head->id == id) {
        Item* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Item* prev = head;
    Item* current = head->next;
    while (current) {
        if (current->id == id) {
            prev->next = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
//doi cho sp de sap xep
void swapItems(Item* a, Item* b) {
    int tempId = a->id;
    a->id = b->id;
    b->id = tempId;

    char tempName[50];
    strcpy(tempName, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tempName);

    int tempQuantity = a->quantity;
    a->quantity = b->quantity;
    b->quantity = tempQuantity;

    double tempPrice = a->price;
    a->price = b->price;
    b->price = tempPrice;
}
//Sap xep theo ID
void sortItems(Item*& head) {
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->id > current->next->id) {
                swapItems(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void printItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << endl;
        temp = temp->next;
    }
}

int main() {
    Item* head = NULL;

    addItem(head, 1, "Item1", 10, 50.0);
    addItem(head, 2, "Item2", 20, 30.0);
    addItem(head, 3, "Item3", 15, 20.0);

    cout << "Danh sach mat hang ban dau:" << endl;
    printItems(head);

    updateItem(head, 2, "UpdatedItem2", 25, 35.0);

    cout << "Danh sach mat hang sau khi sua:" << endl;
    printItems(head);

    deleteItem(head, 1);

    cout << "Danh sach mat hang sau khi xoa:" << endl;
    printItems(head);

    sortItems(head);

    cout << "Danh sach mat hang sau khi sap xep:" << endl;
    printItems(head);

    return 0;
}
//Moi ng sua qua phan main de thao tac
