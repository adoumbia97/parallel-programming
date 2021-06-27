#include <stdlib.h>

double generate_random_double() {
    double rn = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    return rn;
}

bool in_circle(double x, double y) {
    double d = x * x + y * y;
    if (d <= 1.0) {
        return true;
    }
    return false;
    // return d <= 1.0
}


#include<iostream>
using namespace std;
#include <cstring>

void writeTitle(string title, string infos="")
{
  cout<<"\n\t\t\t\t\t---------------------------------------- ";
  cout<<"\n\t\t\t\t\t---------------------------------------- ";
  cout<<"\n";
  cout <<"\n\t\t\t\t\t|  "<<  title<< "    |";
  cout <<"\n";
  cout <<"\n\t\t\t\t\t\t  "<<  infos<< "    ";
  cout<<"\n\t\t\t\t\t---------------------------------------- ";
  cout<<"\n\t\t\t\t\t---------------------------------------- ";
  cout<<"\n ";
}
