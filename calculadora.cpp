#include <iostream>

using namespace std;

int main(){
	int r = 0,n1 = 0, n2 = 0;
	int op = 0;
	printf("Prueba x");
	cout << "Ingrese a operacion deseada:" << endl << "1) suma" << endl << "2) Resta" << endl << "3) multiplicacion "<< endl << "4) division" <<": ";
	cin >> op;
 	cout << "Ingrese n1: ";
	cin >> n1;
       	cout << "Ingrese n2: ";
	cin >> n2;	
	if (op == 1){
		r = n2 + n1;		
	}
	else if(op == 2)
	{
		r = n2 - n1;
	}
	else if(op == 3){
		r = n2*n1;
	}
	else 
	{
		r = n2/n1;
	}
	cout << "El resultado: " << r << endl;
	printf("\n\rChao");
	return 0;
}
