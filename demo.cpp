#include <iostream>
#include <string.h>
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
typedef struct list_item{ 
  node_item *phead = NULL;
  node_item *ptail = NULL;	
}list_item;
void menu();
void input(item &a);
node_item* create_node(item x);
void add_item(list_item &L,item x);
void output(list_item L);
void del_item(list_item &L, string a);
void sortItemsPrice(list_item &L);
void Total(list_item &L);
void load_file(list_item L);
int main(){
	menu();
	system("pause");
}
void menu(){ // Xu ly chinh
	//setting
	list_item L;
	//menu
	bool kt_menu = true;
	while (kt_menu == true){  
   cout << "-------------------------Menu-------------------------\n"; 
   cout << "1. Nhap thong tin san pham\n";
   cout << "2. Hien thi thong tin san pham\n";
   cout << "3. Xoa san pham theo ID\n";
   cout << "4. Sap xep theo gia tu cao den thap\n";
   cout << "5. Tong gia tien va so luong san pham\n";
   cout << "6. Xuat ra file 'Quan_ly_kho' \n";
   cout << "0. Thoat!\n";
   int chon;cin>>chon;
   switch(chon){
   case 1:
   {   
       int sl;cout << "Nhap so luong thong tin ve san pham can them:\n";cin>>sl;
      
   	   for(int i = 1;i<=sl;i++){ 
		 cin.ignore();
	     cout <<"\t\t----------Nhap Item "<< i <<"----------"<<endl;
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
   case 3:
   {
   	  string a;
   	  cin.ignore();
	  cout <<"Nhap ID cua san pham can xoa:";getline(cin,a);
	  del_item(L,a);
	  break;
   } 
   case 4:
   {
	  sortItemsPrice(L);
	  system("pause");
	  break;
   }
   case 5:
   {
   	Total(L);
   	system("pause");
	break;
   }
   case 6:{
	load_file(L);
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
void input(item &a){ // Nhap thong tin san pham 
	cout << "Nhap ma san pham: ";getline(cin,a.id);
	cout << "Nhap ten san pham: ";getline(cin,a.name);
	cout << "Nhap gia(VND): "; cin >> a.price;
	cout << "Nhap so luong: "; cin>> a.quantity;
}
node_item* create_node(item x){// luu data nguoi dung nhap
	node_item *p = new node_item;// cap bo nho dong 
	p->data = x; // gan x cho data luu tru
	p->pnext = NULL; 
}
void add_item(list_item &L, item x){
	node_item *p = create_node(x);
	if(L.phead == NULL){ //danh sach rong 
		L.phead = L.ptail = p;// dau cuoi la 1 
	}
	else{//danh sach chua n phan tu
		L.ptail->pnext=p; 
		L.ptail = p;
	}
}	
void output(list_item L){   
    int i = 1;
	for(node_item *k= L.phead;k != NULL; k=k->pnext){ // Duyet danh sach tu dau dau den cuoi 
		cout<<"\t\t--------Item "<< i++ <<"--------"<<endl; 
		cout<<"ID:"<< k->data.id << endl; 
		cout<<"Ten san pham:"<< k->data.name << endl; 
		cout<<"Gia:"<< k->data.price << endl; 
		cout<<"So luong:"<< k->data.quantity << endl; 
	}
}
void del_item(list_item &L, string a){
	node_item *h = NULL;
	for(node_item *k = L.phead;k != NULL;){
		if(_stricmp(k->data.id.c_str(),a.c_str())== 0 && k == L.phead){ //So sanh theo xau ky tu 
		//check ID dau tien danh sach
			L.phead = L.phead -> pnext;
			delete k; 
			k = L.phead;
		}
		else { // neu ID nhap vao khac ID dau tien	
			if(_stricmp(k->data.id.c_str(),a.c_str())== 0){
				h -> pnext = k-> pnext; // cho con tro h chay lan luot den vi tri tiep theo roi xoa
				delete k;
			if(h -> pnext == NULL){ // check den cuoi roi xoa cuoi
				L.ptail = h;
				return;
			}		
			}
			h = k;
			k = k -> pnext;// buoc lap 
		}
	}
}
void sortItemsPrice(list_item &L) {// ham thay doi vi tri theo gia ca tu cao den thap
    for(node_item* k = L.phead ; k!= NULL;k = k->pnext){ // duyet tu dau danh sach den cuoi
    	for(node_item* h = k->pnext; h!= NULL;h = h->pnext){ // them 1 con tro duyet tu vi tri thu 2 dau den cuoi
    	if(h->data.price > k->data.price){
    		swap(k->data, h->data);// hoan doi neu thoa man
		}
		else if(h->data.price == k->data.price){ // neu bang nhau thi so sanh ve so luong 
			if(h->data.quantity > k->data.quantity){
				swap(k->data , h->data);// hoan doi theo so luong
			}	
		}
		}	
	}
}
void Total(list_item &L){ // ham tong gia va so luong san pham
	int s_quantity = 0; // tong so luong ban dau 
	double s_price = 0; // tong so luong sau 
	for(node_item* k = L.phead ; k!= NULL;k = k->pnext){ 
	   s_quantity += k->data.quantity ;
	   s_price += k->data.price;
	}
	cout << "Tong gia tien : " << s_price <<endl;
	cout << "Tong so luong : " << s_quantity  <<endl;
}
void load_file(list_item L){ // xuat file 
	ofstream filein("Quan_ly_kho.txt"); // xuat file voi ten file theo kem 
	for(node_item* k = L.phead ; k!= NULL;k = k->pnext){ 
	// cac thao tac xuat file tu dau danh sach den cuoi
	filein << "ID: " << k->data.id <<endl;
	filein << "name: " <<k->data.name <<endl;
	filein << "Price: " <<k->data.price <<endl;
	filein << "Quantity: " <<k->data.quantity <<endl;
	}
	filein.close();
}






















