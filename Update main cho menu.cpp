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

//Them mot mat hang moi
void addItem(Item*& head, int id, const char* name, int quantity, double price) {
    Item* newItem = new Item; //Khoi tao
    //Gan id, ten, so luong, gia ca vs con tro cho mat hang
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;
	//Neu danh sach rong thi con tro la mat hang dau danh sach
    if (!head) {
        head = newItem; //gan bang vi tri head
    } else {
        Item* temp = head; 
        while (temp->next) { //Con neu ko thi duyet xuong cuoi danh sach
            temp = temp->next;
        }
        temp->next = newItem;//Them mat hang moi nay vao cuoi danh sach
    }
}
//Sua thong tin mat hang
bool updateItem(Item* head, int id, const char* name, int quantity, double price) {
    Item* temp = head;
    while (temp) {
        if (temp->id == id) {		//Tim mat hang bang id co san ma ng dung muon thay doi
        	//Cap nhat thong tin moi
            strcpy(temp->name, name);
            temp->quantity = quantity;
            temp->price = price;
            return true; 	//Tra ve true khi cap nhat thanh cong
        }
        temp = temp->next;
    }
    return false; //Tra ve false neu mat hang can tim ko ton tai
}
//Xoa mat hang
bool deleteItem(Item*& head, int id) {
    if (!head) return false;	//Tra ve false neu ds rong
    if (head->id == id) {
        Item* temp = head;		//Tao mot con tro tam thoi
        head = head->next;		//Cap nhat dau danh sach
        delete temp;			//Xoa mat hang
        return true;			//Tra ve true khi thanh cong
    }
    Item* prev = head;			//Khoi tao con tro prev tro den phan tu dau tien
    Item* current = head->next;	//Khoi tao con tro current tro den phan tu t2
    while (current) {			//Chay vong lap cho den khi current bang NULL (duyet cac id tu dau den cuoi danh sach)
        if (current->id == id) {//Tim id trung vs id cua mat hang can xoa
            prev->next = current->next;//Tim thay roi thi cap nhat con tro next cho prev de bo qua current
            delete current;		//Xoa current (mat hang hien tai dc chon de xoa)
            return true;		//Tra ve true khi thanh cong
        }
        prev = current;			//Cap nhat mat hang dung truoc vao vi tri mat hang vua xoa de tro den phan tu ke tiep
        current = current->next;
    }
    return false; //Tra ve false neu ko tim dc mat hang
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

    int tempQuantity = a->quantity;	//Hoan doi so luon
    a->quantity = b->quantity;
    b->quantity = tempQuantity;

    double tempPrice = a->price;	//Hoan doi gia
    a->price = b->price;
    b->price = tempPrice;
}
//Sap xep theo ID
void sortItems(Item*& head) {
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
int main() {
    Item* head = NULL;
	int choice;				//Bien lua chon thao tac tren menu
	//Giao dien menu
	do{
		cout<<"\nMenu: \n";
		cout<< "1. Them mat hang\n";
        cout<< "2. Sua thong tin mat hang\n";
        cout<< "3. Xoa mat hang\n";
        cout<< "4. Sap xep mat hang\n";
        cout<< "5. In ra danh sach mat hang\n";
        cout<< "0. Thoat\n";
        cout<< "Lua chon cua ban: ";
        cin >> choice;
	}
	
	//Cai dat ham thao tac voi menu
	switch(choice){
		case 1:{
			int id, quantity;
			char name[50];
			double price;
			cout<< "Nhap ID mat hang: ";cin >> id;
			cout<< "Nhap ten mat hang: ";cin.ignore();cin.getline(name, 50);
            cout<< "Nhap so luong cua mat hang: ";cin >> quantity;
            cout<< "Nhap gia: ";cin >> price;
			break;
		}
		case 2:{
			int id, quantity;
			char name[50];
			double price;
			cout<< "Nhap ID mat hang can sua: ";cin >> id;
			cout<< "Nhap ten moi cua mat hang: ";cin.ignore();cin.getline(name, 50);
            cout<< "Nhap so luong moi cua mat hang: ";cin >> quantity;
            cout<< "Nhap gia moi cua mat hang: ";cin >> price;
            if(!updateItem(head, id, name, quatity, price)){
            	cout<<"Khong tim thay mat hang voi ID nay: "<<id<<endl;
			}
			break;
		}
		case 3:{
			int id;
			cout<<"Nhap ID mat hang ban muon xoa: ";
			cin>>id;
			if(!deleteItem(head, id)){
				cout<<"Khong tim thay mat hang voi ID nay: "<<endl;
			}
			break;
		}
		case 4:{
			sortItem(head);
			cout<<" Danh sach mat hang da duoc sap xep theo ID:\n"
			break;
		}
		case 5{
			cout<<"Danh sach mat hang:\n";
			break;
		}
		case 0:{
			cout<<"Thoat chuong trinh.\n";
			break;
		}
		default:{
			cout<<"Lua chon khong hop le! Vui long chon lai.\n"
			break;
		}
	}while (choide !=0);
	
	return 0;
}
