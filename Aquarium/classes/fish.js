var clickPosX, clickPosY = 0;

elem = document.createElement("img")
elem.setAttribute("src", "./img/fish.png")
elem.setAttribute("id", "image")
console.log(elem)


class fish {
  constructor(x, y, sizeArea, clickPosX, clickPosY) {
    this.x = x
    this.y = y
    this.sizeX = (sizeArea/2)
    this.sizeY = (sizeArea/2)
    this.centerX = (x + (this.sizeX/2))
    this.centerY = (y + (this.sizeY/2))
    this.angle = 0
  }
  draw() {
    ctx.save()
    console.log(this.angle)
    ctx.translate(this.x,this.y)
    ctx.rotate(this.angle*Math.PI/180) //degree*Math.Pi/180
    ctx.fillStyle = "transparent"
    ctx.fillRect(0,0, this.sizeX, this.sizeY)
    ctx.drawImage(elem, 0 - this.sizeX/2,0 - this.sizeY/2, this.sizeX, this.sizeY)
    ctx.restore()

  }
  rotate() {
    
    this.angle = Math.atan2((clickPosY - this.centerY), (clickPosX - this.centerX)) * (180/Math.PI)
    console. log(this.angle)
  }
}

