#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

enum Vehicle{
    TWO_WHEELER, THREE_WHEELER, FOUR_WHEELER
};
class Ticket{
    int ticketId;
    time_t entryTime;
    int rate;
    int floorNo;
    public:
    Ticket() : ticketId(0), entryTime(0), rate(0), floorNo(0) {}
    Ticket(int t,time_t et, int r,int fn):ticketId(t),entryTime(et),rate(r),floorNo(fn){}
    int getEntryTime(){return entryTime;}
    int getRate(){return rate;}
    int getTicketId(){return ticketId;}
    int getFloorNo(){return floorNo;}
};

class User{
    string name;
    string vehicleNo;
    Vehicle vehicleType;
    Ticket ticket;
    public: 
    User(const string& name, const string& vehicleNo, Vehicle vt)
        : name(name), vehicleNo(vehicleNo), vehicleType(vt) {}
    string getName(){return name;}
    string getVehicleNo(){return vehicleNo;}
    Vehicle getVehicleType(){return vehicleType;}
    void setTicket(Ticket &t){
        ticket = t;
    }
    Ticket getTicket(){
        return ticket;
    }
};



class ParkingFloor{
    int floorNo;
    int twoWheelers;
    int currentTwoWheelers;
    int threeWheelers;
    int currentThreeWheelers;
    int fourWheelers;
    int currentFourWheelers;
    public:
    ParkingFloor(int f,int tw,int thw,int fw):floorNo(f),twoWheelers(tw),threeWheelers(thw),fourWheelers(fw){
        currentFourWheelers = currentThreeWheelers = currentTwoWheelers = 0;
    }
    bool isTwoWheelerParkingAvailable(){return twoWheelers> currentTwoWheelers;}
    bool isFourWheelerParkingAvailable(){return fourWheelers> currentTwoWheelers;}
    bool isThreeWheelerParkingAvailable(){return threeWheelers> currentTwoWheelers;}
    void incFourWheeler(){fourWheelers++;}
    void decFourWheeler(){fourWheelers--;}
    void incThreeWheeler(){threeWheelers++;}
    void decThreeWheeler(){threeWheelers--;}
    void incTwoWheeler(){twoWheelers++;}
    void decTwoWheeler(){twoWheelers--;}
    void printStatus() {
        cout << "Floor " << floorNo << ": "
             << "Two-Wheelers (" << currentTwoWheelers << "/" << twoWheelers << "), "
             << "Three-Wheelers (" << currentThreeWheelers << "/" << threeWheelers << "), "
             << "Four-Wheelers (" << currentFourWheelers << "/" << fourWheelers << ")\n";
    }
};

class ParkingLot{
    vector<ParkingFloor>pf;
    int floors;
    int twoWheelerRate;
    int threeWheelerRate;
    int fourWheelerRate;
    unordered_map<Vehicle,int>rateMap;
    public:
    ParkingLot(int floors,vector<ParkingFloor>&pf):floors(floors),pf(pf)
    {
        rateMap[TWO_WHEELER] = 20;
        rateMap[THREE_WHEELER] = 40;
        rateMap[FOUR_WHEELER] = 60;
    }
    int getFourWheelerRate(){return fourWheelerRate;}
    int getThreeWheelerRate(){return threeWheelerRate;}
    int getTwoWheelerRate(){return twoWheelerRate;}
    void printParkingStatus() {
        cout << "Current Parking Status:\n";
        for (auto &floor : pf) {
            floor.printStatus();
        }
        cout << endl;
    }
    void entryService(User user){
        for(int i=0;i<floors;i++){
            if(user.getVehicleType() == FOUR_WHEELER){
                if(pf[i].isFourWheelerParkingAvailable()){
                    pf[i].incFourWheeler();
                    time_t now = system_clock::to_time_t(system_clock::now()); // Current time
                    Ticket t1(1879,now,getFourWheelerRate(),i);
                    user.setTicket(t1);
                    cout << "Entry successful for " << user.getName() << " at floor " << i << endl;
                return;
                    printParkingStatus();

                    return;
                }
            }else
            if(user.getVehicleType() == THREE_WHEELER){
                if(pf[i].isThreeWheelerParkingAvailable()){
                    pf[i].incThreeWheeler();
                    time_t now = system_clock::to_time_t(system_clock::now()); // Current time
                    Ticket t1(10093,now,getThreeWheelerRate(),i);
                    user.setTicket(t1);
                    cout << "Entry successful for " << user.getName() << " at floor " << i << endl;
                    printParkingStatus();
                    return;
                }
            }
            else{
                if(pf[i].isTwoWheelerParkingAvailable()){
                    pf[i].incTwoWheeler();
                    time_t now = system_clock::to_time_t(system_clock::now()); // Current time
                    Ticket t1(1003,now,getTwoWheelerRate(),i);
                    user.setTicket(t1);
                    cout << "Entry successful for " << user.getName() << " at floor " << i << endl;
                    printParkingStatus();
                    return;
                }
            }
        }
    }
    void exitService(User user){
        Ticket ticket = user.getTicket();
        time_t now = system_clock::to_time_t(system_clock::now()); // Current time
        int totalTime = difftime(now, ticket.getEntryTime()) / 60; // Time in minutes
        int price = totalTime*rateMap[user.getVehicleType()];
        cout<<"--------"<<user.getName()<<" ------ "<< "your total amount is :- "<< price<<endl;
        pf[ticket.getFloorNo()].decFourWheeler();
        printParkingStatus();
    }
};

int main(){
    ParkingFloor f1(0,3,4,2);
    ParkingFloor f2(1,2,3,4);
    vector<ParkingFloor>pvector;
    pvector.push_back(f1);
    pvector.push_back(f2);

    ParkingLot parkingLot(2,pvector);
    User u1("Anil","22BH1159D",TWO_WHEELER);

    parkingLot.entryService(u1);
    this_thread::sleep_for(chrono::seconds(10)); // Simulate time passage
    parkingLot.exitService(u1);

}
