#include "clalc.h"
#include "ui_clalc.h"
#include <QKeyEvent>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

clalc::clalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clalc)
{
    ui->setupUi(this);
}

clalc::~clalc()
{
    delete ui;
}

template<typename NUM>
bool numcheck(NUM num){
    return ((num >= 48 && num <= 57)||num == '.');
}

template<typename NUM>
bool sccheck(NUM num) {
    return (num!='(' && num!=')');
}

bool symcheck(char  a) {
    if ((a == '+' || a == '/' || a == '*' || a == '-' || a == '^') && ((a >= 33 && a <= 47)||a==94)) return true;
    return false;
}
static string strout;

bool sexyc(string strout) {
    int test = 0;
    for (int i = 0; i < strout.length(); i++) {
        if (strout[i] == '(') test++;
        else if (strout[i] == ')') test--;
    }
    if (test == 0) return true;
}

bool sexys(string strout) {
    for (int i = 0; i < strout.length(); i++) if((symcheck(strout[i]) && symcheck(strout[i + 1])) || sccheck(strout[i]) && sccheck(strout[i + 1])) return true;
}

void add_obj(char obj){
    strout += obj;
}

QString showstrout(){
    QString str = " ";
    for(int i=0; i<strout.length(); i++) str[i]=strout[i];
    //for(int i=0; i<strout.length(); i++){}
    return str;
}

int priority(char sym){
    switch(sym){
        //case '(': return 1;
        //case ')': return 1;
        case '+': case '-': return 2;
        case '/': case '%': case '*': return 3;
        case '^': case '#' : return 4;
    }
    return 0;
}

double math(double num1, double num2, char action) {
    switch (action) {
    case '^': return pow(num1, num2);
    case '#': return pow(num1, num2);
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num1 / num2;
    }
}

void del(){
    if(strout.length()!=0) strout.pop_back();
}

void go(){
    vector<char> temp; temp.push_back('~');
    vector<char> tur;
    vector<double> num;
    vector<double> num_stack;

    for (int i = 0; i < strout.length(); i++) {
            if (numcheck(strout[i])) {
                if (numcheck(strout[i]) && (i>=1 && numcheck(strout[i - 1]))) {
                    while (numcheck(i)) i++;
                } else {
                    tur.push_back(num.size() + 97);
                    num.push_back(atof(strout.data() + i));
                }
            }
            else if (!numcheck(strout[i]) || symcheck(strout[i])) {
                if (sccheck(strout[i])) {
                    if (priority(strout[i]) <= priority(temp.back())) {
                        tur.push_back(temp.back());
                        temp.pop_back();
                        temp.push_back(strout[i]);
                    }
                    else if (priority(strout[i]) >= priority(temp.back())) {
                        temp.push_back(strout[i]);
                    }
                }
                else if (strout[i] == '(') {
                    temp.push_back(strout[i]);
                }
                else if (strout[i] == ')') {
                    while (temp.back() != '(') {
                        tur.push_back(temp.back());
                        temp.pop_back();
                    }
                    temp.pop_back();
                }
            }
        }
        while (temp.back() != '~') {
            tur.push_back(temp.back());
            temp.pop_back();
        }
        double valuef, values;
        for (int i = 0; i < tur.size(); i++){
            if (!symcheck(tur[i])) {
                num_stack.push_back(num[tur[i]-97]);
            }
            else if (symcheck(tur[i])){
                values = num_stack.back();
                num_stack.pop_back();
                valuef = num_stack.back();
                num_stack.pop_back();
                num_stack.push_back(math(valuef, values, tur[i]));
            }
    }
    qDebug()<<num_stack.back();
    strout = to_string(num_stack.back());
    qDebug()<<strout.back();
    int istr = strout.length();
    while(strout[istr]!='.'){
        if(strout[istr]=='0') strout.pop_back();
        istr--;
    }
    if(strout.back() == '.') strout.pop_back();
    showstrout();
}


void clalc::on_numbutt_1_clicked(){
    add_obj('1');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_2_clicked(){
    add_obj('2');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_3_clicked(){
    add_obj('3');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_4_clicked(){
    add_obj('4');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_5_clicked(){
    add_obj('5');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_6_clicked(){
    add_obj('6');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_7_clicked(){
    add_obj('7');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_8_clicked(){
    add_obj('8');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_9_clicked(){
    add_obj('9');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_0_clicked(){
    add_obj('0');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_00_clicked(){
    add_obj('000');
    ui->Output->setText(showstrout());
}
void clalc::on_numbutt_000_clicked(){
    add_obj('.');
    ui->Output->setText(showstrout());
}
void clalc::on_butt_plus_clicked(){
    add_obj('+');
    ui->Output->setText(showstrout());
}
void clalc::on_butt_minus_clicked(){
    add_obj('-');
    ui->Output->setText(showstrout());
}
void clalc::on_butt_multiplication_clicked(){
    add_obj('*');
    ui->Output->setText(showstrout());
}
void clalc::on_butt_division_clicked(){
    add_obj('/');
    ui->Output->setText(showstrout());
}
void clalc::on_step_clicked(){
    add_obj('^');
    ui->Output->setText(showstrout());
}
void clalc::on_butt_Go_clicked(){
    if(strout.length()!=0)go();
    ui->Output->setText(showstrout());
}
void clalc::on_CEL_clicked(){
    del();
    ui->Output->setText(showstrout());
}
void clalc::on_OpenSk_clicked(){
    add_obj('(');
    ui->Output->setText(showstrout());
}
void clalc::on_CloseSk_clicked(){
    add_obj(')');
    ui->Output->setText(showstrout());
}

void clalc::keyPressEvent(QKeyEvent * press){
    switch(press->key()){
    case Qt::Key_0: on_numbutt_0_clicked(); break;
    case Qt::Key_1: on_numbutt_1_clicked(); break;
    case Qt::Key_2: on_numbutt_2_clicked(); break;
    case Qt::Key_3: on_numbutt_3_clicked(); break;
    case Qt::Key_4: on_numbutt_4_clicked(); break;
    case Qt::Key_5: on_numbutt_5_clicked(); break;
    case Qt::Key_6: on_numbutt_6_clicked(); break;
    case Qt::Key_7: on_numbutt_7_clicked(); break;
    case Qt::Key_8: on_numbutt_8_clicked(); break;
    case Qt::Key_9: on_numbutt_9_clicked(); break;
    }
}




