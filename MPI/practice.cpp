#include <iostream>
using namespace std;

int main(){
    int x=0, num_steps=99999;
    float sum = 0.0, pi;
    float step = 1.0/(double) num_steps;
    //cout <<step<<endl;
    for (int i=0; i < num_steps; ++i) {
        //cout<<i<<endl;
        x = ((i+0.5)*step);
        sum = sum + (4.0/(1.0+x*x));
        //cout <<sum<<endl;
    }
    pi = step * sum;
    cout << pi ;
}
