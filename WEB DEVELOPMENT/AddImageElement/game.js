var c = document.getElementById('canvas')
var ctx = c.getContext('2d')
let boxes = []
class boxWithImage {
  constructor (x, y, w, h, source) {
    this.x = x
    this.y = y
    this.width = w
    this.height = h
    this.image = new Image()
    this.image.src = source
  }
  draw() {
    ctx.drawImage(this.image, this.x, this.y, this.width, this.height)
  }
}

boxes.push(new boxWithImage(0, 0, 50, 50, './images/images.png'))

function animate () {
boxes.forEach((boxWithImage) => {
  boxWithImage.draw()
})
window.requestAnimationFrame(animate)
console.log(boxes)
}

animate()
