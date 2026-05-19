#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "vehicle_rental1.cpp"
using namespace std::chrono;
using namespace std;
vehicle v;


class account
{
public:
    string name;
    int age;
    string gender;
    string aadhar;
    string license;
    vector<vehicle *> vehicle_rented; // made of type vehicle* which is a pointer to objects so that objects of different classes can be stored.
    string reg_num;

    void set()
    {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        if(age<18){
            cout<<"Age must be at least 18 to rent a vehicle."<<endl;
            cout<<"Enter valid age: ";
            cin>>age;
        }
        cout << "Enter gender: ";
        cin >> gender;
        if(gender!="M"||gender!="F"||gender!="O"){
            cout<<"Invalid gender input."<<endl;
            cout<<"Enter gender (M/F/O): ";
            cin >> gender;
        }
        cout << "Enter aadhar: ";
        cin >> aadhar;
        if (aadhar.length() != 12)
        {
            cout << "Invalid aadhar number." << endl;
            cout << "Enter aadhar no. of 12 digits: ";
            cin >> aadhar;
        }
        cout << "License num: ";
        cin >> license;
        if (license.length() != 10)
        {
            cout << "Invalid license number." << endl;
            cout << "Enter license no. of 10 digits: ";
            cin >> license;
        }
    }
    friend void select_veh(account &ob);
    static account readAccountFromFile();
    void bill(string user)
    {
         long long billamt;
         billamt = 0;
         for (auto v : vehicle_rented) {
    
    v->returnvehicle(); // ✅ now billing uses correct time
    billamt += v->getTotalCost();
}
         ifstream fin("rented.txt",ios::in);

        if(!fin){
            cout<<"Bill not found";
            return ;
        }
         

       

        account acc = account::readAccountFromFile();
    
        ofstream fout("returned.txt",ios::app);
        fout<<"------Billing Details------"<<endl;
        fout<<"Name: "<<acc.name<<"\nAge: "<<acc.age<<"\nGender: "<<acc.gender
            <<"\nAadhar: "<<acc.aadhar<<"\nLicense: "<<acc.license<<"\nBill: "<<billamt<<endl;
        fout.close();
        ofstream file("rented.txt",ios::trunc);
        file.close();
        fin.close();
        cout << "\n----- Billing Details -----\n";
        cout << "Name: " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Gender : " << gender << endl;
        cout << "Aadhar : " << aadhar << endl;
        cout << "License : " << license << endl;

      time_t t;
    fin >> t;
    v.setRentStart(std::chrono::system_clock::from_time_t(t));

    cout << "\nReturned Vehicle:\n";
    for (auto v : vehicle_rented) {
        cout << "Model: " << v->getDate() << "\n";
        cout << "Total Bill: ₹" << v->getTotalCost() << "\n";
       time_t start = system_clock::to_time_t(v->getRentStart());
        cout << "Rent start: " << ctime(&start);
        time_t end = system_clock::to_time_t(system_clock::now());
          cout << "Return time: " << ctime(&end);
    }



        if (vehicle_rented.empty())
        {
            cout << "No vehicle rented. Nothing to return.\n";
            return;
        }
      for (auto v : vehicle_rented) {
    delete v;
      }
       vehicle_rented.clear();

        
       
    
    }
};
account account::readAccountFromFile()
{
    account acc;
    ifstream fin("rented.txt", ios::in);
    if (!fin)
    {
        cout << "No saved data found. Starting fresh.\n";
        return acc;
    }

    string line;
    while (getline(fin, line))
    {
        if (line.find("Name:") != string::npos)
            acc.name = line.substr(6);
        else if (line.find("Age:") != string::npos)
            acc.age = stoi(line.substr(5));
        else if (line.find("Gender:") != string::npos)
            acc.gender = line.substr(8);
        else if (line.find("Aadhar:") != string::npos)
            acc.aadhar = line.substr(8);
        else if (line.find("License:") != string::npos)
            acc.license = line.substr(9);
        else if (line.find("Car") != string::npos || line.find("Scooter") != string::npos)
        {
            string type = line;
            string model;
            int speed;
            double mileage;
            int price;

            getline(fin, line);
            model = line.substr(7); // Model: YYYY-MM-DD
            getline(fin, line);
            speed = stoi(line.substr(7)); // Speed:
            getline(fin, line);
            mileage = stod(line.substr(9)); // Mileage:
            getline(fin, line);
            price = stoi(line.substr(7)); // Price:

            vehicle *v = nullptr;
            if (type == "Car")
                v = new car(model, speed, mileage, price);
            else if (type == "Scooter")
                v = new scooter(model, speed, mileage, price);

            if (v)
                acc.vehicle_rented.push_back(v);
        }
    }

    fin.close();
    return acc;
}



void writeFile(account &acc)
{ 
    ofstream fout("rented.txt", ios::app);
    if (!fout)
    {
        cerr << "Error opening file for writing.\n";
        return;
    }
    fout << "Account details\n";
    fout << "Name: " << acc.name << "\n";
    fout << "Age: " << acc.age << "\n";
    fout << "Gender: " << acc.gender << "\n";
    fout << "Aadhar: " << acc.aadhar << "\n";
    fout << "License: " << acc.license << "\n";
    for (auto v : acc.vehicle_rented)
    {
        if (car *c = dynamic_cast<car *>(v))
        {
            fout << "Car\n";
            fout << "Model: " << c->getDate() << "\n";
            fout << "Speed: " << c->getSpeed() << "\n";
            fout << "Mileage: " << c->getMileage() << "\n";
            fout << "Price: " << c->getVehCost() << "\n";
        }
        else if (scooter *s = dynamic_cast<scooter *>(v))
        {
            fout << "Scooter\n";
            fout << "Model: " << s->getDate() << "\n";
            fout << "Speed: " << s->getSpeed() << "\n";
            fout << "Mileage: " << s->getMileage() << "\n";
            fout << "Price: " << s->getVehCost() << "\n";

        }
        auto tp = v->getRentStart(); // get the time_point
        time_t time =system_clock::to_time_t(tp);

        fout<<"Rent Days: "<<v->getRentDays()<<endl;
        fout<<"Rent Start: "<<ctime(&time);


    }
    fout.close();
}
void select_veh(account &ob)
{
    vector<vehicle *> &vehicle_rented = ob.vehicle_rented;
    int numVehicles;
    cout << "How many vehicles do you want to rent? ";
    cin >> numVehicles;

    for (int i = 0; i < numVehicles; ++i)
    {
        int choice, days;
        string model;
        int speed;
        double mileage;
        int price;

        cout << "\nVehicle " << (i + 1) << ":\n";
        cout << "1. Car\n2. Scooter\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;
        if(choice!=1 && choice!=2){
            cout<<"Invalid choice. Please select 1 or 2.\n";
            --i; // decrement i to repeat this iteration
            continue;
        }

        cout << "Enter model year (e.g., 2025-10-01): ";
        cin >> model;
        if(model.length()!=10){
            cout<<"Invalid model year format."<<endl;
            cout<<"Enter model year (e.g., 2025-10-01): ";
            cin>>model;
        }
        cout << "Enter speed: ";
        cin >> speed;
        cout << "Enter mileage: ";
        cin >> mileage;
        cout << "Enter price: ";
        cin >> price;
        cout << "For how many days? ";
        cin >> days;

        vehicle *v = nullptr;

        if (choice == 1)
        {
            v = new car(model, speed, mileage, price);
        }
        else if (choice == 2)
        {
            v = new scooter(model, speed, mileage, price);
        }
        else
        {
            cout << "Invalid choice. Skipping this vehicle.\n";
            continue;
        }

        if (v)
        {
            v->rent(days);
            cout << "Vehicle rented successfully.\n";
            vehicle_rented.push_back(v);
        }
    }
}

int main()
{
    int choice;
    string ch;
    int days;
    ifstream fin("rented.txt", ios::in);

    account acc = account::readAccountFromFile(); // ✅ Load saved account and rented vehicles

    acc.set();

    fin.close();
    while(true){
    cout << "\nHow can I help you?\n";
    cout << "1. Rent a vehicle\n2. Return a vehicle\n3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    switch(choice){
    
    case 1:
    
        select_veh(acc);
        writeFile(acc);
        cout << "\nThank you for using our service.\n";
        break;
    
    case 2:

        cout << "Which vehicle do you want to return? (Car or Scooter): ";
        cin >> ch;

        acc.bill(ch); // returnvehicle() is called here
        
        cout << "\nThank you for using our service.\n";
        break;
    case 3:
        cout << "Exiting. Goodbye!\n";
        return 0;

    default:
        cout << "Invalid choice.\n";
    }
}

    return 0;

}

