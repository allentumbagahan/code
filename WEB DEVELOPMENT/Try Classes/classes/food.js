class food {
  constructor(x, y) {
    this.x  = x
    this.y = y
    this.status = "still" //still or gone
    
    
  }
  draw() {
    if (this.status == "still") {
    ctx1.beginPath()
    ctx1.arc(this.x, this.y, 4, 0, 2*Math.PI)
    ctx1.stroke()
    ctx1.fillStyle = "green"
    ctx1.fill()
    } else{
      
    }
    
  }
}
