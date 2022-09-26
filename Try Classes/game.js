  c = document.getElementById('canvas')
ctx = c.getContext('2d')

mapWidth = document.body.offsetWidth
mapHeight = document.body.offsetHeight

c.width = mapWidth
c.height = mapHeight

let people = []
let foods = []

class person {
  constructor(x, y, sizeX, sizeY, energy, speed){
    this.posX = x
    this.posY = y
    this.sizeX = sizeX
    this.sizeY = sizeY
    this.targetPlaceX = x
    this.targetPlaceY = y
    this.action = 0
    this.ActionStatus = "idle" //idle, move
    this.energy = (80 - (energy * 5))
    this.speed = speed
    this.hunger = 100
    this.targetfood = 0
    
    
  }
  
    
  
  
  draw () {
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
  findPlace() {
    
    if (this.ActionStatus == "idle") {
    if (this.action == 1) {
      this.targetPlaceX = (Math.floor(Math.random()*c.width - 25) + 25)
      this.targetPlaceY = (Math.floor(Math.random()*c.height - 25) + 25)
    }
      }
      
    }
    
  move () {
    if (this.ActionStatus == "move")
    if (this.x != this.targetPlaceX) {
     if (this.posX < this.targetPlaceX) {
       this.posX += 1
     }
     if (this.posX > this.targetPlaceX) {
       this.posX -= 1
     }
    }
    if (this.posY != this.targetPlaceY) {
     if (this.posY < this.targetPlaceY) {
       this.posY += 1
     }
     if (this.posY > this.targetPlaceY) {
       this.posY -= 1
     }
    }
     
  }
  
  
  updateStatus() {
    if(this.posX == this.targetPlaceX && this.posY == this.targetPlaceY) {
      this.ActionStatus =  "idle"
      this.action = -1
      this.targetfood = -1
     
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
    
  
  
 
}//end of class person

class food {
  constructor(x, y) {
    this.x  = x
    this.y = y
  }
  draw() {
    ctx.beginPath()
    ctx.arc(this.x, this.y, 4, 0, 2*Math.PI)
    ctx.stroke()
    ctx.fillStyle = "green"
    ctx.fill()
  }
}




function animate () {
  ctx.clearRect(0, 0, c.width, c.height)
  requestAnimationFrame(animate)
  foods.forEach((food) => {
    food.draw()
  })
  people.forEach((person, index) => {
    person.draw()
    person.findPlace()
    person.idleORmove()
    person.updateStatus()
    person.move()
    person.hungerUpdate()
   
    person.hunger -= 0.1
    if (person.hunger <= 0){
    delete people[index]
    }
    
      
    
    
  })
  

 


}

animate()


function clickPosition(event) {
  var clickX = Math.abs(event.clientX)
  var clickY = Math.abs(event.clientY)
  
  
  people.push(new person(clickX, clickY, c.width * 0.05, c.width * 0.05, 5, 5));
  
  
}

setInterval((addFood => {
  foods.push(new food((Math.floor(Math.random()* (c.width - 50)) + 50), (Math.floor(Math.random()*(c.width - 50)) + 50)))
  
}), 5000)

function NearFood(value, index, array) {
  return (c.width / 2) > value
}

 
