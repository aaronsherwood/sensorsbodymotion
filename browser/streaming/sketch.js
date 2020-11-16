// this sketch shows how to use texture coordinates to create a fly's eye mosaic effect


// the shader variable
let streamShader;
let flvPlayer;
let ctx;

function preload(){
  // load the shader
  streamShader = loadShader('effect.vert', 'effect.frag');
}

function setup() {
  // shaders require WEBGL mode to work
  createCanvas(windowWidth, windowHeight, WEBGL);
  setupStream();
  noStroke();
}

function draw() {
  // only do something if receiving the stream
  if (flvPlayer.currentTime>0.0){
    // get the stream image data
    let stream = ctx.getImageData(0, 0, windowWidth, windowHeight);
    // send to shader
    shader(streamShader);
    streamShader.setUniform('tex0', stream);
    streamShader.setUniform('resolution', [width, height]);
    streamShader.setUniform('amount', map(mouseX,0,width,0,1));
    streamShader.setUniform('power', map(mouseY,0,height,0,10));
    // rect gives us some geometry on the screen
    rect(0,0,width, height);
  }
}

function setupStream(){
  // get the video element from the HTML
  let videoElement = document.getElementById('videoElement');
  // get the second canvas from the HTML, we will draw the stream into it so we can use it as an image for a shader
  let canvas = document.getElementById('canvas');
  ctx = canvas.getContext('2d');
  canvas.width = width;
  canvas.height = height;
  // when the video element starts to play call the draw function (just below) to draw into canvas
  videoElement.addEventListener('play', function(){
      draw(this,ctx,width, height);
  },false);

  function draw(v,c,w,h) {
    c.drawImage(v,0,0,w,h);
    // keep calling draw on a timeout
    setTimeout(draw,20,v,c,w,h);
  }

  // start the actual stream
  if (flvjs.isSupported()) {
    flvPlayer = flvjs.createPlayer({
      type: 'flv',
      ////////////////////THIS IS THE IMPORTANT PLACE TO CHANGE\\\\\\\\\\\\\\\\\\\\\\\\\\
      // put your ngrok url here (without the port)
      // example: 'http://fdb6505ee720.ngrok.io/live/STREAM_NAME.flv'
      url: 'http://localhost:7000/live/STREAM_NAME.flv'
    });
    flvPlayer.attachMediaElement(videoElement);
    flvPlayer.load();
    flvPlayer.play();
  }
}

function windowResized(){
  resizeCanvas(windowWidth, windowHeight);
}
