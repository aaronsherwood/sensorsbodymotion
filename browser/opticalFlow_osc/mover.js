// The Nature of Code
// Daniel Shiffman
// http://natureofcode.com

var Mover = function(mass, x, y, c) {
  this.angle = 0;
  this.angularAcceleration = 0;
  this.angularVelocity = 0;
  this.position = createVector(x, y);
  this.velocity = createVector(1, 0);
  this.acceleration = createVector(0, 0);
  this.mass = mass;
  this.c=c;

  this.applyForces = function(force) {
    var f = p5.Vector.div(force,this.mass);
    this.acceleration.add(f);
  };

  this.update = function() {
    this.velocity.add(this.acceleration);
    this.position.add(this.velocity);

    this.checkEdges();

    this.angularAcceleration = this.acceleration.x / 50.;
    this.angularVelocity += this.angularAcceleration;
    this.angularVelocity = constrain(this.angularVelocity,-1.,.1);
    this.angle += this.angularVelocity;
    this.velocity.mult(.9);
    this.angularVelocity*=.9;
    this.acceleration.mult(0);

  };

  this.display = function() {
    noStroke();
    // strokeWeight(3);
    rectMode(CENTER);
    push();
    fill(c);
    // noFill();
    // stroke(c);
    translate(this.position.x, this.position.y);
    rotate(this.angle);

    rect(0,0, this.mass*16, this.mass*16,5,5,5,5);
    pop();
  };

  this.checkEdges = function() {
    if (this.position.x >= width) {
      this.position.x = width;
      this.velocity.x *= -1;
    } else if (this.position.x <= 0) {
      this.velocity.x *= -1;
      this.position.x = 0;
    }
    if (this.position.y >= height) {
      this.velocity.y *= -1;
      this.position.y = height;
    }
    if (this.position.y <= 0) {
      this.velocity.y *= -1;
      this.position.y = 0;
    }
  };
};
