function StickMan(x, y, r){
    var options = {
        restitution: 1,
        friction: 0
    }
    this.body = Bodies.circle(x, y, r, options);
    this.r = r;
    World.add(world, this.body); 
}

StickMan.prototype.show = function(){
    fill(255);
    stroke(255);
    var pos = this.body.position;
    push();
    translate(pos.x, pos.y);
    ellipse(10, 0, this.r * 2);
    pop();
}