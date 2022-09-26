c = document.getElementById('canvas')
ctx = c.getContext('2d')

mapWidth = document.body.offsetWidth
mapHeight = document.body.offsetHeight

c.width = mapWidth
c.height = mapHeight

let people = []

class person {
  constructor(x, y, sizeX, sizeY){
    this.posX = x
    this.posY = y
    this.sizeX = sizeX
    this.sizeY = sizeY
    this.targetPlaceX = x
    this.targetPlaceY = y
    this.action = 0
    this.ActionStatus = "idle" //idle, move
    
    
    
  }
  
    
  
  
  draw () {
    ctx.beginPath()
    ctx.rect(this.posX, this.posY, this.sizeX, this.sizeY)
    ctx.stroke()
    
    if (this.updateStatus == "move"){
      ctx.fillStyle = "red"
      ctx.fill()
      
    } else {
      ctx.fillStyle = "black"
      ctx.fill()
      this.idleORmove()
      
    }
    
    
    
    
  }
  findPlace() {
    
    if (this.ActionStatus == "idle") {
    if (this.action = 3)
      this.targetPlaceX = (Math.floor(Math.random()*c.width - 25) + 25)
      this.targetPlaceY = (Math.floor(Math.random()*c.height - 25) + 25)
      
      }
      console.log(this.ActionStatus)
      console.log(this.targetPlaceY)
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
      this.action = 0
     
    }else {
      this.ActionStatus = "move"
      
    }
  }
  idleORmove() {
    if (this.action != 3) {
    if (this.ActionStatus == "idle") {
      this.action = Math.random()*20
      }
    }
  }
  
    
  
  
 
}





function animate () {
  ctx.clearRect(0, 0, c.width, c.height)
  requestAnimationFrame(animate)
  people.forEach((person) => {
    person.draw()
    person.findPlace()
    person.idleORmove()
    person.updateStatus()
    person.move()
    
    
    
  })
  
console.log(people);
 


}

animate()


function clickPosition(event) {
  var clickX = Math.abs(event.clientX)
  var clickY = Math.abs(event.clientY)
  console.log(clickX);
  console.log(clickY)
  
  people.push(new person(clickX, clickY, c.width * 0.05, c.width * 0.05));
  
  console.log(people)
}
  
