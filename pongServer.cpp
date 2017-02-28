

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
	int i = 0;
	
	//needed for ball control
	string canvasWidth = "300";
	string canvasHeight = "300";
	string x = "50"; //positions of the ball
	string y = "50";
	string dx = "2"; //can set these to random numbers in the beginning
	string dy = "8";
	string paddleHeight = "75";
	bool gameInPlay = true;
	
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
	
	while(userno == "2" && gameInPlay == true) {
	
		
		//move the ball according to the game rules
		if (y + dy > canvasHeight || y + dy < "0") {
    		dy = -dy;
    		}
    	if ( x + dx > canvasWidth) {
    		if (y > p2Paddle && y < p2Paddle + paddleHeight) {
    			dy = -dy;
    			}
    		else {
    			gameInPlay = false;
    			}
    	if ( x + dx < "0") {
    		if (y > p1Paddle && y < p1Paddle + paddleHeight) {
    			dy = -dy;
    			}
    		else {
    			gameInPlay = false;
    			}
    		}
    	x += dx;
    	y += dy;
    	
    	
		paddleRecfifo.openread();
		recString = paddleRecfifo.recv();
		
		cout << recString << endl;
		
		string user = recString.substr(1,1);
		
		if (user == "1") {
			p1Paddle = recString.substr(3, recString.length()-3);
			cout << "P1 Paddle: " << p1Paddle << endl;
			paddleSendfifo.openwrite();
			cout << "fifo opened" << endl;			
			paddleSendfifo.send(p2Paddle + "*" + x + "*" + y);
			cout << "Sent: p2: " << p2Paddle << endl;
			cout << "fifo sent" << endl;
		}
		if (user == "2") {
			p2Paddle = recString.substr(3, recString.length()-3);
			cout << "P2 Paddle: " << p2Paddle << endl;
			paddleSendfifo.openwrite();
			cout << "fifo opened" << endl;
			paddleSendfifo.send(p1Paddle + "*" + x + "*" + y);
			cout << "Sent: p1: " << p1Paddle << endl;
			cout << "fifo sent" << endl;
		}
		paddleRecfifo.fifoclose();
		cout << "rec fifo close" << endl;
		paddleSendfifo.fifoclose();
		cout << "send fifo close" << endl;
		i++;


	}
	
	
	
	return 0;
}

/*if (x + dx > width || x + dx < 0) { //if the ball hits the sides of the board. [0--------width]
        dx = -dx;
    }
    
    
    if (y + dy < 0) { //if y is less than 0 (top), reverse the direction of the ball
        dy = -dy;
        
    } else if (y + dy > height) { //if the ball goes farther down than it should
        if (x > paddlex && x < paddlex + paddlew) { //if the x position of the ball is along the paddle, reverse the direction
            dy = -dy;
        } else { //if not along the paddle, clear the game
            clearInterval(intervalId);
        }
    }
    x += dx; //new changes in ball position
    y += dy;
    
    
    need:
    	int canvasWidth;
    	int canvasHeight;
    	int x;
    	int y;
    	int dx;
    	int dy;
    	int paddleHeight;
    	
    	
    	
    	if (y + dy > canvasHeight || y + dy < 0) {
    		dy = -dy;
    		}
    	if ( x + dx > canvasWidth) {
    		if (y > p2Paddle && y < p2Paddle + paddleHeight) {
    			dy = -dy;
    			}
    		else {
    			gameInPlay = false;
    			}
    	if ( x + dx < 0) {
    		if (y > p1Paddle && y < p1Paddle + paddleHeight) {
    			dy = -dy;
    			}
    		else {
    			gameInPlay = false;
    			}
    		}
    	x += dx;
    	y += dy;*/
    			
    		
    	










