#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

template<typename Tkey, typename Tval>
class Map{
private:
    struct conformity{
        Tkey key;
        Tval value;
    };
    conformity* con_array;
    int size;
    int insize;
public:
    Map():size(1), insize(0){
        con_array = new conformity[size];
    }

    Map(const Map & arr){
        insize = arr.insize;
        size = arr.size;
        con_array = new conformity[size];
        for(int i=0; i<insize;i++){
            con_array[i].key = arr.con_array[i].key;
            con_array[i].value=arr.con_array[i].value;
        }
    }

    void add(Tkey key, Tval value){                        // добавление в массив. Добавить проверку на ключ
        if(size==insize){
            conformity* old_con = con_array;
            con_array = new conformity[size+10];
            memcpy(con_array, old_con, sizeof(conformity) *size);
            size += 10;
            delete old_con;
        }
        conformity ct;
        ct.key = key;
        ct.value = value;
        con_array[insize++] = ct;
    }



    ~Map(){
        delete [] con_array;
    }

};
 int main(){

 }
