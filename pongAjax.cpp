/*************************************************************/
/* Pong CGI program                                          */
/*************************************************************/

#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

int main()
{
	
	string paddleRecFromServer;
	
  ofstream log;
  log.open("/tmp/gavin.log",ios::out | ios::app);
  
  string nameRec = "name_reply"; //use this to identify different users
	string nameSend = "name_request";
	string paddleRec = "paddle_reply";
	string paddleSend = "paddle_request";
	
	string ownName = "Did not receive";
	string otherName = "Did not receive";
	string remote_IP = getenv("REMOTE_ADDR");
	string userno = "-1";
	
	Cgicc cgiNum;    // Ajax object
	form_iterator userNumber = cgiNum.getElement("userNumber");
	userno = **userNumber;
	
	Cgicc cgi;    // Ajax object	
	form_iterator name = cgi.getElement("name");
	string message = **name;
	
	Cgicc cgiPaddle;    // Ajax object	
	form_iterator paddley = cgiPaddle.getElement("paddley");
	string paddlePos = **paddley;
	
	cout << "Content-Type: text/plain\n\n";
	
	log << "Recv :" +userno+":"+message+":"+paddlePos << endl;
	
	if(userno == "-1") //get the user number from the server
	{
		Fifo nameRec_fifo(nameRec);
		Fifo nameSend_fifo(nameSend);
		
		nameSend_fifo.openwrite();
		nameSend_fifo.send(userno);
		nameSend_fifo.fifoclose();
	
		nameRec_fifo.openread();
		userno = nameRec_fifo.recv();
		nameRec_fifo.fifoclose();

		log << "User#: " << userno << endl;
		//		cout << "Hello word\n";
		cout << userno;
		
	}
	
	else
	{
		Fifo paddleRec_fifo(paddleRec);
		Fifo paddleSend_fifo(paddleSend);
		
		paddleSend_fifo.openwrite();
		paddleSend_fifo.send("*" + userno + "*" + paddlePos);
		
		
		paddleRec_fifo.openread();
		log << "Waiting for read from server\n";
		paddleRecFromServer = paddleRec_fifo.recv();
		cout << paddleRecFromServer << endl;
		log << "move:" << paddleRecFromServer << endl;
		paddleRec_fifo.fifoclose();
		paddleSend_fifo.fifoclose();
	}
	
	
	
	
	// create the FIFOs for communication
	
	/*if (userno == "1")
	{
		cout << "Content-Type: text/html\n\n";
		cout << "Username: " << ownName;
		cout << "<br>Other connected user: " << otherName;
		cout << "<br>You are the first user, waiting for a second connection.";
	}
	if (userno == "2")
	{
		cout << "Content-Type: text/html\n\n";
		cout << "Username: " << ownName;
		cout << "<br>Other connected user: " << otherName;
		cout << "<br>You are the second user, please press ready when you are prepared to start the game.";
	}
	if (userno == "3")
	{
		cout << "Content-Type: text/html\n\n";
		cout << "Sorry " << ownName << " the game is full, please visit at another time.";
	}
	*/
	
	return 0;
}
