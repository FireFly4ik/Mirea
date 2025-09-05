//Галанов Андрей Вадимович ЭФБО-03-24

#include <iostream>
#include <cmath>
using namespace std;

class Triangle{
public:
    Triangle(){}
    Triangle(double a, double b, double c): a(a), b(b), c(c) {}

    double perimetr(){
        return a + b + c;
    }

    double square(){
        double polu = perimetr() / 2;
        return sqrt(polu * (polu - a) * (polu - b) * (polu -c));
    }

    void setSides(double newA, double newB, double newC){
        a = newA;
        b = newB;
        c = newC;
    }

private:
    double a, b, c;
};

int main(){
    Triangle* triangle1 = new Triangle;
    triangle1->setSides(2, 2, 2);
    cout << triangle1->perimetr() << " " << triangle1->square() << endl;
    Triangle* triangle2 = new Triangle(3, 3, 3);
    cout << triangle2->perimetr() << " " << triangle2->square() << endl;
    return 0;
}