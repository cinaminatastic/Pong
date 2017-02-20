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



#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include "fifo.h"
using namespace std;

int main()
{
	string p1Name, p2Name;
	string nameRec_fifo = "name_request";
	string nameSend_fifo = "name_reply";
	
	cout << "test: main_1\n";
	// create the FIFOs for communication
	Fifo nameRecfifo(nameRec_fifo);
	Fifo nameSendfifo(nameSend_fifo);
	cout << "test: main_2 (fifo's created)\n";
	
	
	while(1) {
		cout << "teststststs\n";
		nameRecfifo.openread();
		
		cout << "teststststs\n";
		p1Name = nameRecfifo.recv();
		
		cout << p1Name << endl;
		nameRecfifo.fifoclose();
			
		cout << "test: main_3 (name received)\n";
		cout << "Name: " << p1Name << endl;

		/*nameSendfifo.openwrite();
		nameSendfifo.send(p1Name);
		nameSendfifo.fifoclose();*/
		cout << "test: main_4 (name sent)\n";

		cout << "Server to eventually run pong\n";
	}
	
	return 0;
}
