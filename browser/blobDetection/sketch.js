// https://kylemcdonald.github.io/cv-examples/

var capture;
var w = 640;
var h = 480;

function setup() {
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
    capture.size(w, h);
    createCanvas(w, h);
    let cnv = createCanvas(w, h);
  // positions canvas 50px to the right and 100px
  // below upper left corner of the window
  cnv.position(360, 20, 'fixed');

    capture.hide();
}

var backgroundPixels;

function resetBackground() {
    backgroundPixels = undefined;
}

function copyImage(src, dst) {
    var n = src.length;
    if (!dst || dst.length != n) {
        dst = new src.constructor(n);
    }
    while (n--) {
        dst[n] = src[n];
    }
    return dst;
}

var captureMat, gray, blurred, thresholded;
var contours, hierarchy;

function cvSetup() {
    captureMat = new cv.Mat([h, w], cv.CV_8UC4);
    gray = new cv.Mat([h, w], cv.CV_8UC1);
    blurred = new cv.Mat([h, w], cv.CV_8UC1);
    thresholded = new cv.Mat([h, w], cv.CV_8UC1);
}

var ready = false;
function cvReady() {
    if(!cv || !cv.loaded) return false;
    if(ready) return true;
    cvSetup();
    ready = true;
    return true;
}

function draw() {

    var blurRadius = select('#blurRadius').value();
    blurRadius = map(blurRadius, 0, 100, 1, 20);

    var threshold = select('#threshold').value();
    threshold = map(threshold, 0, 100, 0, 255);

    var minArea = select('#minArea').value();
    minArea = map(minArea, 0, 100, 0, 200000);

    var maxArea = select('#maxArea').value();
    maxArea = map(maxArea, 0, 100, 0, 200000);

    var showThresholded = select('#showThresholded').checked();

    if (cvReady()) {
        capture.loadPixels();
        if (capture.pixels.length > 0) {
          if (!backgroundPixels) {
            backgroundPixels = copyImage(capture.pixels, backgroundPixels);
          }
          var i = 0;
          var pixels = capture.pixels;
          var total = 0;
          for (var y = 0; y < h; y++) {
            for (var x = 0; x < w; x++) {
              var rdiff = Math.abs(pixels[i + 0] - backgroundPixels[i + 0]) > threshold;
              var gdiff = Math.abs(pixels[i + 1] - backgroundPixels[i + 1]) > threshold;
              var bdiff = Math.abs(pixels[i + 2] - backgroundPixels[i + 2]) > threshold;
              var anydiff = rdiff || gdiff || bdiff;
              var output = 0;
              if (anydiff) {
                  output = 255;
                  total++;
              }
              pixels[i++] = output;
              pixels[i++] = output;
              pixels[i++] = output;
              i++; // skip alpha
            }
          }
          captureMat.data().set(pixels);

          cv.cvtColor(captureMat, gray, cv.ColorConversionCodes.COLOR_RGBA2GRAY.value, 0);
          cv.blur(gray, blurred, [blurRadius, blurRadius], [-1, -1], cv.BORDER_DEFAULT);
          cv.threshold(blurred, thresholded, threshold, 255, cv.ThresholdTypes.THRESH_BINARY.value);

          if (showThresholded) {
            var src = thresholded.data();
            var dst = capture.pixels;
            var n = src.length;
            var j = 0;
            for (var i = 0; i < n; i++) {
                dst[j++] = src[i];
                dst[j++] = src[i];
                dst[j++] = src[i];
                dst[j++] = 255;
            }
            capture.updatePixels();
          }

          contours = new cv.MatVector();
          hierarchy = new cv.Mat();
          cv.findContours(thresholded, contours, hierarchy, 3, 2, [0, 0]);
        }
    }

    image(capture, 0, 0, w, h);

    if (contours && !showThresholded) {
        noStroke();
        for (var i = 0; i < contours.size(); i++) {
            fill(0, 0, 255, 128);
            var contour = contours.get(i);
            var area = cv.contourArea(contour, false);

            if (area>minArea && area<maxArea){
              beginShape();
              var k = 0;
              for (var j = 0; j < contour.total(); j++) {
                  var x = contour.get_int_at(k++);
                  var y = contour.get_int_at(k++);
                  vertex(x, y);
              }
              endShape(CLOSE);

              noFill();
              stroke(255, 255, 255)
              var box = cv.boundingRect(contour);
              var center = createVector(box.x + box.width/2, box.y + box.height/2);
              ellipse(center.x, center.y, 10, 10);

              rect(box.x, box.y, box.width, box.height);
          }

            // these aren't working right now:
            // https://github.com/ucisysarch/opencvjs/issues/30
//            var minAreaRect = cv.minAreaRect(contour);
//            var minAreaEllipse = cv.ellipse1(contour);
//            var fitEllipse = cv.fitEllipse(contour);
        }
    }
}
