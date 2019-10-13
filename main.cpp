#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include "Polynomial.h"
#include "Vector.h"

using namespace std;

int main(){
    cout << "Polynomial and Vector List program!"<<endl<<"Polynomials and Vectors are read from text files!"<<endl<<endl;
    ifstream poly_file;
    poly_file.open("Polynomial.txt");
    
    int polamount = -1, vecamount=-1;
    //Creating polynomials
    poly_file >> polamount;
    Polynomial *polyarr = new Polynomial[polamount];
    int *emptyarray = new int[polamount];
    for(int i = 0; i < polamount;i++){
        emptyarray[i] = 0;
    }
    for(int i = 0; i < polamount;i++){ //initializer
        polyarr[i] = Polynomial(0, emptyarray);
    }
    
    for(int i = 0; i < polamount;i++){
        int degree = -1;
        poly_file >> degree;
        int valsize = degree+1;
        int* polyvals = new int[valsize];
        for (int j = 0; j < valsize; j++){
           polyvals[j] = 0;
        }
        for (int j = 0; j < valsize; j++){
            poly_file >> polyvals[j];
        }
        polyarr[i] = Polynomial(valsize, polyvals);
        //delete[] polyvals;
    }
    poly_file.close();
    delete[] emptyarray;

    //Creating vectors
    ifstream vect_file;
    vect_file.open("Vector.txt");
    vect_file >> vecamount;
    Vector *vecarr = new Vector[vecamount];

    int size = -1;
    for (int i = 0; i < vecamount; i++){
        vect_file >> size;
        int* vecvals = new int[size];
        for(int j = 0; j<size;j++){
            vecvals[j] = 0;
        }
        for(int j = 0; j<size;j++){
            vect_file >> vecvals[j];
        }
        vecarr[i] = Vector(size, vecvals);
    }
    vect_file.close();
    
   

    ////////////
    cout<<"Possible Actions:"<<endl<<"1. Print Polynomial and Vector Lists"<<endl<<"2. Do a polynomial operation"<<endl<<"3. Do a vector operation"<<endl<<"4. Help: Print possible actions"<<endl<<"0. Exit the program"<<endl<<endl;
    int input = 1;
    char op;
    while(input != 0){
        cout<<"Enter an option: ";
        cin >> input;
        switch (input)
        {
            case 1:
                cout<<"Vectors:"<<endl;
                for(int i = 0; i < vecamount;i++){
                    cout<<i+1<<". ";
                    cout<<vecarr[i];
                    cout<<endl;
                }
                cout<<endl<<"Polynomials:"<<endl;
                for(int i = 0; i <polamount;i++){
                    cout<<i+1<<". ";
                    cout<<polyarr[i];
                    cout<<endl;
                }
                break;
            
            case 2:
                cout<<"Which polynomial operation would you like to do? (+: addition, *:multiplication)"<<endl;
                int pol1, pol2;
                cin>> pol1 >> op >> pol2;
                pol1-=1;
                pol2-=1;
                if(polamount < pol1 || polamount < pol2) cout<<"You entered invalid polynomial number(s)."<<endl;
                else if(op == '+') {
                    Polynomial res = polyarr[pol1] + polyarr[pol2];
                    cout<<"(";
                    cout<<polyarr[pol1];
                    cout<<") + (";
                    cout<<polyarr[pol2];
                    cout<<") = ";
                    cout<<res;
                    cout<<endl<<endl;
                    }
                else if(op=='*'){
                    Polynomial res = polyarr[pol1]*polyarr[pol2];
                    cout<<"(";
                    cout<<polyarr[pol1];
                    cout<<") * (";
                    cout<<polyarr[pol2];
                    cout<<") = ";
                    cout<<res;
                    cout<<endl<<endl;
                    }
                else cout<<"You entered invalid polynomial operation."<<endl;
                break;

            case 3:
                cout<<"Which vector operation would you like to do? (+: addition, *:scalar multiplication, .:dot product)"<<endl;
                int vec1, vec2;
                cin>> vec1 >> op >> vec2;
                vec1-=1;
                vec2-=1;
            
                if(op == '+'){
                    if(vecamount < vec1 || vec1<0 || 0 > vec2 || vecamount < vec2) cout<<"You entered invalid vector number(s)."<<endl;
                    else if(vecarr[vec1].get_size() != vecarr[vec2].get_size()) cout<<"Please enter 2 equivalent sized vectors. "<<endl;
                    else{
                        Vector res = vecarr[vec1] + vecarr[vec2];
                        cout<<vecarr[vec1];
                        cout<<" + ";
                        cout<<vecarr[vec2];
                        cout<<" = ";
                        cout<<res;
                        cout<<endl<<endl;
                    }
                } 
                else if(op=='*') {
                    if(vecamount < vec1) cout<<"You entered invalid vector number(s)."<<endl;
                    Vector res = vecarr[vec1]*(vec2+1);
                    cout<<vecarr[vec1];
                    cout<<" * ";
                    cout<<vec2+1;
                    cout<<" = ";
                    cout<<res;
                    cout<<endl<<endl;
                }
                else if(op=='.'){
                    if(vecamount < vec1 || 0>vec1 || 0 > vec2 || vecamount < vec2) cout<<"You entered invalid vector number(s)."<<endl;
                    else if(vecarr[vec1].get_size() != vecarr[vec2].get_size()) cout<<"Please enter 2 equivalent sized vectors. "<<endl;
                    else{
                        int res = vecarr[vec1]*vecarr[vec2];
                        cout<<vecarr[vec1];
                        cout<<" . ";
                        cout<<vecarr[vec2];
                        cout<<" = ";
                        cout<<res;
                        cout<<endl<<endl;
                    }
                } 
                else{
                     cout<<"You entered invalid vector operation."<<endl;
                }
                break;

            case 4:
                cout<<"Possible Actions:"<<endl<<"1. Print Polynomial and Vector Lists"<<endl<<"2. Do a polynomial operation"<<endl<<"3. Do a vector operation"<<endl<<"4. Help: Print possible actions"<<endl<<"0. Exit the program"<<endl<<endl;
                break;

            case 0:
                break;

            default:
                cout << "Please enter a valid operation number. ";
                break;
        }
    }

    for(int i = 0; i<polamount;i++){
        polyarr[i].deletefunc();
    }
    delete[] polyarr;
    for(int i = 0; i<vecamount;i++){
        vecarr[i].deletefunc();
    }
    delete[] vecarr;

    return 0;
}
