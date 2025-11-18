#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;


string companyName = "C++ Motors Ltd";

class Vehicle{
public:
    string brand;
    string model;
    static int count;

    Vehicle(string b, string m){
    brand = b;
    model = m;
    count++;
    }
    virtual void displayInfo(){
        cout<< "Brand: "<< brand<<", Model "<< model<< endl;
    }

    virtual updateModel(string Newer){
         string temp = Newer;
         model = temp;
    }
    virtual string getFileData(){
    return "Brand: " + brand +", Model: "+ model;
    }

};

int Vehicle::count =0;

class Car: public Vehicle{
public:
    int seats;

    Car(string b, string m, int s): Vehicle(b, m){
    if (s<0)  throw invalid_argument("Seats can't be negative.");
    seats= s;
    }

    void displayInfo() override{
    cout<< "Brand: "<< brand
    <<", Model: "<< model
    <<", Seats: "<< seats<< endl;

    }
    string getFileData() override{
    return  "Brand: "+ brand+
    ", Model: "+model+
    ", Seats: "+ to_string(seats);

    }

};

class Motorbike: public Vehicle{
public:
    int enginecapacity;

    Motorbike(string b, string m, int ec): Vehicle(b, m){
    if (ec<0) throw invalid_argument("Engine capacity cannot be zero.");
    enginecapacity= ec;
    }

    void displayInfo() override{
    cout<< "[Motorbike] brand: "<< brand
    << ", Model: "<< model
    << ", Engine Capacity: "<< enginecapacity<< endl;
    }

    string getFileData() override {
        return "[Motorbike] Brand: " + brand +
               ", Model: " + model +
               ", Engine: " + to_string(enginecapacity) + "cc";
    }
};

int main(){
    try{
          cout << "=== " << companyName << " ====\n\n";


        Car c1("Toyota", "Corolla", 5);
        Car c2("Honda", "Civic", 4);
        Motorbike m1("Yamaha", "R1", 1000);
        Motorbike m2("Kawasaki", "Ninja", 650);

        Vehicle* vehicles[4] = { &c1, &c2, &m1, &m2 };

        cout << " Vehicle Info ";
        for (int i = 0; i < 4; i++) {
            vehicles[i]->displayInfo();
        }

        cout << "\nTotal Vehicles Created: " << Vehicle::count << endl;


        c1.updateModel("Corolla X");
        m1.updateModel("R1 Elite");

        ofstream outFile("vehicles.txt");
        if (!outFile) throw runtime_error("Error opening file for writing.");

        for (int i = 0; i < 4; i++) {
            outFile << vehicles[i]->getFileData() << endl;
        }
        outFile.close();


        cout << " Reading from File ";
        ifstream inFile("vehicles.txt");
        if (!inFile) throw runtime_error("Error opening file for reading.");

        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();

    }
    catch(exception& e){
        cout<< "Exception caught: "<< e.what() << endl;
    }
return 0;
};
