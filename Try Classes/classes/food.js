class food {
  constructor(x, y) {
    this.x  = x
    this.y = y
    this.status = "still" //still or gone
    this.image = new Image()
    
  }
  draw() {
    if (this.status == "still") {
    ctx1.beginPath()
    ctx1.arc(this.x, this.y, 4, 0, 2*Math.PI)
    ctx1.stroke()
    ctx1.fillStyle = "green"
    ctx1.fill()
    image1.document.createElement('img')
    image1.setAttribute('src', './src/img/images.png')
    c.appendChild(image1)
    ctx1.drawImage(imageSrc, this.x, this.y, 50, 50)
    } else{
      
    }
    
  }
}
