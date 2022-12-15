c = document.querySelector('canvas')
console.log('start')
var x = 10;
var y = 10;
var h = "world!"
var grave = `hello ${h}`
function allen () {
x++
y++
console.log(c.style.transform)
c.style.transform = `translate3d( ${x}px, ${y}px, 0)` ; // use backtick character "``"
console.log(grave)
}
