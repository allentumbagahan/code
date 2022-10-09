var c = document.getElementById("canvas")
var x = 0
function animate () {
  console.log(x)
  x++
   console.log(c.style.transform)
  requestAnimationFrame(animate)
  
}
animate()
 
