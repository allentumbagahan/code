$ = document.getElementById('canvas')
ctx = $.getContext('2d')
$.height = (document.documentElement.clientHeight - 10)
$.width = (document.documentElement.clientWidth - 10)


function NewSizeScreen () {
  $.height = (document.documentElement.clientHeight - 10)
  $.width = (document.documentElement.clientWidth - 10)
  drawSlots()

}


var aquarium = []




function animate () {
  ctx.clearRect(0,0, $.width, $.height)
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
   putItem(itemHeld, clickPosX, clickPosY)
}

drawSlots()

