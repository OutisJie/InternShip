// var start = null;
// var element = document.getElementById('actor');
// element.style.position = 'absolute';

// function step(timestamp){
//     if (!start) start = timestamp;
//     var progress = timestamp - start;
//     element.style.left = Math.min(progress / 10, 5000) + 'px';
//     if (progress < 5000){
//         window.requestAnimationFrame(step);
//     }
// }

// window.requestAnimationFrame(step);

var Engine = Matter.Engine,
    World = Matter.World,
    Bodies = Matter.Bodies;

var engine,
    world,
    stickmans = [];

var landHeight = 100;
// var render = Render.create({
//     element: document.body,
//     engine: engine

// });

function setup() {
    createCanvas(windowWidth, windowHeight);

    engine = Engine.create();
    world = engine.world;

    var tsm = new StickMan(windowWidth/2, 100,20);
    stickmans.push(tsm);

    land = new Land(0, windowHeight - landHeight/2, windowWidth, landHeight);
}

function windowResized(){
    resizeCanvas(windowWidth, windowHeight);
}

function draw() {
    background(51);
    Engine.update(engine);
    
    stickmans[0].show();
    land.show();
}

function mousePressed(){
    if (mouseX > 0 && mouseY > 0) {
        var isfull = fullscreen();
        fullscreen(!isfull);
        red
    }
}
