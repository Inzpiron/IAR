#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int l = 10;
    while(cin >> l) { 
        int size = l*2 + 1;
        short int mapa[size][size];
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                if(!(i == j && i == l)) {
                    if(i == j) {
                        if(i < l)
                            mapa[i][j]= 2<<7;
                        else 
                            mapa[i][j]= 2<<3;
                    } else if(i+j == size-1) {
                        if(i < l)
                            mapa[i][j]= 2<<1;
                        else 
                            mapa[i][j]= 2<<5;
                    }else if(i < j) {
                        if(i+j < size - 1)
                            mapa[i][j] = 2<<0;
                        else 
                            mapa[i][j] = 2<<2;
                    }else{
                        if(i+j > size -1)
                            mapa[i][j] =  2<<4;
                        else
                            mapa[i][j] = 2<<6;
                    }
                }
            }
        }

        mapa[l][l] = 0;

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                cout << setw(4) << mapa[i][j];
            }
            cout << endl;
        }

    }
    return 0;
}