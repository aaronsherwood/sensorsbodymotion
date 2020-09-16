
var w = 640;
var h = 480;

function setup() {
    createCanvas(w, h);
}

function draw() {
    // send OSC
    sendOsc('/ctrl', 'fromProcessing', sin(frameCount*.01)+3);
}
