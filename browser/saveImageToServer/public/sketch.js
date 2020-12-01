var video;
var w = 640;
var h = 480;
var savedImage;

function setup(){
  createCanvas(w*2, 480);
  video = createCapture(VIDEO);
  video.size(w, h);
  video.hide();
}

function draw(){
  background(0);
    image(video, 0, 0);
    text("Click to save webcam image", 20, 20);
    if (savedImage){
      push();
      translate(640, 0);
      image(savedImage, 0, 0);
      text("Saved image loaded from server", 20, 20);
      pop();
    }
}

function mousePressed(){
  // send the image to the server
  video.loadPixels();
  var imageData = video.canvas.toDataURL('image/png'); // produces a base64 image string
  var formData = new FormData();
  formData.append('photo', imageData);
  $.ajax({
      type: "POST",
      url: "/upload",
      enctype: 'multipart/form-data',
      data: formData,
      processData: false,
      contentType: false,
      success: function () {
          console.log("image sent.");
      }
  }).done(function ( data ) {
    console.log("file name: " + data.filename);
    savedImage = loadImage(data.filename);
  });
  // have to recreate the video element
  video = createCapture(VIDEO);
  video.hide();
}
