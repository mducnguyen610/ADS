#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
typedef struct item{
	string id, name;
	int quantity;
	unsigned long long price;
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
void input(item &a);//nhap san pham
node_item* create_node(item x);//tao node dung de luu data
void add_item(list_item &L,item x);//them san pham vao dslk
void output(list_item L);// xuat san pham
void update_item(list_item &L, item &x);// cap nhat san pham theo id
void del_item(list_item &L, string a);//xoa 1 san pham theo id
void sortItemsPrice(list_item &L);// thay doi vi tri sp trong dslk theo gia
void Total(list_item &L);//ham tong tien va tong so luong
void load_file(list_item L);//xuat file ra "Quan_ly_kho.txt"
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
   cout << "3. Sua thong tin san pham\n";
   cout << "4. Xoa san pham theo ID\n";
   cout << "5. Sap xep theo gia tu cao den thap\n";
   cout << "6. Tong gia tien va so luong san pham\n";
   cout << "7. Xuat ra file 'Quan_ly_kho' \n";
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
   {   item y;
       cin.ignore();
	   update_item(L,y);
	   break;
   }
   case 4:
   {
   	   string a;
   	   cin.ignore();
	   cout <<"Nhap ID cua san pham can xoa:";getline(cin,a);
	   del_item(L,a);
	   break;
   } 
   case 5:
   {
	   sortItemsPrice(L);
	   break;
   }
   case 6:
   {
   	   Total(L);
   	   system("pause");
	   break;
   }
   case 7:
   {
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
	p->data = x; // gan x truc tiep cho data luu tru
	p->pnext = NULL;  
	return p;
}
void add_item(list_item &L, item x){ // ham luu vao danh
	node_item *p = create_node(x);// gan ham luu data cho con tro khoi tao 
	if(L.phead == NULL){ //danh sach rong 
		L.phead = L.ptail = p;// dau cuoi la 1 roi gan cho data  
	}
	else{//danh sach chua n phan tu
		L.ptail->pnext=p; // them cuoi
		L.ptail = p;//cap nhat lai ptail
	}
}	
void output(list_item L){ // ham xuat danh sach
    int i = 1;
	for(node_item *k= L.phead;k != NULL; k=k->pnext){ // Duyet danh sach tu dau dau den cuoi 
		cout<<"\t\t--------Item "<< i++ <<"--------"<<endl; 
		cout<<"ID:"<< k->data.id << endl; 
		cout<<"Ten san pham:"<< k->data.name << endl; 
		cout<<"Gia:"<< k->data.price << endl; 
		cout<<"So luong:"<< k->data.quantity << endl; 
	}
}
void update_item(list_item &L, item &x){// ham cap nhat danh sach theo ID
	cout << "Nhap ID san pham can thay doi: ";getline(cin,x.id);
	cout << "Nhap ten san pham moi: ";getline(cin,x.name);
	cout << "Nhap gia(VND) moi: "; cin >> x.price;
	cout << "Nhap so luong moi: "; cin>> x.quantity;
	for(node_item* k = L.phead ; k!= NULL;k = k->pnext){ // Duyet con tro tu dau dslk den cuoi
  	  	if(_stricmp(k->data.id.c_str(),x.id.c_str())== 0){ // tim kiem ID cua san pham can thay doi
  	  		k->data = x;// chuyen du lieu vua nhap vao 
			}
	}	
}	
void del_item(list_item &L, string a){//xoa 1 san pham theo id
	node_item *h = NULL;
	for(node_item *k = L.phead;k != NULL;){
		if(_stricmp(k->data.id.c_str(),a.c_str())== 0 && k == L.phead){ //So sanh theo xau ky tu 
		//check ID dau tien danh sach
			L.phead = L.phead -> pnext;
			delete k; // xoa du lieu con tro k
			k = L.phead; // cap nhat lai k
		}
		else { // neu ID nhap vao khac ID dau tien	
			if(_stricmp(k->data.id.c_str(),a.c_str())== 0){ //So sanh theo xau ky tu
				h -> pnext = k-> pnext; // cho con tro h chay lan luot den vi tri tiep theo 
				delete k;//xoa du lieu
			if(h -> pnext == NULL){ // check den cuoi roi xoa cuoi
				L.ptail = h;
				return;
			}		
			}
			h = k;// cap nhat lai du lieu
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
	unsigned long long s_price = 0; // tong so luong sau 
	for(node_item* k = L.phead ; k!= NULL;k = k->pnext){ //Duyet danh sach lien ket
	   s_quantity += k->data.quantity ; // duyet roi cong them so luong
	   s_price += (k->data.price)*(k->data.quantity);//duyet cong them gia * so luong cua san pham do
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



















