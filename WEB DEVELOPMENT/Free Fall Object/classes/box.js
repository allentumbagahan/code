class box {
  constructor(x, y, sizeArea) {
    
    this.x = x
    this.y = y
    this.sizeArea = sizeArea
    this.sizeX = sizeArea/2
    this.sizeY = sizeArea/2
    this.initialVelocity = 1
    this.velocity = 0
    this.timeInAir = 0
    this.collide = "false"
    this.colliderBoxCenterX = this.x + (this.sizeX/2)
    this.colliderBoxCenterY = this.y + (this.sizeY/2)
  }
  draw() {
    ctx.beginPath()
    ctx.rect(this.x, this.y, this.sizeX, this.sizeY)
    ctx.stroke()
    ctx.fill()
  }
  update(){
    
    
    if (c.height > (this.y + this.sizeY)) {
      //if box in the air then 
      this.timeInAir += 0.01
      //changing the free fall velocity 
      this.velocity = Math.floor(velocityCal(this.initialVelocity, this.timeInAir))
     
      //falling false
        if (this.collide == "false") {
   
              this.y += this.velocity 
         
         
                  if((this.y + this.sizeY) < c.height - 4){
       
                  } else {
                    this.timeInAir = 0
      
                         }
       }
      
    }
    boxes.forEach((box) => {
      if (this.y != box.y) {
        console.log((Math.floor(
          Math.hypot(
            (box.x - this.x),
            (box.y - this.y)
            ))))
       if ((Math.floor(
         Math.hypot(
           (box.x - this.x),
           (box.y - this.y))) - 
(this.sizeArea/1.6) ) < 0){
        this.collide = "true"
        
      }
       
      }
    })
    
    
    
  }
}
