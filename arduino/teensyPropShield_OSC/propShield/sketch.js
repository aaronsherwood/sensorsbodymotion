var w = 600;
var h = 500;
var yaw = 0.0;
var pitch = 0.0;
var roll = 0.0;

function setup() {
  var cnv = createCanvas(w, h, WEBGL);
  var x = (windowWidth - width) / 2;
  var y = (windowHeight - height) / 2;
  cnv.position(x, y);

  socket.on('message', function(msg) {
    console.log(msg);
    if (msg != null) {
      var list = split(trim(msg), ",");
      if (list.length >= 3 && list[0] == "/ctrl") {
        switch (list[1]) {
          case "heading":
            yaw = float(list[2]) * 360;
            break;
          case "pitch":
            pitch = float(list[2]) * 180 - 90;
            break;
          case "roll":
            roll = float(list[2]) * 360 - 180;
            break;
        }
      }
    }
  });
}

function draw() {
  background(255); // set background to white

  push();

  var c1 = cos(radians(roll));
  var s1 = sin(radians(roll));
  var c2 = cos(radians(-pitch));
  var s2 = sin(radians(-pitch));
  var c3 = cos(radians(yaw));
  var s3 = sin(radians(yaw));
  applyMatrix(c2 * c3, s1 * s3 + c1 * c3 * s2, c3 * s1 * s2 - c1 * s3, 0,
    -s2, c1 * c2, c2 * s1, 0,
    c2 * s3, c1 * s2 * s3 - c3 * s1, c1 * c3 + s1 * s2 * s3, 0,
    0, 0, 0, 1);

  drawPropShield();

  pop();
}

function drawPropShield() {
  // 3D art by Benjamin Rheinland
  stroke(0); // black outline
  fill(0, 128, 0); // fill color PCB green
  box(190, 6, 70); // PCB base shape

  fill(255, 215, 0); // gold color
  noStroke();

  //draw 14 contacts on Y- side
  translate(65, 0, 30);
  for (var i = 0; i < 14; i++) {
    sphere(4.5); // draw gold contacts
    translate(-10, 0, 0); // set new position
  }

  //draw 14 contacts on Y+ side
  translate(10, 0, -60);
  for (var i = 0; i < 14; i++) {
    sphere(4.5); // draw gold contacts
    translate(10, 0, 0); // set position
  }

  //draw 5 contacts on X+ side (DAC, 3v3, gnd)
  translate(-10, 0, 10);
  for (var i = 0; i < 5; i++) {
    sphere(4.5);
    translate(0, 0, 10);
  }

  //draw 4 contacts on X+ side (G C D 5)
  translate(25, 0, -15);
  for (var i = 0; i < 4; i++) {
    sphere(4.5);
    translate(0, 0, -10);
  }

  //draw 4 contacts on X- side (5V - + GND)
  translate(-180, 0, 10);
  for (var i = 0; i < 4; i++) {
    sphere(4.5);
    translate(0, 0, 10);
  }

  //draw audio amp IC
  stroke(128);
  fill(24); //Epoxy color
  translate(30, -6, -25);
  box(13, 6, 13);

  //draw pressure sensor IC
  stroke(64);
  translate(32, 0, 0);
  fill(192);
  box(10, 6, 18);

  //draw gyroscope IC
  stroke(128);
  translate(27, 0, 0);
  fill(24);
  box(16, 6, 16);

  //draw flash memory IC
  translate(40, 0, -15);
  box(20, 6, 20);

  //draw accelerometer/magnetometer IC
  translate(-5, 0, 25);
  box(12, 6, 12);

  //draw 5V level shifter ICs
  translate(42.5, 2, 0);
  box(6, 4, 8);
  translate(0, 0, -20);
  box(6, 4, 8);
}
