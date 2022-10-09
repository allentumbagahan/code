// set canvas
c = document.getElementById('canvas');
ctx = c.getContext("2d");

var bodyH = document.body.clientHeight
var bodyW = document.body.clientWidth

c.heigth = bodyH ;
c.width = bodyW ;


console.log(c.width)
console.log(c.heigth)



class Player {
    constructor (x, y, color, sizeX, sizeY) {
        this.x = x;
        this.y = y;
        this.color = color ;
        this.sizeX = sizeX;
        this.sizeY = sizeY;
        }
        draw () {
            ctx.beginPath();
            ctx.rect(this.x, this.y, this.sizeX, this.sizeY);
            ctx.stroke();
        }
        update () {

        }
}

const player = new Player(50, 50, 'red', 50, 50)

console.log(player)
player.draw()


