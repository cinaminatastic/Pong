

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
	string p1Name, p2Name, p1Paddle = "150", p2Paddle = "150", recString;
	string nameRec_fifo = "name_request";
	string nameSend_fifo = "name_reply";
	string paddleRec_fifo = "paddle_request";
	string paddleSend_fifo = "paddle_reply";
	string userno = "-1";
	string jsUserno = "0";
	
	// create the FIFOs for communication
	Fifo nameRecfifo(nameRec_fifo);
	Fifo nameSendfifo(nameSend_fifo);
	Fifo paddleRecfifo(paddleRec_fifo);
	Fifo paddleSendfifo(paddleSend_fifo);
	
	while(userno != "2" && userno != "3") {
		nameRecfifo.openread();
		jsUserno = nameRecfifo.recv();
		nameRecfifo.fifoclose();
		
		if (jsUserno == "-1" && userno == "-1") //no user has connected yet
		{
			userno = "1";
			nameSendfifo.openwrite();
			nameSendfifo.send(userno);
			nameSendfifo.fifoclose();
			cout << userno << endl;
		}
		else if (jsUserno == "-1" && userno == "1") //first user is connected
		{
			userno = "2";
			nameSendfifo.openwrite();
			nameSendfifo.send(userno);
			nameSendfifo.fifoclose();
			cout << userno << endl;

		}
		else //two users are already connected
		{
			userno = "3";
			nameRecfifo.openread();
			p2Name = nameRecfifo.recv();
			nameRecfifo.fifoclose();
			cout << "Name: " << p2Name << endl;

			nameSendfifo.openwrite();
			nameSendfifo.send(userno);
			nameSendfifo.send(p2Name);
			nameSendfifo.send("None");
			nameSendfifo.fifoclose();
		}
	}
	
	while(userno == "2") {
		paddleRecfifo.openread();
		recString = paddleRecfifo.recv();
		paddleRecfifo.fifoclose();
		
		string user = recString.substr(1,1);
		if (user == "1") {
			p1Paddle = recString.substr(2, recString.length()-2);
			cout << "P1 Paddle: " << p1Paddle << endl;
			paddleSendfifo.openwrite();
			paddleSendfifo.send(p2Paddle);
			paddleSendfifo.fifoclose();
		}
		if (user == "2") {
			p2Paddle = recString.substr(2, recString.length()-2);
			cout << "P2 Paddle: " << p2Paddle << endl;
			paddleSendfifo.openwrite();
			paddleSendfifo.send(p1Paddle);
			paddleSendfifo.fifoclose();
		}
		
	}
	
	
	
	return 0;
}
