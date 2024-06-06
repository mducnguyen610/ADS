#include<conio.h>
#include<stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

// Định nghĩa cấu trúc của mặt hàng bao gồm id, tên, số lượng, giá cả và đi kèm con trỏ
struct Item {
    int id;
    char name[50];
    int quantity;
    double price;
    Item* next;
};

void pressAnyKey() {
    cout << "\n\nBấm phím bất kỳ để tiếp tục...";
    getch();
    system("cls");
}

// Thêm một mặt hàng mới
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

// Sửa thông tin mặt hàng
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

// Xóa mặt hàng
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

// Đổi thông tin giữa các mặt hàng cho nhau để sắp xếp trong danh sách
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

// Sắp xếp theo ID từ bé đến lớn
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

// Sắp xếp theo số lượng từ bé đến lớn
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

// In ra danh sách mặt hàng
void printItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << std::endl;
        temp = temp->next;
    }
}

// Hàm xuất hàng
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
                cout << "Không đủ số lượng hàng trong kho để xuất." << endl;
                return;
            }
        }
        temp = temp->next;
    }
    cout << "Không tìm thấy mặt hàng với ID này." << endl;
}

// In ra danh sách sản phẩm đã xuất
void printSoldItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << std::endl;
        temp = temp->next;
    }
}

// Tính tổng số lượng và giá trị của các sản phẩm
void calculateTotal(const Item* head) {
    int totalQuantity = 0;
    double totalPrice = 0;
    const Item* temp = head;
    while (temp) {
        totalQuantity += temp->quantity;
        totalPrice += temp->price * temp->quantity;
        temp = temp->next;
    }
    cout << "Tổng số lượng các sản phẩm trong kho: " << totalQuantity << endl;
    cout << "Tổng giá trị các sản phẩm trong kho: " << totalPrice << endl;
}

// Tính tổng số lượng và giá trị của các sản phẩm đã xuất
void calculateTotalSold(const Item* head) {
    int totalQuantity = 0;
    double totalPrice = 0;
    const Item* temp = head;
    while (temp) {
        totalQuantity += temp->quantity;
        totalPrice += temp->price * temp->quantity;
        temp = temp->next;
    }
    cout << "Tổng số lượng các sản phẩm đã xuất: " << totalQuantity << endl;
    cout << "Tổng giá trị các sản phẩm đã xuất: " << totalPrice << endl;
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
        cout << "1. Thêm mặt hàng\n";
        cout << "2. Sửa thông tin mặt hàng\n";
        cout << "3. Xóa mặt hàng\n";
        cout << "4. Sắp xếp mặt hàng theo ID\n";
        cout << "5. In ra danh sách mặt hàng\n";
        cout << "6. Tính tổng số lượng và giá trị các sản phẩm\n";
        cout << "7. Xuất hàng\n";
        cout << "8. In ra danh sách sản phẩm đã xuất\n";
        cout << "9. Tính tổng số lượng và giá trị các sản phẩm đã xuất\n";
        cout << "0. Thoát\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhập ID mặt hàng: ";
                cin >> id;
                cout << "Nhập tên mặt hàng: ";
                cin.ignore();
                cin.getline(name, 50);
                cout << "Nhập số lượng của mặt hàng: ";
                cin >> quantity;
                cout << "Nhập giá: ";
                cin >> price;
                addItem(head, id, name, quantity, price);
                pressAnyKey();
                break;

            case 2:
                cout << "Nhập ID mặt hàng cần sửa: ";
                cin >> id;
                cout << "Nhập tên mới của mặt hàng: ";
                cin.ignore();
                cin.getline(name, 50);
                cout << "Nhập số lượng mới của mặt hàng: ";
                cin >> quantity;
                cout << "Nhập giá mới của mặt hàng: ";
                cin >> price;
                if (!updateItem(head, id, name, quantity, price)) {
                    cout << "Không tìm thấy mặt hàng với ID này: " << id << endl;
                }
                pressAnyKey();
                break;

            case 3:
                cout << "Nhập ID mặt hàng bạn muốn xóa: ";
                cin >> id;
                if (!deleteItem(head, id)) {
                    cout << "Không tìm thấy mặt hàng với ID này: " << id << endl;
                }
                pressAnyKey();
                break;

            case 4:
                sortItemsID(head);
                cout << "Danh sách mặt hàng đã được sắp xếp theo ID:\n";
                pressAnyKey();
                break;

            case 5:
                cout << "Danh sách mặt hàng:\n";
                printItems(head);
                pressAnyKey();
                break;

            case 6:
                calculateTotal(head);
                pressAnyKey();
                break;

            case 7:
                cout << "Nhập ID mặt hàng cần xuất: ";
                cin >> id;
                cout << "Nhập số lượng cần xuất: ";
                cin >> quantity;
                exportItem(head, soldHead, id, quantity);
                pressAnyKey();
                break;

            case 8:
                cout << "Danh sách sản phẩm đã xuất:\n";
                printSoldItems(soldHead);
                pressAnyKey();
                break;

            case 9:
                calculateTotalSold(soldHead);
                pressAnyKey();
                break;

            case 0:
                cout << "Thoát chương trình.\n";
                return 0;

            default:
                cout << "\nKhông có chức năng này!";
                cout << "\nHãy chọn chức năng trong hợp menu.";
                pressAnyKey();
                break;
        }
    }
}
