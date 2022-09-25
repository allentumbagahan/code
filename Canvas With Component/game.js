
//allen
//Delacruz


	// c = canvas and get canvas attributes
	var c = document.getElementById("canvas");
	ctx = c.getContext("2d");


	//when screen is click
function showCoord(event) {
		var x = Math.abs(event.clientX );     // Get the horizontal coordinate
		var y = Math.abs(event.clientY);     // Get the vertical coordinate
		console.log("mouseX : " + Math.floor(x));
		console.log("mouseY : " + Math.floor(y));
		c.scrollRight
		//onclick in canvas
			//define what box clicked by mouse
				

				
}
	//window heigth and width
	var winWidth = window.screen.availWidth;
	var winHeigth = window.screen.availHeight;
	var bodyH = document.body.clientHeight
	var bodyW = document.body.clientWidth
	console.log("body height " + bodyH)
	console.log("body width " + bodyW)

    //set size of canvas
	c.width  = bodyW
	c.height  = bodyH 
			
	

//resize if srceen size changed
function setScreenSize() {
	var bodyH = document.body.clientHeight
	var bodyW = document.body.clientWidth
	c.width  = bodyW
	c.height  = bodyH
}




//setup the game and add component
	//make component for Player
class Player {
	constructor(x, y, sizeX, sizeY, speed) {
		this.x = x 
		this.y = y
		this.sizeX = sizeX
		this.sizeY = sizeY
		this.speed = speed
		this.targetPlaceX = this.targetPlaceX
		this.targetPlaceY = this.targetPlaceY
		this.distanceX = this.distanceX
		this.distanceY = this.distanceY
		
	}
	draw() {
		ctx.beginPath()
		ctx.rect(this.x, this.y, this.sizeX, this.sizeY)
		ctx.restore()
		ctx.stroke()
		ctx.fill()
		
	}
	update() { 
		
		if (this.distanceX == 0 && this.distanceY == 0 ) {
			this.moveOn()
		} 
	
		if (this.x ==  this.targetPlaceX) {
			
		}else {
			if (this.x < this.targetPlaceX) {
			this.x +=  this.speed 
		}else {
			this.x -=  this.speed 
		}
		}
		
		if (this.y == this.targetPlaceY) {
			
			
		} else {
			if (this.y < this.targetPlaceY) {
				this.y +=  this.speed 
			}	else {
				this.y -=  this.speed 
			}
		}
		
		
		
		 
		 
		 /* this update cannot change the position of this player but the 
		 data value of x, To change the position in canvas try to clear the canvas and re-draw this component with new position value*/
		
		 this.distanceX = Math.floor(this.targetPlaceX - this.x)
		 this.distanceY = Math.floor(this.targetPlaceY - this.y)
		 if (this.distanceX % this.speed != 0){
			this.targetPlaceX -= (this.distanceX%this.speed)
		}
		if (this.distanceY % this.speed != 0){
			this.targetPlaceY -= (this.distanceY%this.speed)
		}
		 console.log(player)
		
	}
	moveOn() {
		this.targetPlaceX = Math.floor(Math.random () * (c.width - 50) + 50)
		this.targetPlaceY = Math.floor(Math.random () * (c.height - 50) + 50)
		

		// check if target is visible factor for speed
		console.log(this.targetPlaceX)
		console.log(this.targetPlaceY)
		
	}

	
}

const player = new Player(0, 50, 50, 50, 156) // make a player with component properties
console.log(player)
player.draw() // try to draw a player

function animate () {
	ctx.clearRect(0, 0, c.width, c.height) // clear the whole canvas
	requestAnimationFrame(animate)
	player.draw() // then draw the new rectangle with new position
	player.update()
	console.log("animate")

}

animate() 
player.moveOn()

/* credits to the owner totoy */ 
/* wag puro gaya */

