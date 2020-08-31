// modified from https://kylemcdonald.github.io/cv-examples/

var capture;
var previousPixels;
var w = 640;
var h = 480;
var section1_gain = 0.;
var section1_destination = 0;
var section2_gain = 0.;
var section2_destination = 0;

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
    capture.hide();
}

function copyImage(src, dst) {
    var n = src.length;
    if (!dst || dst.length != n) dst = new src.constructor(n);
    while (n--) dst[n] = src[n];
    return dst;
}

function draw() {
    capture.loadPixels();
    var total = 0;
		var section1 = 0;
    var section2 = 0;
    if (capture.pixels.length > 0) { // don't forget this!
        if (!previousPixels) {
            previousPixels = copyImage(capture.pixels, previousPixels);
        } else {
            var w = capture.width,
                h = capture.height;
            var i = 0;
            var pixels = capture.pixels;
						//threshold slider is 100 scale
						//this puts it to 255 scale
            var thresholdAmount = select('#thresholdAmount').value() * 255. / 100.;
            thresholdAmount *= 3; // 3 for r, g, b
            for (var y = 0; y < h; y++) {
                for (var x = 0; x < w; x++) {
                    // calculate the differences
                    var rdiff = Math.abs(pixels[i + 0] - previousPixels[i + 0]);
                    var gdiff = Math.abs(pixels[i + 1] - previousPixels[i + 1]);
                    var bdiff = Math.abs(pixels[i + 2] - previousPixels[i + 2]);
                    // copy the current pixels to previousPixels
                    previousPixels[i + 0] = pixels[i + 0];
                    previousPixels[i + 1] = pixels[i + 1];
                    previousPixels[i + 2] = pixels[i + 2];
                    var diffs = rdiff + gdiff + bdiff;
                    var output = 0;
                    if (diffs > thresholdAmount) {
                        output = 255;
                        total += diffs;
                        // section 1
												if (x<100){
													section1 += diffs;
												}
                        // section 2
                        if (x>width-100){
													section2 += diffs;
												}
                    }
                    //thresholded amounts
                    pixels[i++] = output;
                    pixels[i++] = output;
                    pixels[i++] = output;
                    // comment above and uncomment below to see the original differenced amount
                    // pixels[i++] = rdiff;
                    // pixels[i++] = gdiff;
                    // pixels[i++] = bdiff;
                    i++; // skip alpha
                }
            }
        }
    }

    // set each section's threshold from the sliders
    var threshold1Amount = select('#threshold1Amount').value() * 10000;
    var threshold2Amount = select('#threshold2Amount').value() * 10000;

    // when smoothing down go slower
    var sec1changeRate = .1;
		if (section1>threshold1Amount){
      // section 1 gain goes to 1.1
			section1_destination = 1.1;
      // when smotthing up go faster
      sec1changeRate = .99;
		} else {
			section1_destination = 0;
		}

    // smoothing alogrithm: smoothedValue += (dest-current)*scalar
		section1_gain += (section1_destination-section1_gain)*sec1changeRate;

    var sec2changeRate = .1;
    if (section2>threshold2Amount){
      // section 2 gain goes just to 1
			section2_destination = 1;
      sec2changeRate = .99;
		} else {
			section2_destination = 0;
		}

		section2_gain += (section2_destination-section2_gain)*sec2changeRate;

    // send OSC
    sendOsc('/ctrl', 'section1_gain', section1_gain);
    sendOsc('/ctrl', 'section2_gain', section2_gain);

    // show on screen only 2 decimal places
    var sec1num = (Math.round(section1_gain* 100) / 100).toFixed(2);
    var sec2num = (Math.round(section2_gain* 100) / 100).toFixed(2);

    // need this because sometimes the frames are repeated
    if (total > 0) {
        capture.updatePixels();
        // un comment to flip video image (note: the sections will also be reversed)
				// push();
				// translate(width,0); // move to far corner
  			// scale(-1.0,1.0);    // flip x-axis backwards
        image(capture, 0, 0, 640, 480);
				// pop();

        // set the HTML text
        select('#motion').elt.innerText = total +"\nSection1: "+ section1+ "\n Section1 Gain: "+sec1num + "\nSection2: "+ section2+ "\n Section2 Gain: "+sec2num;
    }

    // draw rectangles for the sections
    noStroke();

		fill(255,0,0, 255*sec1num);
		rect(0,0,100, height);

    fill(255,0,0, 255*sec2num);
		rect(width-100,0,width, height);
}
