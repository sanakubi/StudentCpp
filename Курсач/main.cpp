#include <iostream>
#include <fstream>
#include <string.h>

#define esc 27
#define cls printf("%c[2J",esc)	 //ШОБ ЭКРАН ОБНОВЛЯЛСЯ, А НЕ ТУДА-СЮДА ДЕЛАЛ ГЫ

using namespace std;
// ОБЪЕКТ ПОЕЗД
class Train{
public:
	string City = "";
	string Time = "";

	friend ostream& operator<<(ostream& out, Train& X){
		out<<X.City<<" "<<X.Time;
		return out;
	}
	friend istream& operator>>(istream& in, Train& X){
		in>>X.City>>X.Time;
		return in;
	}
	friend bool operator==(Train& A, Train& B) {
		return(A.Time == B.Time && A.City == B.City);
	} 
}; /**/
// КОЛЛЕКЦИЯ ПОД ПОЕЗД (В ДАННОМ СЛУЧАЕ ПЕРЕМЕННАЯ TRAIN - САМО ЗНАЧЕНИЕ)
template<typename Tkey, typename Ttrain>
class Map {
private:
	struct conformity {
		Tkey key;
		Ttrain train;;
	};
	conformity* con_array;
	int size;
	int insize;
public:
	Map() : size(4), insize(0) {
		con_array = new conformity[size];
	}
	Map(const Map& arr) {
		size = arr.size;
		insize = arr.insize;
		con_array = new conformity[size];
		for (int i = 0; i < insize; i++) {
			con_array[i].key = arr.con_array[i].key;
			con_array[i].train = arr.con_array[i].train;
		}
	}

	~Map() {
		delete[] con_array;
	}
	void add(Tkey key, Ttrain train) {
		bool check = true;               // добавление в массив. Добавить проверку на ключ
		for (int i = 0; i < insize; i++) {
			if (con_array[i].key == key) check = false;
		}
		if (check == true) {
			if (insize == size) {
				conformity* old = con_array;
				con_array = new conformity[size + 2];
				memcpy(con_array, old, sizeof(conformity) + 2);
				size += 2;
				delete old;
			}
			conformity ct;
			ct.key = key;
			ct.train = train;
			con_array[insize++] = ct;
		}else if (check == false) {
			cout << ">ERROR_ADD: KEY " << key << " ALREADY ADDED" << endl;
		}
	}
	void del(Tkey key) {
		bool check = false;
		for (int i = 0; i < insize; i++) {
			if (con_array[i].key == key) check = true;
		}
		if (check == true) {
			conformity* temp_con = new conformity[size];
			memcpy(temp_con, con_array, sizeof(conformity) * size);
			this->~Map();
			size = 4;
			int ins = insize;
			insize = 0;
			con_array = new conformity[size];
			for (int i = 0; i < ins; i++)
				if (temp_con[i].key != key) {
					add(temp_con[i].key, temp_con[i].train);
				}
		}else if (check == false) {
			cout << ">ERROR_DEL: KEY " << key << " DOESN'T EXIST" << endl;
		}

	}		
	void print() {
		for (int i = 0; i < insize; i++) {
			cout << con_array[i].key << " " << con_array[i].train << endl;
		}
	}
	/* City& operator[](Tkey key){
		 for (int i = 0; i < len; i++){
			 if (pairs[i].key == key){
				 return pairs[i].value;
			 }
		 }
		 throw;
	 } */
	void samesign(Ttrain train) {
		for (int i = 0; i < insize; i++)if (con_array[i].train == train) cout << con_array[i].train;
	}
	/* void samesign(Tcity city){
		for(int i=0;i<insize;i++)if(con_array[i].city == city) cout<< con_array[i].city;
	} */

	void savelist() {
		ofstream out;
		out.open("board.txt");
		for (int i = 0; i < insize; i++) {
			if (i == insize - 1) {
				out << con_array[i].key << endl << con_array[i].train << endl;
			}
		}
	}

	void getlist() {
		bool end = 1;
		ifstream lst; lst.open("board.txt");
		if (!lst) { cout << "Error " << endl; }
		else {
			Tkey key;
			Ttrain train;
			while (!lst.eof()) {
				lst>>key;
				lst>>train;
				add(key, train);
			}
		}
		lst.close();
	}

};
int main() {
	Map<int, string> Board;
	Board.add(1, "Chel");
	Board.add(2, "Mosk");
	Board.add(2, "Mosk");
	Board.add(8, "Mosk");
	Board.del(3);

	Board.print();

	//// MENU ////
	setlocale(LC_ALL, "Russian");
}
