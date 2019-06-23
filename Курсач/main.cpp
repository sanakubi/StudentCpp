	#include <iostream>
	#include <fstream>
	#include <string.h>
	#define cls printf("%c[2J",27)	

	using namespace std;
	class Train_{
	public:
		string City;
		string Time;

		Train_() {
			City = "";
			Time = "";
		}

		Train_(string City, string Time)  : City(City), Time(Time) {}

		friend ostream& operator<<(ostream& out, Train_& X){
			out<<X.City<<" "<<X.Time;
			return out;
		}
		friend istream& operator>>(istream& in, Train_& X){
			in>>X.City>>X.Time;
			return in;
		}
		friend bool operator==(Train_& A, Train_& B) {
			return(A.Time == B.Time && A.City == B.City);
		} 
	}; 

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
			bool check = true;              
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
				delete[] con_array;
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
		
		friend ostream& operator<<(ostream& out, Map& X) {
			for (int i = 0; i < X.insze; i++) out << X.con_array[i].key << " " << X.con_array[i].train << endl;
			return out;
		}

		friend istream& operator<<(istream& in, Map& X) {
			Tkey key; Ttrain train;
			in>>key;
			in>>train;
			X.insert(key, train);
			return in;
		}

		void print() {
			for (int i = 0; i < insize; i++) {
				cout << con_array[i].key << " " << con_array[i].train << endl;
			}
		}
		void samesign(Ttrain train) {
			for (int i = 0; i < insize; i++)if (con_array[i].train == train) cout << con_array[i].train;
		}

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
		Map<int, Train_> Board;
		Board.getlist();
		Board.print();
		cout << endl;
		Board.add(8,Train_("df", "er"));
		Board.print();
		//// MENU ////
		setlocale(LC_ALL, "Russian");

	}
