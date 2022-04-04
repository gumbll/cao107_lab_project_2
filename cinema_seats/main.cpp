//////////////////////////////////////////////////////////////////////////////
//
// Project Name: CAO107 LAB 2 - Cinema seats
// Student Name: Lachlan Ashton
// Student ID: 00327153T
// 
//////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <Windows.h>
#include "colornames.h"
#include "structures.h"
using namespace std::chrono_literals;

int num_threads = std::thread::hardware_concurrency(); // this is here for no reason

std::vector<Order> ordersCompleted;
std::mutex mtx;

bool sellSeats(Order& order, std::vector<Seat>& seats);
void showSeats(std::vector<Seat>& seats);
void printOrder(Order& order);

//TODO:
// LIST OF SEATS AVAILABLE
// LIST OF TICKETS SOLD
// 5 cashiers = threads
// 1 cashier can do all the work in a loop
// It gets crazy for the cashiers.

int main()
{
  std::vector <std::thread> thvec;
  auto orders = std::vector<Order>{
    { "Cust 1", on_red, {"G1", "G2"}},
    { "Cust 2", on_blue, {"G1"}},
    { "Cust 3", on_green, {"G4", "G5"}},
    { "Cust 4", on_yellow,  {"G5"}}, // potential disruptor here
    { "Cust 5", on_magenta, {"G4"}},
    { "Cust 6", on_cyan,  {"G3", "G4"}}  // Another cheeky one
  };

  auto seats = std::vector<Seat>{
    { "G1", true },
    { "G2", true },
    { "G3", true },
    { "G4", true },
    { "G5", true },
  };

  std::cout << "\n" << "## Customers Enter" << "\n\n";
  for (auto& order : orders)
  {
    thvec.push_back(std::thread(printOrder, std::ref(order)));
 
    //printOrder(order);
  }
  //sleep to so that text isnt all over the place
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  showSeats(seats);
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  
  
  // create multiple threads/sales clerks
  std::cout << "\n" << "## Sales Begin" << "\n\n";
  for (Order& order : orders){ 

      thvec.push_back(std::thread(sellSeats, std::ref(order), std::ref(seats)));

  }  

  std::cout << "\n" << "## Successful Orders" << "\n\n";
  for (auto& order : ordersCompleted){
    thvec.push_back(std::thread(printOrder, std::ref(order)));

    //printOrder(order);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  showSeats(seats);

  //join each thread once all tasks are complete
  // this might not be required here
  for (int i = 0; i < thvec.size(); i++) {
      if (thvec.at(i).joinable())
        thvec.at(i).join();
  }
}



bool sellSeats(Order& order, std::vector<Seat>& seats)
{
    mtx.lock();
    std::this_thread::sleep_for(1000ms);
    
    std::cout << white << order.color << order.custName << white << on_black;

    // if the seats in the order aren't already sold, mark them sold and return true
    bool allAvailable{ true };
    for (auto& seatId : order.seatIds)
    {
        for (auto& seat : seats)
        {
            // If we find the seat and it's not available, order is ded.
            if (seat.id == seatId && !seat.available)
            {
                std::cout << ": unavailable D:\n";
                allAvailable = false;
                break;
            }
        }
    }

    if (allAvailable)
    {
        std::cout << ": Sold!\n";
        order.sold = true;
        ordersCompleted.push_back(order);
        // oh boy, we sure wasted some time there before marking the seats
        // unavailable. What could go wrong?
        for (auto& seatId : order.seatIds)
        {
            for (auto& seat : seats)
            {
                if (seat.id == seatId) 
                    seat.available = false;
            }
        }
    }
    mtx.unlock();
    return allAvailable;
    
}



void printOrder(Order& order)
{
    mtx.lock();
    std::cout << white << order.color << order.custName << white << on_black << ", seats: [";
    for (auto& seatId : order.seatIds)
    {
        std::cout << seatId << " ";
    }
    std::cout << "\b]\n";   // backspace removes the space after the last seat id
    mtx.unlock();
}



void showSeats(std::vector<Seat>& seats)
{
    mtx.lock();
    std::cout << "\n" << "## Seat Availability" << "\n\n";
    int seatCount = seats.size();
    std::string line = "-";
    for (auto i = 0; i < seatCount; ++i)
    {
        line += "-----";
    }

    //cout << line << endl;
    for (auto& seat : seats)
    {
        // If the seat is available, use green background, else red
        // if this syntax looks weird, google "universal initializers" and
        // "c++ ternary operator"
        std::string bg{ (seat.available) ? on_green : on_red };
        std::cout << "|" << white << bg << " " << seat.id << " " << white_on_black;
    }
    std::cout << "|" << std::endl;
    //cout << line << endl;
    mtx.unlock();
    
}