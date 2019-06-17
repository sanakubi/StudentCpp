#include<iostream>
#include<cstring>

using namespace std;

class train{
    char name[256];
    int number;
public:
    train(char name[] = "none", int number = 0){
        this->number=number;
        strcpy(this-> name, name);
        //this->name[]="none";
    }
    void set_num(){
        cout<<"Введите номер поезда: ";
        cin>>number;
        cout<<endl;
    }
    void get_num(){
        cout<<"Номер поезда: "<<number<<endl;
    }
};

int main(){
    setlocale(LC_ALL, "Russian");
    int n;
    cin>>n;
    train vokzal[n];
    for(int i=0;i<n;i++){
        vokzal[i].set_num();
        cout<<endl;
    }
        for(int i=0;i<n;i++){
        vokzal[i].get_num();
        cout<<endl;
    }
    return 0;
}


