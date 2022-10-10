c = document.getElementById('canvas')
ctx = c.getContext('2d')
c.height = (document.documentElement.clientHeight - 10)
c.width = (document.documentElement.clientWidth - 10)

function NewSizeScreen () {
  c.height = (document.documentElement.clientHeight - 4)
  c.width = (document.documentElement.clientWidth - 4)
}


var aquarium = []




function animate () {
  ctx.clearRect(0,0, c.width, c.height)
  aquarium.forEach((fish) => {
    fish.rotate()
    fish.draw()
    
    
    
  })
  requestAnimationFrame(animate)
}
animate()


function clickFunction(event) {
   clickPosX = event.clientX
   clickPosY = event.clientY
   aquarium.push(new fish(clickPosX, clickPosY, 100))
}
