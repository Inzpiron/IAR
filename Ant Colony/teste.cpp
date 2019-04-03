#include <iostream>
#include <iomanip>
#include <thread>
using namespace std;

int main() {
    int * a = NULL;
    int b = 10;
    a = &b;
    cout << *a << endl;
    std::srand(std::time(nullptr));
    cout << (std::rand()%1000000)/1000000.0<< endl;
    int l =5;
    int size = l*2 + 1;
        int ** mapa = new int*[size]();
        for(int i = 0; i < size; i++) {
            mapa[i] = new int[size];
            for(int j = 0; j < size; j++) {
                if(!(i == j && i == l)) {
                    if(i == j) {
                        if(i < l)
                            mapa[i][j]= (2<<0)|(2<<3);
                        else 
                            mapa[i][j]= (2<<1)|(2<<2);
                    } else if(i+j == size-1) {
                        if(i < l)
                            mapa[i][j]= (2<<0)|(2<<1);
                        else 
                            mapa[i][j]= (2<<2)|(2<<3);
                    }else if(i < j) {
                        if(i+j < size - 1)
                            mapa[i][j] = 2<<0;
                        else 
                            mapa[i][j] = 2<<1;
                    }else{
                        if(i+j > size -1)
                            mapa[i][j] =  2<<2;
                        else
                            mapa[i][j] = 2<<3;
                    }
                }

                cout << setw(4) << mapa[i][j];
            }
            cout << endl;
        }
        mapa[l][l] = 0;
    return 0;
}