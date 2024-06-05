#include<conio.h>
#include<stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
//Dinh nghia cau truc cua mat hang bao gom id, ten, so luong, gia ca va di kem con tro
struct Item {
    int id;
    char name[50];
    int quantity;
    double price;
    Item* next;
};

}
//Doi thong tin giua cac mat hang cho nhau de sap xep trong danh sach
void swapItems(Item* a, Item* b) {
    int tempId = a->id; //Hoan doi id
    a->id = b->id;
    b->id = tempId;

    char tempName[50];	//Hoan doi ten
    strcpy(tempName, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tempName);

    int tempQuantity = a->quantity;	//Hoan doi so luong
    a->quantity = b->quantity;
    b->quantity = tempQuantity;

    double tempPrice = a->price;	//Hoan doi gia
    a->price = b->price;
    b->price = tempPrice;
}
//Sap xep theo ID tu be den lon
void sortItemsID(Item*& head) {
    if (!head) return;	//Ds rong thi ko lam gi
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->id > current->next->id) { //Kiem tra id mat hang hien tai co lon hon id mat hang ke tiep
                swapItems(current, current->next);//Hoan doi thong tin 2 mat hang
                swapped = true;	//Danh dau da hoan doi
            }
            current = current->next;
        }
    } while (swapped);
}

//Sap xep theo so luong tu be den lon
void sortItemsQuantity(Item*& head) {
    if (!head) return;	//Ds rong thi ko lam gi
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->price > current->next->price) { //Kiem tra gia tien mat hang hien tai co lon hon mat hang ke tiep
                swapItems(current, current->next);//Hoan doi thong tin 2 mat hang
                swapped = true;	//Danh dau da hoan doi
            }
            current = current->next;
        }
    } while (swapped);
}

//Sap xep theo gia tien tu be den lon
void sortItemsPrice(Item*& head) {
    if (!head) return;	//Ds rong thi ko lam gi
    bool swapped;
    do {
        swapped = false;
        Item* current = head;
        while (current->next) {
            if (current->id > current->next->id) { //Kiem tra id mat hang hien tai co lon hon id mat hang ke tiep
                swapItems(current, current->next);//Hoan doi thong tin 2 mat hang
                swapped = true;	//Danh dau da hoan doi
            }
            current = current->next;
        }
    } while (swapped);
}

//In ra danh sach mat hang
void printItems(const Item* head) {
    const Item* temp = head;
    while (temp) {
        cout << "ID: " << temp->id << ", Name: " << temp->name
                  << ", Quantity: " << temp->quantity << ", Price: " << temp->price << std::endl;
        temp = temp->next;
    }
}

