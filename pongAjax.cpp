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
	string nameRec = "name_reply"; //use this to identify different users
	string nameSend = "name_request";
	
	string ownName = "Did not receive";
	string otherName = "Did not receive";
	string remote_IP = getenv("REMOTE_ADDR");
	string userno = "-1";
	
	
	// create the FIFOs for communication
	Fifo nameRec_fifo(nameRec);
	Fifo nameSend_fifo(nameSend);

	Cgicc cgi;    // Ajax object
	
	form_iterator name = cgi.getElement("name");
	string message = **name;
	

	nameSend_fifo.openwrite();
	nameSend_fifo.send(message);
	nameSend_fifo.fifoclose();
	
	nameRec_fifo.openread();
	userno = nameRec_fifo.recv();
	ownName = nameRec_fifo.recv();
	otherName = nameRec_fifo.recv();
	if (userno == "1")
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
	nameRec_fifo.fifoclose();
	
	return 0;
}
