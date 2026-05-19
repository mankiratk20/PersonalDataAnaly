#include <iostream>
#include <string>
#include <ctime>
#include<chrono>
#include <fstream>
using namespace std;
class vehicle
{
protected:
    string date;
    float speed;
    double mileage;
    int veh_cost;
    chrono::system_clock::time_point rentstart;
    int rentdays;
    long long totalcost;
    bool returned;

public:
    vehicle() {}
    vehicle(string d, int s, double m, int c, chrono::system_clock::time_point rentstart, bool isReturned) : date(d), speed(s), mileage(m), veh_cost(c), rentdays(0), totalcost(0), returned(isReturned), rentstart(chrono::system_clock::now()) {}
    void rent(int days)
    {
        rentdays = days;

    rentstart = chrono::system_clock::now();
   
        returned = false;
        cout << "Vehicle rented for " << rentdays << " days" << endl;
    }
    virtual long long returnvehicle()
    {
        if (returned)
        {
            cout << "Already returned.\n";
            return 0;
        }

         using namespace std::chrono;

        auto now = system_clock::now();
        auto duration = duration_cast<hours>(now - rentstart);
        long long actual_days = (duration.count()) / 24;
        if (actual_days == 0) actual_days = 1;

       if(duration.count()<0){
           duration =chrono::hours(0);
       }
        long long overdue = 0;

        if (actual_days > rentdays)
        {
            overdue = (actual_days - rentdays) * veh_cost;
        }

        totalcost = (rentdays * veh_cost) + overdue;

        cout << "Returned after " << actual_days << " simulated day(s)\n";
        cout << "Overdue cost: " << overdue << endl;
        cout << "Total cost: " << totalcost << endl;

        returned = true;
        return totalcost;
    }

   
    virtual string getDate() const { return date; } //virtual getters .the derived classes automatically inherit them.
    virtual float getSpeed() const { return speed; }
    virtual double getMileage() const { return mileage; }
    virtual int getVehCost() const { return veh_cost; }

    // getters for rent info
    int getRentDays() const { return rentdays; }
    chrono::system_clock::time_point getRentStart() const { return rentstart; }
    bool isReturned() const { return returned; }
    long long getTotalCost() const { return totalcost; }
    void setRentStart(std::chrono::system_clock::time_point tp) {
    rentstart = tp;
}


    virtual ~vehicle() {}
};

class car : public vehicle
{
    static string cars[5];

public:
    car() : vehicle() {}
    car(string D, float S, double M, int C) : vehicle(D, S, M, C, chrono::system_clock::now(), false)
    {
    }
    long long returnvehicle() override{
        return vehicle::returnvehicle();
    }

    static void set_nums()
    {
        cars[0] = "PB02GH5643";
        cars[1] = "PB01BH4355";
        cars[2] = "PB05BN3786";
        cars[3] = "PB03WXDF";
        cars[4] = "PB01AS5638";
    }
    static void search()
    {
        bool not_avail = true;
        for (int i = 0; i < 5; i++)
        {
            if (!cars[i].empty())
            {
                cout << "Registration number:" << cars[i] << endl;
                not_avail = false;
            }
        }
        if (not_avail)
        {
            cout << "No cars available." << endl;
        }
    }
};
class scooter : public vehicle
{
    static string scooters[5];

public:
    scooter() : vehicle() {}
    scooter(string D, float S, double M, int C) : vehicle(D, S, M, C,chrono:: system_clock::now(), false) {}
    long long returnvehicle() override{
        return vehicle::returnvehicle();
    }
    static void set_nums()
    {
        scooters[0] = "PB02AM2435";
        scooters[1] = "PB05CF5678";
        scooters[2] = "CH02RT3456";
        scooters[3] = "PB07GH8965";
        scooters[4] = "PB01SV3627";
    }

    static void search()
    {
        bool not_avail = true;
        for (int i = 0; i < 5; i++)
        {
            if (!scooters[i].empty())
            {
                cout << "Registration number:" << scooters[i] << endl;
                not_avail = false;
            }
        }
        if (not_avail)
        {
            cout << "No scooter available." << endl;
        }
    }
};
string car::cars[5];
string scooter::scooters[5];
