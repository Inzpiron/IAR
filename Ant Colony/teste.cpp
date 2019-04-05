#include <bits/stdc++.h>
using namespace std;


std::random_device rd;
std::mt19937 gen;
std::uniform_real_distribution<> r_dist;
std::uniform_int_distribution<> i_dist;


int integer(int i, int j){
            i_dist = std::uniform_int_distribution<>(i, j);
            return i_dist(gen);
        }


void reset() {
            gen = std::mt19937(rd());
        }

double real(double i, double j){
    r_dist = std::uniform_real_distribution<>(i, j);
    return r_dist(gen);
}

int roulette(std::vector<double> row){
    double choosen_by_god = real(0, 1);
    double sum = 0;
    cout << "choosen " << choosen_by_god << endl; 
    int cont = 0;
    int i;
    for(i = 0; i < row.size(); i++) {
        cont++;
        cout << row[i] << endl;
        if(choosen_by_god >= sum && choosen_by_god < row[i]){
            break;
        }
        sum += row[i];
    }

    return i;

    reset();
}


int main() {
    reset();
    cout << integer(0, 1) << endl;
    //reset();
    //cout << roulette({0.25, 1-0.75}) << endl;;
    return 0;
}