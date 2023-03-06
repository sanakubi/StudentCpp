#include <iostream>
#include <cmath>
#include<math.h>

//int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200 };
//int y[] = { 9411.0f, 9364.0f, 9341.0f, 9327.0f, 9316.0f, 9304.0f, 9300.0f, 9291.0f, 9286.0f, 9280.0f, 9278.0f, 9276.0f, 9269.0f, 9270.0f, 9268.0f, 9262.0f, 9256.0f, 9258.0f, 9258.0f, 9252.0f, 9246.0f, 9248.0f, 9242.0f, 9244.0f, 9245.0f, 9241.0f, 9239.0f, 9238.0f, 9234.0f, 9232.0f, 9235.0f, 9227.0f, 9231.0f, 9231.0f, 9230.0f, 9231.0f, 9226.0f, 9222.0f, 9220.0f, 9226.0f, 9219.0f, 9214.0f, 9217.0f, 9219.0f, 9218.0f, 9215.0f, 9217.0f, 9215.0f, 9211.0f, 9211.0f, 9211.0f, 9208.0f, 9211.0f, 9212.0f, 9207.0f, 9210.0f, 9207.0f, 9207.0f, 9210.0f, 9201.0f, 9204.0f, 9202.0f, 9203.0f, 9202.0f, 9203.0f, 9202.0f, 9200.0f, 9198.0f, 9199.0f, 9193.0f, 9194.0f, 9193.0f, 9199.0f, 9196.0f, 9192.0f, 9192.0f, 9194.0f, 9193.0f, 9194.0f, 9195.0f, 9197.0f, 9198.0f, 9195.0f, 9193.0f, 9190.0f, 9189.0f, 9190.0f, 9191.0f, 9187.0f, 9191.0f, 9191.0f, 9190.0f, 9191.0f, 9188.0f, 9188.0f, 9188.0f, 9188.0f, 9188.0f, 9186.0f, 9185.0f, 9188.0f, 9182.0f, 9182.0f, 9186.0f, 9189.0f, 9188.0f, 9188.0f, 9183.0f, 9185.0f, 9182.0f, 9182.0f, 9182.0f, 9184.0f, 9182.0f, 9183.0f, 9183.0f, 9180.0f, 9181.0f, 9179.0f, 9182.0f, 9179.0f, 9177.0f, 9178.0f, 9180.0f, 9178.0f, 9177.0f, 9178.0f, 9177.0f, 9177.0f, 9182.0f, 9177.0f, 9171.0f, 9175.0f, 9179.0f, 9177.0f, 9175.0f, 9174.0f, 9177.0f, 9175.0f, 9177.0f, 9174.0f, 9177.0f, 9179.0f, 9178.0f, 9175.0f, 9172.0f, 9176.0f, 9176.0f, 9175.0f, 9178.0f, 9178.0f, 9174.0f, 9174.0f, 9176.0f, 9176.0f, 9173.0f, 9175.0f, 9172.0f, 9174.0f, 9175.0f, 9174.0f, 9178.0f, 9174.0f, 9173.0f, 9174.0f, 9172.0f, 9177.0f, 9178.0f, 9172.0f, 9175.0f, 9171.0f, 9175.0f, 9173.0f, 9173.0f, 9174.0f, 9168.0f, 9171.0f, 9173.0f, 9165.0f, 9166.0f, 9170.0f, 9168.0f, 9169.0f, 9174.0f, 9173.0f, 9170.0f, 9168.0f, 9171.0f, 9174.0f, 9167.0f, 9167.0f, 9170.0f, 9170.0f, 9169.0f, 9169.0f, 9167.0f, 9168.0f, 9167.0f, 9175.0f, 9171.0f };

double x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
double y[] = { 1000, 900, 810, 720, 640, 550, 460, 370, 280, 19,};

int N = 10;//200;
double a, b;

double GetOne(double* arr, int pw){
    int x_fin, size;
    x_fin = size = 0;
    size = N;
    for (int i = 0; i < size; i++) {
        x_fin += powf(x[i], pw);
    }
    return x_fin;
}

double GetOneLog(double* arr) {
    int x_fin, size;
    x_fin = size = 0;
    size = N;
    for (int i = 0; i < size; i++) {
        x_fin += log(x[i]);
    }
    return x_fin;
}

double GetLnPw(double* arr_one) {
    int x_fin, size;
    x_fin = size = 0;
    size = N;
    for (int i = 0; i < size; i++) {
        x_fin += powf(log(x[i]), 2);
    }
    return x_fin;
}

double GetXLnY(double* arr_one, double* arr_two){
    int xy_fin, size = 0;
    xy_fin = size = 0;
    size = N;
    for (int i = 0; i < size; i++) {
        xy_fin += arr_one[i] * log(arr_two[i]);
    }
    return xy_fin;
}
/***/

void GetB_Exp() {
    b = ((double)N * GetXLnY(x, y) - (GetOne(x, 1) * GetOneLog(y) )) / ((double)N * GetOne(x, 2) - pow(GetOne(x, 1), 2));

}
void GetA_Exp() {
    a = ((double)1 / (double)N) * GetOneLog(y) - (b / (double)N) * GetOne(x, 1);

}

void GetB_Log() {
    b = (N * GetXLnY(y, x) - (GetOne(y, 1) * GetOneLog(x))) / ((double)N * GetOne(y, 2) - pow(GetOne(y, 1), 2));

}
void GetA_Log() {
    a = ((float)1 / (float)N) * GetOne(y, 1) - ((float)b / (float)N) * GetOneLog(x);

}

/***/


int main()
{
    std::cout << GetOne(x, 1) << " " << log(23) << " " << sizeof(x) << " " << sizeof(x[0]) << " " << a << " " << b << "\n";
   
    GetB_Exp();
    GetA_Exp();
    std::cout << a << " " << b << "\n";

    GetB_Log();
    GetA_Log();
    std::cout << a << " " << b << "\n";


}
