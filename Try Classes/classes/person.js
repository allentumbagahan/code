class person {
  constructor(x, y, size, energy, speed){
    this.posX = x
    this.posY = y
    this.size = size
    this.sizeX = size/2
    this.sizeY = size/2
    this.targetPlaceX = x
    this.targetPlaceY = y
    this.action = 0
    this.ActionStatus = "idle" //idle, move
    this.energy = (80 - (energy * 5))
    this.speed = speed
    this.hunger = 100
    this.targetfood = 0
    this.status = "alive" //alive or died
    
    
    
    
    
    
  }
  
    
  
  
  draw () {
  if(this.status == "alive"){
    ctx.beginPath()
    ctx.rect(this.posX, this.posY, this.sizeX, this.sizeY)
    ctx.stroke()
    
    if (this.ActionStatus == "move"){
      ctx.fillStyle = "red"
      ctx.fill()
      
    } else {
      ctx.fillStyle = "black"
      ctx.fill()
      this.idleORmove()
      
    }
    //draw hunger bar
    ctx.beginPath()
    ctx.rect(this.posX - 5, this.posY - 10, this.sizeX + 10, 2)
    ctx.fillStyle = "black"
    ctx.stroke()
    ctx.beginPath()
    ctx.rect(this.posX - 5, this.posY - 10, (this.sizeX + 10) * (this.hunger/100), 2)
    if (this.hunger < 60) {
    ctx.fillStyle = "red"
    }else {
      ctx.fillStyle = "green"
    }
    ctx.stroke()
    ctx.fill()
    
  }
  }
  findPlace() {
    
    if (this.ActionStatus == "idle") {
    if (this.action == 1) {
      if (this.hunger > 60) {
      this.targetPlaceX = (Math.floor(Math.random()*c.width - 25) + 25)
      this.targetPlaceY = (Math.floor(Math.random()*c.height - 25) + 25)
      }
    }
      }
      
    }
    
  move () {
    if (this.ActionStatus == "move")
    if (this.x != this.targetPlaceX) {
     if (this.posX < this.targetPlaceX) {
       this.posX += this.speed
     }
     if (this.posX > this.targetPlaceX) {
       this.posX -= this.speed
     }
    }
    if (this.posY != this.targetPlaceY) {
     if (this.posY < this.targetPlaceY) {
       this.posY += this.speed
     }
     if (this.posY > this.targetPlaceY) {
       this.posY -= this.speed
     }
    }
     
  }
  
  
  updateStatus() {
    this.sizeX = (this.size/2)
    this.sizeY = (this.size/2)
    if(this.posX == this.targetPlaceX && this.posY == this.targetPlaceY) {
      this.ActionStatus =  "idle"
      this.action = -1
      this.targetfood = -1
      const targetX = this.targetPlaceX + (this.sizeX/2)
      const targetY = this.targetPlaceY + (this.sizeY/2)
      foods.forEach((food) => {
        if (food.status == "still" && food.x == targetX && food.y == targetY) {
          console.log("go lang")
          
        }else {
          console.log("gone na ")
          this.ActionStatus = "idle"
          this.action = 1
        }
        console.log(food.x + " & " + food.y )
         console.log(targetX + " & " + targetY )
      })
      
     
    }else {
      this.ActionStatus = "move"
      
    }
  }
  idleORmove() {
    if (this.action != 1) {
    if (this.ActionStatus == "idle") {
      this.action = Math.floor(Math.random()*this.energy)
      
      }
    }
  }
  
  hungerUpdate() {
    
    if (this.hunger < 70){
      //find food
      if (this.targetfood == -1) {
        
     this.targetfood = (Math.floor((Math.random() * foods.length )))
     }
     if (foods[this.targetfood].status == "still") {
     this.targetPlaceX = (foods[this.targetfood].x - (this.sizeX/2))
     this.targetPlaceY = (foods[this.targetfood].y - (this.sizeY/2))
     }
     
      
    }
    
  }
  
  die(){
    if (this.hunger <= 0){
      people = people.slice(index - 1)
      
    }
  }
  eat(){
    this.size += 20
    this.hunger += 20
  }
    
  
  
 
}//end of class person
