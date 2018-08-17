function Land(x, y, w, h){
    var options = {
        restitution: 1,
        friction: 0,
        isStatic: true,
    };

    this.body = Bodies.rectangle(x, y, 2*w, h, options);
    this.w = w;
    this.h = h;
    World.add(world, this.body);
}

Land.prototype.show = function(){
    noStroke();
    
    fill('rgba(0, 255, 0, 0.25)');
    var pos = this.body.position;
    push();
    translate(pos.x, pos.y);
    rect(0, 0 - this.h/2, this.w, this.h);
    pop();
}