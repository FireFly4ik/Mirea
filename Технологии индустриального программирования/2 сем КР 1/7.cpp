//Галанов Андрей Вадимович ЭФБО-03-24

#include <iostream>
using namespace std;

class Car{
public:
    Car(){}
    Car(string brand, string model, uint year): brand(brand), model(model), year(year) {}

    int getYear(){
        return year;
    }

    string getModel(){
        return model;
    }

    string getBrand(){
        return brand;
    }

    void setYear(uint newYear){
        year = newYear;
    }

    void setModel(string newModel){
        model = newModel;
    }

    void setBrand(string newBrand){
        brand = newBrand;
    }

private:
    string brand, model;
    uint year;
};

int main(){
    Car* car1 = new Car;
    car1->setBrand("Skoda");
    car1->setModel("Kodiaq");
    car1->setYear(2015);
    cout << car1->getBrand() << " " << car1->getModel() << " " << car1->getYear() << endl;
    Car* car2 = new Car("Porshe", "Taycan", 2018);
    cout << car2->getBrand() << " " << car2->getModel() << " " << car2->getYear() << endl;
    return 0;
}