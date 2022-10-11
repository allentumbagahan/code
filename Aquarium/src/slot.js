// use $ as canvas element
// use ctx for canvas 2d context
var itemHeld = 1

function drawSlots () {
    document.getElementById("slots").style.transform = `translate3d( 10px, ${0 - $.height}px, 0)` ;
    console.log($.height)
    }

function putItem (num, x, y) {
        switch (num) {
            case 1 :
            aquarium.push(new fish(x, y, 0.035*(document.documentElement.clientWidth + (2880 - document.documentElement.clientWidth)), elem1, elem2, elem3, elem4))
            break
            case 2 :
            aquarium.push(new fish(x, y, 0.035*(document.documentElement.clientWidth + (2880 - document.documentElement.clientWidth)), elem5, elem6, elem7, elem8))
            break
        }
}

function getItem1 () {
    itemHeld = 1    
}   

function getItem2 () {
    itemHeld = 2    
}   
