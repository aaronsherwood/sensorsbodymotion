var w = 640;
var h = 640;
var threshold = 25;

var temps = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];


function setup() {
  var cnv = createCanvas(w, h);
  var x = (windowWidth - width) / 2;
  var y = (windowHeight - height) / 2;
  cnv.position(x, y);

  socket.on('message', function(msg) {
    if (msg != null) {
      // generate an array of strings that contains each of the comma
      // separated values
      var list = split(trim(msg), ",");
      var average = 0;
      // for each of the 64 values, map the temperatures between 20C and 40C
      // to the blue through red portion of the color space
      for (var q = 0; q < 64; q++) {
        // lets keep track of the overall heat too
        average+=float(list[q]);

        // map each square from heat to HSB
        temps[q] = map(float(list[q]), 20, 40, 240, 360);

        // send osc
        // for each square send a 0 unless it's over the threshold
        var num=0;
        if (list[q] > threshold)
          num = 1
        var name = "square"+q;
        sendOsc("/ctrl", name, num);
      }

      // get the average and put into the range of 0 - 1
      average/=64;
      average = constrain( map(average, 25, 30, 0, 1), 0, 1);
      sendOsc("/ctrl", "average", average);
    }

  });
  noStroke();
  colorMode(HSB, 360, 100, 100);
  textAlign(CENTER);
}

function draw() {
  background(0); // Clear the screen with a black background

  // Prepare variables needed to draw our heatmap
  var x = 0;
  var y = 0;
  var i = 0;

  // each GridEYE pixel will be represented by a 80px square:
  // because 80 x 8 = 640, we draw squares until our y location
  // is 640
  while (y < 640) {
    // for each increment in the y direction, draw 8 boxes in the
    // x direction, creating a 64 pixel matrix
    while (x < 640) {
      // before drawing each pixel, set our paintcan color to the
      // appropriate mapped color value
      fill(temps[i], 100, 100);
      rect(x, y, 80, 80);
      fill(0,0, 100);
      // draw the numbers on screen cetner in the box (+40)
      text(i, x+40, y+40);
      x = x + 80;
      i++;
    }
    y = y + 80;
    x = 0;
  }

}
