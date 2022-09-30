  c = document.getElementById('canvas')
    
ctx = c.getContext('2d')
ctx1 = c.getContext('2d')
screenWidth = document.body.offsetWidth
screenHeight = document.body.offsetHeight
const mapWidth = screenWidth
const mapHeight = screenHeight


c.width = mapWidth
c.height = mapHeight


let people = []
let foods = []







function animate () {
  ctx.clearRect(0, 0, c.width, c.height)
  requestAnimationFrame(animate)
  
  people.forEach((person, index) => {
    person.draw()
    person.findPlace()
    person.idleORmove()
    person.updateStatus()
    person.move()
    person.hungerUpdate()
   
    person.hunger -= 0.05
    if (person.hunger <= 0){
    person.status = "died"
    people.splice(index, 1)
    }
    
    foods.forEach((food, index) => {
      

      
      //if person collide to the food
      if (Math.floor(Math.hypot((food.x - (person.posX + person.sizeX/2)), (food.y - (person.posY + person.sizeY/2)))) == 0) {
       if(food.status == "still"){
       person.hungerUpdate()
       person.eat()
       }
       food.status = "gone"
       
      }
       food.draw()
       
    })
    
      
    
    
  })
  

 


}

animate()


function clickPosition(event) {
  var clickX = Math.abs(event.clientX)
  var clickY = Math.abs(event.clientY)
  
  if (c.width < c.height) {
  people.push(new person(clickX, clickY, c.width * 0.10, 5, 1));
  }
  if (c.width > c.height) {
  people.push(new person(clickX, clickY, c.height * 0.10, 5, 1));
  }
}

setInterval((addFood => {
  foods.push(new food((Math.floor(Math.random()* (c.width - 50)) + 50), (Math.floor(Math.random()*(c.width - 50)) + 50)))
  
}), 5000)

function NearFood(value, index, array) {
  return (c.width / 2) > value
}

 
