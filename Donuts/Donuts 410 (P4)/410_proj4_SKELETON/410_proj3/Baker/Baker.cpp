//===================================================================
// Name: Baker.cpp
// Version: 11/19/16
// Authors: Micah Coffman and Jonathan Thomas
// Description: Baker is responsible for baking and 
//				boxing the donuts. It gets the orders from waiter and 
//				fills them
//===================================================================
#include <mutex>

#include "..\includes\Baker.h"
#include "..\includes\externs.h"
using namespace std;

//initializes baker's id to the int passed in
Baker::Baker(int id) :id(id)
{
}

//baker's destructor
Baker::~Baker()
{
}

//bake and box bakes and boxes the donuts, ensuring only 12 to a box
void Baker::bake_and_box(ORDER &anOrder) {
	Box abox;
	for (int i = anOrder.number_donuts; i > 0; i--)
	{
		DONUT adonut;
		if (!abox.addDonut(adonut))
		{
			//box is full, increment number of boxes in this order
			anOrder.boxes.push_back(abox);
			abox.clear();//clear box
			abox.addDonut(adonut);//add next donut
		}
	}
	//as long as the box has donuts in it, update the order
	if (abox.size() != 0)
	{
		anOrder.boxes.push_back(abox);
	}
}

//be baker calls bake and box to bake and box all donuts 
//as long as there's still orders in the order in queue.
//Also pushes completed orders out to output vector 
void Baker::beBaker() {
	ORDER anOrder;

	while (!b_WaiterIsFinished)
	{
		unique_lock<mutex> lk(mutex_order_inQ);
		cv_order_inQ.wait(lk);

		while (!order_in_Q.empty())
		{
			//accessing input queue, need to block other threads from accessing it
			mutex_order_outQ.lock();
			anOrder = order_in_Q.front();
			order_in_Q.pop();
			mutex_order_outQ.unlock();

			//bake / box the donuts
			bake_and_box(anOrder);

			//accessing the output queue, need to prevent other threads from accessing it
			mutex_order_outQ.lock();
			order_out_Vector.push_back(anOrder);
			mutex_order_outQ.unlock();
		}
	}
}
