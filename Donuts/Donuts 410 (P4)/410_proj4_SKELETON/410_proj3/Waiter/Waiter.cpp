//=========================================================
// Name: Waiter.cpp
// Version: 11/19/16
// Authors: Micah Coffman and Jonathan Thomas
// Description: Waiter is responsible for reading and 
//				interpretting orders from an input file.
//=========================================================
#include <string>
#include "stdlib.h"

#include "..\includes\Waiter.h"
#include "..\includes\externs.h"

using namespace std;

//waiter's constructor. initializes a waiter's id and the filename to read from based on the two parameters passed in
Waiter::Waiter(int id, std::string filename) :id(id), myIO(filename) {
}

//waiter's destructor
Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder) {
	return myIO.getNext(anOrder);
}

//as long as there are more orders in the file, waiter continues parsing, reading, and interpretting the data
void Waiter::beWaiter() {
	ORDER anOrder;

	//while there's another order...
	while (getNext(anOrder) == SUCCESS)
	{
		//push the order onto the order in queue
		order_in_Q.push(anOrder); 
		cv_order_inQ.notify_all();
	}
	//no more orders
	b_WaiterIsFinished = true;
	cv_order_inQ.notify_all();
}

