#include <iostream>
#include <string>
#include <fstream>
using namespace std;
typedef struct item{
	string id, name;
	int quantity;
	double price;
}item;
struct node_item{
	//data
	item data;
	//pointer
	node_item *pnext;
};
typedef struct node_item node_item;
typedef struct list_item{
  node_item *phead = NULL;
  node_item *ptail = NULL;	
}list_item;
void menu();
void input(item &a);
node_item* create_node(item x);
void add_item(list_item &L,item x);
void output(list_item L);
int main(){
	menu();
	system("pause");
}
void menu(){
	//setting
	list_item L;
	//menu
	bool kt_menu = true;
	while (kt_menu == true){  
   cout << "-------------------------Menu-------------------------\n"; 
   cout << "1. Nhap thong tin san pham\n";
   cout << "2. Hien thi thong tin san pham\n";
   cout << "0. Thoat!\n";
   int chon;cin>>chon;
   switch(chon){
   case 1:
   {   
       int sl;cout << "Nhap so luong san pham can them:\n";cin>>sl;
      
   	   for(int i = 1;i<=sl;i++){ 
		 cin.ignore();
	     cout <<"\t\t----------Nhap Item"<< i <<"----------"<<endl;
	     item x;
	     input(x);
	     add_item(L,x);
		 }
		 break;
   }
   case 2:
   {
	   output(L);
	   system("pause");
	   break;
   }	
   case 0:
   {
   	   kt_menu = false;
	   break;
   }
   }
}
}
void input(item &a){
	cout << "Nhap ma san pham: ";getline(cin,a.id);
	cout << "Nhap ten san pham: ";getline(cin,a.name);
	cout << "Nhap gia: "; cin >> a.price;
	cout << "Nhap so luong: "; cin>> a.quantity;
}
node_item* create_node(item x){// luu data nguoi dung nhap
	node_item *p = new node_item;
	p->data = x;
	p->pnext = NULL;
	return p;
}
void add_item(list_item &L, item x){
	node_item*p = create_node(x);
	if(L.phead == NULL){ //danh sach rong 
		L.phead = L.ptail = p;
	}
	else{//danh sach chua n phan tu
		L.ptail->pnext=p;
		L.ptail = p;
	}
}	
void output(list_item L){   
    int i = 1;
	for(node_item *k= L.phead;k != NULL; k=k->pnext){
		cout<<"\t\t--------Item "<< i++ <<"--------"<<endl; 
		cout<<"ID:"<< k->data.id << endl; 
		cout<<"Ten san pham:"<< k->data.name << endl; 
		cout<<"Gia:"<< k->data.price << endl; 
		cout<<"So luong:"<< k->data.quantity << endl; 
	}
}
