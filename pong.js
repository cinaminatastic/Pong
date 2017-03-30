var x = 150; //positions of the ball
var xNew;
var dx = 2; //can set these to random numbers in the beginning
var mirrorx = 150;
var y = 150;
var ctx;
var width;
var height;
var paddley;
var paddle2y;
var paddlew = 10;
var paddleh = 75;
var intervalId = 0;
var userNumber = -1;
var padRec;
var intVar;
var waitPaddleMove = false;

var XMLHttp;
var XMLHttp2;
var upDown = false;
var downDown = false;
var name
var i = 0;

function initialize() { //this function is called at least

	if(navigator.appName == "Microsoft Internet Explorer") {
		XMLHttp = new ActiveXObject("Microsoft.XMLHTTP");
		XMLHttp2 = new ActiveXObject("Microsoft.XMLHTTP");
	} else {
		XMLHttp = new XMLHttpRequest(); //this else part is entered using chrome
		XMLHttp2 = new XMLHttpRequest();
	}
	document.getElementById("canvas").style.background = 'rgb(128, 128, 128)';
	init();
	paddley = height/2;
	paddle2y = height/2;

}

function paddleEnd() {
    clearInterval(intVar);
}
function paddle() {

    intVar = setInterval(function(){ movePaddle()}, 500);
}

function movePaddle() {
    if (waitPaddleMove) {
		console.log("Error - previous paddle move not complete");
		//return;
    }
    waitPaddleMove = true;
    console.log(waitPaddleMove);
    
    if(upDown) {
		paddley -= 10;
		
	} else if(downDown) {
		paddley +=10;
	}

    
    
    var sendStr = "/cgi-bin/gavinhannerc_pongAjax.cgi?" + "&name=" + name + "&userNumber=" + userNumber + "&paddley=" + paddley;
    console.log("Send:"+ sendStr);
    XMLHttp.open("GET", sendStr, true);

    XMLHttp.onreadystatechange=function() {
    	if (XMLHttp.readyState == 4) {
			padRec = XMLHttp.responseText;;
			paddle2y = padRec.slice(0, padRec.indexOf("*"));
			xNew = padRec.slice(padRec.indexOf("*") + 1, padRec.lastIndexOf("*"));
			if (userNumber === "2") { //setting ball position
				dx = mirrorx - xNew;
				x += dx;
				mirrorx = xNew;
				}
			else {
				x = xNew;
				}
				
			y = padRec.slice(padRec.lastIndexOf("*") +1, padRec.length);
			
			if (padRec === undefined) {
    		} else {
				clear(); //clears the rectangle...?
				rect(0, paddley, paddlew, paddleh); //sets paddle 1
				rect(width - paddlew, paddle2y, paddlew, paddleh); //sets paddle 2
				circle(x, y, 10); //sets the ball in motion
				waitPaddleTrue = false;
			
   		 	}
		}
	}
    
    XMLHttp.send(null);
    
}

function getUsername() { //function is called when submit is pressed

    name = document.getElementById('name').value;	     
    console.log("getUsername");
    if (name === undefined) return;

    XMLHttp.open("GET", "/cgi-bin/gavinhannerc_pongAjax.cgi?" + "&name=" + name + "&userNumber=" + userNumber + "&paddley=" + paddley, true);
    XMLHttp.onreadystatechange=function() {	
		var tuser = XMLHttp.responseText;
		console.log("Getting user:"+tuser);
		if ((tuser !== undefined) && (tuser.length > 0)) {
			userNumber = tuser;
		}
		document.getElementById('response_area').innerHTML = userNumber;;
		console.log("setting user number: "+ userNumber);
    }
    XMLHttp.send(null);
    upDown = false;
	downDown = false;
}

function rect(x, y, w, h) {
    ctx.beginPath();
    ctx.rect(x, y, w, h); 
    ctx.closePath();
    ctx.fill();
}

function circle(x, y, r) {
    ctx.beginPath();
    ctx.arc(x, y, r, 0, Math.PI * 2, true);
    ctx.closePath();
    ctx.fill();
}

function clear() {
    ctx.clearRect(0, 0, width, height);
}

$(document).keydown(function(e) { //gives the value of the key when you press down
    if(e.keyCode == 40) {
        downDown = true;
    } else if(e.keyCode == 38) {
        upDown = true;
    }
    else if(e.keycode != 40) {
    	downDown = false;
    }
    else if(e.keycode != 38) {
    	upDown = false;
    }
});
$(document).keyup(function(e) { //tells the program that you have stopped pressing the key
    if(e.keyCode == 40) {
        downDown = false;
    } else if(e.keyCode == 38) {
        upDown = false;
    }
    else if(e.keycode != 40) {
    	downDown = false;
    }
    else if(e.keycode != 38) {
    	upDown = false;
    }
});
	

function init() {
    ctx = $("#canvas")[0].getContext("2d");
    width = $("#canvas").width();
    height = $("#canvas").height();
    paddlex = width / 2;
}