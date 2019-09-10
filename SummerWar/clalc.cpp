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

static string strout = "";
static vector<string> backstr = {string()};
void getstrback() {
    backstr.push_back(strout);
}
void back() {
    if(backstr.size()>0){
        strout=backstr.back();
        backstr.pop_back();
        qDebug()<<backstr.size();
    }
    else return;
}

bool dev = 0;

bool numcheck(char num){
    return ((num >= 48 && num <= 57)||num == '.');
}
bool sccheck(char num) {
    return (num!='(' && num!=')');
}
bool symcheck(char  a) {
    if ((a == '+' || a == '/' || a == '*' || a == '-' || a == '^' || a == '#') ) return true;
    return false;
}
bool minuscheck(int i) {
    if( (i == 0 || strout[i - 1] == '+' || strout[i - 1] == '/' || strout[i - 1] == '*' || strout[i - 1] == '^'|| strout[i - 1] == '#' || strout[i - 1] == '(') && strout[i]=='-' )return true;
}

bool sexyc(string strout) {
    int tmp = 0;
    for (int i = 0; i < strout.length(); i++) {
        if (strout[i] == '(') tmp++;
        else if (strout[i] == ')') tmp--;
    }
    if (tmp == 0) return true;
}

bool sexysystem(string strout) {
    for (int i = 0; i < strout.length(); i++)
        if((symcheck(strout[i]) && (symcheck(strout[i + 1]) && !minuscheck(strout[i + 1])) )
                || (sccheck(strout[i]) && sccheck(strout[i + 1]))
                || symcheck(strout.back())
                || (numcheck(strout[i]) && sccheck(strout[i++]))
                || (sccheck(strout[i]) && numcheck(strout[i++])) ) return false;
}
/////
void add_obj(char obj) {
    if( (symcheck(obj) && obj!='-') && (strout.back()=='(' || symcheck(strout.back()) /* && strout.back()!='-' && strout.back()!='+'*/ ) ) return;
    else if( (obj=='+'||obj=='-') && (strout.back()=='+' || strout.back()=='-') ) {
        strout.pop_back();{getstrback(); strout+=obj;}
    }else if(obj=='.'){
        if( strout.length()==0 || symcheck(strout.back()) || strout.back()=='(' ){strout+='0'; strout+=obj;}
        else if(strout.back() == '.') return;
        else{ getstrback();strout += obj;}
    }else if(symcheck(obj) && obj!='-' && strout.length()==0) return;
    else { getstrback(); strout += obj;}
}

QString showstrout() {
    QString str = " ";
    if(dev)for(int i=0; i<strout.length(); i++) str+=strout[i];
    else
    for(int i=0; i<strout.length(); i++) {
         if(strout[i]=='^'){
            if(i+1 < strout.length()){str+="<sup>";}
            else{str+="^";break;}
            i++;
            if(numcheck(strout[i])){
                while(numcheck(strout[i])){ str+=strout[i];i++;}
                str+="</sup>";
                i--;
            } else if(strout[i]=='('){
                i++;
                while(numcheck(strout[i]) || symcheck(strout[i])){ str+=strout[i];i++;}

                str+="</sup>";
            }
        }else if(strout[i]=='#'){
            int tmp=i;
            while(str[tmp] >= '0' && str[tmp] <= '9'){
                tmp--;
            }
            tmp++;
            str.insert(tmp, "<sup>");
            str+="</sup>";
            if(i+1 < strout.length()){str+="√<span style=\"text-decoration: overline\">";}
            else{str+="√";break;}
            i++;
            if(numcheck(strout[i])){
                while(numcheck(strout[i])){ str+=strout[i];i++;}
                str+="</span>";
                i--;
            }else if(strout[i]=='('){
                i++;
                while(numcheck(strout[i]) || symcheck(strout[i])){ str+=strout[i];i++;}
                str+="</span>";
            }
        }else str+=strout[i];
    }
    return str;
}

int priority(char sym) {
    switch(sym){
        case '+': case '-': return 2;
        case '/': case '%': case '*': return 3;
        case '^': case '#' : return 4;
    }
    return 0;
}

double math(double num1, double num2, char action) {
    switch (action) {
    case '^': return pow(num1, num2);
    case '#': return pow(num2, 1/num1);
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num1 / num2;
    }
}


void del() {
    if(strout.length()!=0){ getstrback(); strout.pop_back();}
}

void go() {
    vector<char> temp;
    temp.push_back('~');
    vector<char> tur;
    vector<double> num;
    vector<double> num_stack;
    if (!sexysystem(strout) && sexyc(strout)&&!symcheck(strout.back())){
    getstrback();
    for (int i = 0; i < strout.length(); i++) {
            if (numcheck(strout[i]) || minuscheck(i)) {
                if (numcheck(strout[i]) && ((i>0 && (numcheck(strout[i - 1])) || minuscheck(i-1) ))){
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
    }
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
    add_obj('0');add_obj('0');add_obj('0'); //да тупо да я
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
void clalc::on_Clear_clicked(){
    getstrback();
    strout = "";
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
void clalc::on_kor_clicked(){
    add_obj('#');
    ui->Output->setText(showstrout());
}
void clalc::on_back_clicked(){
    back();
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
    case Qt::Key_Plus: on_butt_plus_clicked(); break;
    case Qt::Key_Minus: on_butt_minus_clicked(); break;
    case Qt::Key_Slash: on_butt_division_clicked(); break;
    case Qt::Key_ParenLeft: on_OpenSk_clicked(); break;
    case Qt::Key_ParenRight: on_CloseSk_clicked(); break;
    case Qt::Key_Delete: on_Clear_clicked(); break;
    case Qt::Key_Backspace: on_CEL_clicked(); break;
    case Qt::Key_Z: if( press->modifiers() == Qt::ControlModifier) on_back_clicked(); break;
    case Qt::Key_Return:on_butt_Go_clicked(); break;
    }
}
bool owo_uwu = 0;
void clalc::on_UWU_clicked()
{   if(owo_uwu == 0){
        ui->UWU->setText("OWO");owo_uwu = 1;
        ui->Output->setText("Поставьте 4 пожалуйста!!! ");
    }else if(owo_uwu ==1){
        ui->UWU->setText("UWU");owo_uwu = 0;
        ui->Output->setText(showstrout());
    }
}

void clalc::on_devmode_button_clicked(){
    if(dev == 0){
        ui->devmode_button->setText("dev on");dev = 1;
        ui->Output->setText(showstrout());
    }else if(dev == 1){
        ui->devmode_button->setText("dev of");dev = 0;
        ui->Output->setText(showstrout());
    }
}
