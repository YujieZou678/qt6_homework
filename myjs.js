function add(x, y) {
    return x + y
}

/*
得到一个随机int类型的数
console.log(getRandomInt(3));
Expected output: 0, 1 or 2

得到一个0-1的数
console.log(Math.random());
Expected output: a number from 0 to <1
*/
function getRandomInt(max) {
    return Math.floor(Math.random() * max)
}

/*返回的是一个匿名类对象*/
function getColorRandom() {
    let x = Math.random()
    let y = Math.random()
    let z = Math.random()
    return { x: x, y: y, z: z }
}
