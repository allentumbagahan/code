// use $ as canvas element
// use ctx for canvas 2d context
//use this class like this : array.push(new fish(x, y, sizeArea))
// animate the for each functions: fish.draw(), fish.rotate()
bg1 = document.createElement("img")
bg1.setAttribute("src", "./img/Aquarium1.png")
bg1.setAttribute("id", "image")


elem1 = document.createElement("img")
elem1.setAttribute("src", "./img/fish.png")
elem1.setAttribute("id", "image")

elem2 = document.createElement("img")
elem2.setAttribute("src", "./img/fishflipX.png")
elem2.setAttribute("id", "image")

elem3 = document.createElement("img")
elem3.setAttribute("src", "./img/fishflipY.png")
elem3.setAttribute("id", "image")

elem4 = document.createElement("img")
elem4.setAttribute("src", "./img/fishflipYX.png")
elem4.setAttribute("id", "image")

elem5 = document.createElement("img")
elem5.setAttribute("src", "./img/fish2.png")
elem5.setAttribute("id", "image")

elem6 = document.createElement("img")
elem6.setAttribute("src", "./img/fish2flipX.png")
elem6.setAttribute("id", "image")

elem7 = document.createElement("img")
elem7.setAttribute("src", "./img/fish2flipY.png")
elem7.setAttribute("id", "image")

elem8 = document.createElement("img")
elem8.setAttribute("src", "./img/fish2flipYX.png")
elem8.setAttribute("id", "image")


class fish {
  constructor(x, y, sizeArea, image1, image2, image3, image4) {
    this.x = x
    this.y = y
    this.sizeX = (sizeArea/2)
    this.sizeY = (sizeArea/2)
    this.centerX = (x + (this.sizeX/2))
    this.centerY = (y + (this.sizeY/2))
    this.angle = 0
    this.targetX = 0
    this.targetY = 0
    this.status = "alive" //"alive" or "died"
    this.action = "idle" // "idle" or "moving"
    this.image1 = image1
    this.image2 = image2
    this.image3 = image3
    this.image4 = image4
    
  }
  draw() { 
    ctx.save()
    this.rotate()
    ctx.translate(this.x, this.y)
    ctx.rotate(this.angle*Math.PI/180) //degree*Math.Pi/180
    ctx.fillStyle = "transparent"
    ctx.fillRect(0,0, this.sizeX, this.sizeY)
    console.log(this.angle)
    var num = 1
    if (this.angle < 90 && this.angle >= 0) {
      num = 1
    }
    if (this.angle < 0 && this.angle > -90){
      num = 1
    }
    if (this.angle > 90 && this.angle < 270) {
      num = 3
    }
    if (this.angle < -90 && this.angle >= -270) {
      num = 3
    }
    
    if(this.x != 0 && this.y == this.targetY){
      if (this.x > this.targetX) {
        num = 2
      }
      if (this.x < this.targetX) {
        num = 1
      }
    }
    if(this.y != 0 && this.x == this.targetX){
      if (this.x > this.targetX) {
        num = 2
      }
      if (this.x < this.targetX) {
        num = 1
      }
    }
    switch (num) {
      case 1 :
        ctx.drawImage(this.image1, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
        console.log("image1")
        break;
      case 2 :
        ctx.drawImage(this.image2, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
        console.log("image2")
        break;

      case 3 :
        ctx.drawImage(this.image3, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
        console.log("image3")
        break;

      case 4 :
        ctx.drawImage(this.image4, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
        console.log("image4")
        break;
      
    }
    /*if (this.angle < 90 && this.angle > 0) {
    ctx.drawImage(elem1, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
    console.log("image1")
      }else {
        ctx.drawImage(elem2, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
        console.log("image2")
      } */
      
      ctx.restore()
    this.findTarget()
    this.move()
    
  }
  rotate() {
    this.centerX = (this.x + (this.sizeX/2))
    this.centerY = (this.y + (this.sizeY/2))
    this.angle = Math.atan2((this.targetY - this.centerY), (this.targetX - this.centerX)) * (180/Math.PI)
    if (this.angle > 90 && this.angle < 130) {
      this.angle += 40
      this.findTarget()
    }
    if (this.angle < 90 && this.angle > 50) {
      this.angle -= 40
      this.findTarget()
    }
    if (this.angle < -90 && this.angle > -130) {
      this.angle -= 40
      this.findTarget()
    }
    if (this.angle > -90 && this.angle < -50) {
      this.angle += 40
      this.findTarget()
    }

  }

  move() {
    if(Math.floor(Math.hypot((this.targetY - this.centerY), (this.targetX - this.centerX))) - 35 >= 20) {
   
            if(this.y > this.targetY) {
              this.y -= 1
                }
                if(this.y < this.targetY) {
                this.y += 1
                  }
            if(this.x > this.targetX) {
            this.x -= 1
             }
              if(this.x < this.targetX) {
              this.x += 1
                }
              
              
    }else{
      this.action = "idle"
      this.angle = 0 
    }
  }
  findTarget(){
    
    if (this.action == "idle") {
      this.targetX = (Math.random() * ($.width - this.sizeX)) + this.sizeX
      this.targetY = (Math.random() * ($.height - this.sizeY - 380)) + this.sizeY + 200
      this.action = "moving"
    }
    if (this.targetX < this.targetY ) {
      this.targetX = (Math.random() * ($.width - this.sizeX)) + this.sizeX
      this.targetY = (Math.random() * ($.height - 380)) + this.sizeY + 200
      this.action = "moving"
    }
  
}
}

