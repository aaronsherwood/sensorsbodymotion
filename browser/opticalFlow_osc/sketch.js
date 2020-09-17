// adapted from https://kylemcdonald.github.io/cv-examples/

var capture;
var previousPixels;
var flow;
var w = 640;
var h = 480;
var step = 8;
var avgOpticalFlow;
var smoothedAvgOpticalFlow;
var movers = [];
var numMovers = 1;

function setup() {
    createCanvas(w, h);
    capture = createCapture({
        audio: false,
        video: {
            width: w,
            height: h
        }
    }, function() {
        console.log('capture ready.')
    });
    capture.elt.setAttribute('playsinline', '');
    capture.hide();
    flow = new FlowCalculator(step);
    avgOpticalFlow = createVector(0,0);
    smoothedAvgOpticalFlow = createVector(0,0);

    for (var i = 0; i < numMovers; i++) {
      c = color(255, 100);
      var s = 3; //random(1, 4);
      var x = random(width);
      var y = random(height);
      movers[i] = new Mover(s, x, y, c);
    }
}

function copyImage(src, dst) {
    var n = src.length;
    if (!dst || dst.length != n) dst = new src.constructor(n);
    while (n--) dst[n] = src[n];
    return dst;
}

function same(a1, a2, stride, n) {
    for (var i = 0; i < n; i += stride) {
        if (a1[i] != a2[i]) {
            return false;
        }
    }
    return true;
}

function draw() {
  capture.loadPixels();
      if (capture.pixels.length > 0) {
          if (previousPixels) {
              // cheap way to ignore duplicate frames
              if (same(previousPixels, capture.pixels, 4, width)) {
                  return;
              }
              flow.calculate(previousPixels, capture.pixels, capture.width, capture.height);
          }
          previousPixels = copyImage(capture.pixels, previousPixels);
          image(capture, 0, 0, w, h);

          if (flow.flow && flow.flow.u != 0 && flow.flow.v != 0) {
              strokeWeight(2);

              flow.flow.zones.forEach(function(zone) {
                  stroke(map(zone.u, -step, +step, 0, 255),
                      map(zone.v, -step, +step, 0, 255), 128);
                  line(zone.x, zone.y, zone.x + zone.u, zone.y + zone.v);
              })
              // do smoothing \\

              // create a vecot first with the average optical flow
              avgOpticalFlow = createVector(flow.flow.u, flow.flow.v);
              // copy our current smoothed value into a new vector called smoothing
              var smoothing = avgOpticalFlow.copy();

              // remember, our smoothing algorithm is take where we are currently and...
              // ADD our destination minus where we are currently times a scalar
              // i.e. smoothedValue += (destination - smoothedValue) * .1

              // this is the first part: subtract where we are from our destination
              // (remember, we copied the new average flow into the smoothing variable)
              smoothing.sub(smoothedAvgOpticalFlow);
              // then multiply that by a scalar
              smoothing.mult(.1);
              // then add that to where we are currently
              smoothedAvgOpticalFlow.add(smoothing);

              for (var i = 0; i < numMovers; i++) {
                var arrayLoc = flow.getArrayLoc(movers[i].position.x, movers[i].position.y, w);
                var zone = flow.flow.zones[arrayLoc];
                // console.log(flow.flow.zones[arrayLoc]);
                var force;
                if (zone) {
                  force = createVector(zone.u, zone.v);
                  movers[i].applyForces(force);
                }
                movers[i].update();

                movers[i].display();
            }

              // we can get the the direction horz, vert, and the size of the line (via mag())
              console.log("x: "+avgOpticalFlow.x + "\ny: "+ avgOpticalFlow.y + "\nlength: " + smoothedAvgOpticalFlow.mag());

              // send OSC

              sendOsc('/ctrl', 'optflowX', smoothedAvgOpticalFlow.x);
              sendOsc('/ctrl', 'optflowY', smoothedAvgOpticalFlow.y);
              sendOsc('/ctrl', 'optflowLength', smoothedAvgOpticalFlow.mag());

              var moverX = map(movers[0].position.x,0,w,0.,1.);
              sendOsc('/ctrl', 'moverX', moverX);
              var moverY = map(movers[0].position.y,0,h,0.,1.);
              sendOsc('/ctrl', 'moverY', moverY);

              // draw the average flow
              strokeWeight(5);
              stroke(255,0,0);
              // multipling by 10 in order to see on screen better
              line(width/2, height/2, width/2+smoothedAvgOpticalFlow.x*10, height/2+smoothedAvgOpticalFlow.y*10);
          }
      }
}
