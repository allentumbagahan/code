
c = document.getElementById("canvas")
ctx = c.getContext('2d')

var gravity = 9.8
let boxes = []


c.height = (document.documentElement.clientHeight - 4)
c.width = (document.documentElement.clientWidth - 4)

function velocityCal (velocityInitial, time) {
  return (velocityInitial * gravity * time)
}




function animate () {
  ctx.clearRect(0, 0, c.width, c.height)
  boxes.forEach((box) => {
    box.draw()
    
    
    box.update()
    
  })
  requestAnimationFrame(animate)
}


animate()


function addBox(event){
  boxes.push(new box(event.clientX, event.clientY, 50))
  console.log(boxes)
  
}
