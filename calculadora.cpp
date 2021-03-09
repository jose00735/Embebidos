#include <iostream>

using namespace std;

int main(){
	int r = 0,n1 = 0, n2 = 0;
	int op = 0;
	cout << "Ingrese a operacion deseada:" << endl << "1) suma" << endl << "2) Resta" << endl << ": ";
	cin >> op;
 	cout << "Ingrese n1: ";
	cin >> n1;
       	cout << "Ingrese n2: ";
	cin >> n2;	
	if (op == 1){
		r = n2 + n1;		
	}
	else
	{
		r = n2 - n1;
	}
	cout << "El resultado: " << r << endl;
	return 0;
}
