c = document.getElementById('canvas')
ctx = c.getContext('2d')
c.height = (document.documentElement.clientHeight - 10)
c.width = (document.documentElement.clientWidth - 10)
console.log(document.documentElement.clientWidth)

function NewSizeScreen () {
  c.height = (document.documentElement.clientHeight - 10)
  c.width = (document.documentElement.clientWidth - 10)
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
   if (document.documentElement.clientWidth > document.documentElement.clientHeight) {
   aquarium.push(new fish(clickPosX, clickPosY, 0.035*document.documentElement.clientWidth))
   }else {
    aquarium.push(new fish(clickPosX, clickPosY, 0.035*document.documentElement.clientHeight))
   }
}
