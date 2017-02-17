/*************************************************************/
/* Authors: Alex Seaver and Coire Gavin-Hanner               */
/* Date Created: 2-17-17					                 */
/*                                                           */
/* Variables:
		ballx, bally
		pad1y, pad1x, pad2y, pad2x
		padw, padh (same for both paddles)
		height
		*/



#include <iostream>
#include "fifo.h"
using namespace std;

int main()
{
	string p1Name, p2Name;
	string nameRec_fifo = "receivename";
	string nameSend_fifo = "sendname";
	
	cout << "test: main_1"
	// create the FIFOs for communication
	Fifo nameRecfifo(nameRec_fifo);
	Fifo nameSendfifo(nameSend_fifo);

	cout << "test: main_2 (fifo's created)"

	nameRecfifo.openread();
	p1Name = nameRecfifo.recv();
	nameRecfifo.fifoclose();	
	cout << "test: main_3 (name received)"
	cout << "Name: " << p1Name << endl;

	nameSendfifo.openwrite();
	nameSendfifo.send(p1Name);
	nameSendfifo.fifoclose;	
	cout << "test: main_4 (name sent)"

	
	
	cout << "Server to eventually run pong\n";
	
	while(1)
	{
		
	}
	

	//system("pause");
	return 0;
}
