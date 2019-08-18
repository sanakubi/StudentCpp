#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename NUM>
bool numcheck(NUM num) {
	return ((num >= 48 && num <= 57) || num == '.');
}
template<typename NUM>
bool sccheck(NUM num) {
	return (num!='(' && num!=')');
}

bool symcheck(char  a) {
	if ((a == '+' || a == '/' || a == '*' || a == '-' || a == '%') && (a >= 33 && a <= 47)) return true;
	return false;
}

int priority(char sym) {
	switch (sym) {
	//case '(': return 1;
	case '+': case '-': return 2;
	case '/': case '%': case '*': return 3;
	case '^': case '#': return 4;
	}
	return 0;
}

int math(int num1, int num2, char action) {
	switch (action) {
	//case '^': return pow(num1, num2);
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	}
}

int main() {
	string strout = "512+6321";
	string numz;
	vector<char> temp; temp.push_back('~');
	vector<char> tur;
	vector<int> num;
	vector<int> num_stack;

	//cout <<"atoi- "<<atoi(strout.data()+1)<<endl;

	for (int i = 0; i < strout.length(); i++) {
		if (numcheck(strout[i])) {
			if (numcheck(strout[i]) && (i>=1 && numcheck(strout[i - 1]))) {
				while (numcheck(i)) i++;
			} else tur.push_back(num.size() + 97);
			num.push_back(atoi(strout.data() + i));
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
	cout << num[tur[0]- 97]<<" "<< tur[0]<< endl;
	
	int valuef, values;
	for (int i = 0; i < tur.size(); i++){
		if (!symcheck(tur[i])) {
			num_stack.push_back(num[tur[i]-97]);
			cout << "GOT NUM - " << num_stack.back() << endl;
		}
		else if (symcheck(tur[i])){
			cout << "MATH - " << num_stack.back() << endl;
			values = num_stack.back();
			num_stack.pop_back();
			valuef = num_stack.back();
			num_stack.pop_back();
			num_stack.push_back(math(valuef, values, tur[i]));
		}
	}
	cout<< num_stack.back()<<endl;
	return 0;
}
