let people = []

class Person {
  constructor(x, y){
    this.posX = x
    this.posY = y
  }
  
  Try (data, index) { 
    /*data is the value of array and index is the position number*/
   
    people[index].posX += 1
    people[index].posY += 1
    
  }
}

var person = new Person(1, 2)
people.push(person)
var person = new Person(3, 4)
people.push(person)

console.log(people)


function animate () {
  
console.log(people)
people.forEach(person.Try)
requestAnimationFrame(animate)
}

animate()
