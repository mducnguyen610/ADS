#include<conio.h>
#include<stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

// Dinh nghia cau truc cua mat hang bao gom id, ten, so luong, gia ca va di kem con tro
struct Item {
    int id;
    char name[50];
    int quantity;
    double price;
    Item* next;
};

void pressAnyKey() {
    cout << "\n\nBam phim bat ky de tiep tuc...";
    getch();
    system("cls");
}

// Them mat hang moi
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

// Sua thong tin mat hang
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

// Xoa mat hang
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

// Ham doi cho
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

// Sap xep theo ID
void sortItemsID(Item*& head) {
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

// Sap xep theo so luong tu lon den be
void sortItemsQuantity(Item*& head) {
    if (!head) return;
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->quantity > current->next->quantity) {
                swapItems(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}
//Sap xep theo gia tien tu lon den be
void sortItemsPrice(Item*& head) {
    if (!head) return;	//Ds rong thi ko lam gi
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->price > current->next->price) { //Kiem tra gia cua mat hang hien tai co lon hon gia cua mat hang ke tiep
                swapItems(current, current->next);//Hoan doi thong tin 2 mat hang
                swapped = true;	//Danh dau da hoan doi
            }
            current = current->next;
        }
    } while (swapped);
}
// In ra danh sach
void printItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << std::endl;
        temp = temp->next;
    }
}

// Xuat mat hang
void exportItem(Item*& head, Item*& soldHead, int id, int quantity) {
    Item* temp = head;
    while (temp) {
        if (temp->id == id) {
            if (temp->quantity >= quantity) {
                temp->quantity -= quantity;
                Item* soldItem = new Item;
                soldItem->id = id;
                strcpy(soldItem->name, temp->name);
                soldItem->quantity = quantity;
                soldItem->price = temp->price;
                soldItem->next = soldHead;
                soldHead = soldItem;
                if (temp->quantity == 0) {
                    deleteItem(head, id);
                }
                return;
            } else {
                cout << "Khong du so luong san pham trong kho de xuat." << endl;
                return;
            }
        }
        temp = temp->next;
    }
    cout << "Khong tim thay san pham voi ID nay" << endl;
}

// In ra danh sach da xuat
void printSoldItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << std::endl;
        temp = temp->next;
    }
}

// Tinh tong so luong va tong gia tri
void calculateTotal(const Item* head) {
    int totalQuantity = 0;
    double totalPrice = 0;
    const Item* temp = head;
    while (temp) {
        totalQuantity += temp->quantity;
        totalPrice += temp->price * temp->quantity;
        temp = temp->next;
    }
    cout << "Tong so luong cac san pham trong kho: " << totalQuantity << endl;
    cout << "Tong gia tri cac san pham trong kho: " << totalPrice << endl;
}

// Tính tong so luong va tong gia tri cua san pham da xuat
void calculateTotalSold(const Item* head) {
    int totalQuantity = 0;
    double totalPrice = 0;
    const Item* temp = head;
    while (temp) {
        totalQuantity += temp->quantity;
        totalPrice += temp->price * temp->quantity;
        temp = temp->next;
    }
    cout << "Tong so luong cac san pham da xuat: " << totalQuantity << endl;
    cout << "Tong gia tri cac san pham da xuat: " << totalPrice << endl;
}

int main() {
    Item* head = NULL;
    Item* soldHead = NULL;
    int choice;
    int id, quantity;
    char name[50];
    double price;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Them san pham\n";
        cout << "2. Sua thong tin san pham\n";
        cout << "3. Xoa san pham\n";
        cout << "4. Sap xep san pham theo ID\n";
        cout << "5. Sap xep san pham theo so luong\n";
        cout << "6. Sap xep san pham theo so tien\n";
        cout << "7. In ra danh sach san pham\n";
        cout << "8. Tinh tong so san pham va tong gia tri san pham";
        cout << "9. Xuat san pham\n";
        cout << "10. In ra danh sach san pham da xuat\n";
        cout << "11. Tinh tong so san pham va tong gia tri san pham da xuat\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap ID san pham: ";
                cin >> id;
                cout << "Nhap ten san pham: ";
                cin.ignore();
                cin.getline(name, 50);
                cout << "Nhap so luong san pham: ";
                cin >> quantity;
                cout << "Nhap gia tri san pham: ";
                cin >> price;
                addItem(head, id, name, quantity, price);
                pressAnyKey();
                break;

            case 2:
                cout << "Nhap ID san pham can sua: ";
                cin >> id;
                cout << "Nhap ten moi san pham: ";
                cin.ignore();
                cin.getline(name, 50);
                cout << "Nhap so luong moi cua san pham: ";
                cin >> quantity;
                cout << "Nhap gia tri moi cua san pham: ";
                cin >> price;
                if (!updateItem(head, id, name, quantity, price)) {
                    cout << "Khong tim thay san pham voi ID nay. " << id << endl;
                }
                pressAnyKey();
                break;

            case 3:
                cout << "Nhap ID san pham can xoa: ";
                cin >> id;
                if (!deleteItem(head, id)) {
                    cout << "Khong tim thay san pham voi ID nay. " << id << endl;
                }
                pressAnyKey();
                break;

            case 4:
                sortItemsID(head);
                cout << "Danh sach san pham duoc sap xep theo ID: \n";
                pressAnyKey();
                break;
            case 5:
                sortItemsQuantity(head);
                cout << "Danh sach san pham duoc sap xep theo so luong: \n";
                pressAnyKey();
                break;
            case 6:
                sortItemsPrice(head);
                cout << "Danh sach san pham duoc sap xep theo gia tien: \n";
                pressAnyKey();
                break;
            case 7:
                cout << "Danh sach san pham: \n";
                printItems(head);
                pressAnyKey();
                break;

            case 8:
                calculateTotal(head);
                pressAnyKey();
                break;

            case 9:
                cout << "Nhap ID san pham can xuat:  ";
                cin >> id;
                cout << "Nhap so luong can xuat: ";
                cin >> quantity;
                exportItem(head, soldHead, id, quantity);
                pressAnyKey();
                break;

            case 10:
                cout << "Danh sach san pham da xuat: \n";
                printSoldItems(soldHead);
                pressAnyKey();
                break;

            case 11:
                calculateTotalSold(soldHead);
                pressAnyKey();
                break;

            case 0:
                cout << "Thoat khoi chuong trinh.\n";
                return 0;

            default:
                cout << "\nKhong co chuc nang nay! ";
                cout << "\nHay chon chuc nang phu hop trong menu. ";
                pressAnyKey();
                break;
        }
    }
}
