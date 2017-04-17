/* --------------------------------------------------------------------------
 * SimpleOpenNI DepthImage Test
 * --------------------------------------------------------------------------
 * Processing Wrapper for the OpenNI/Kinect 2 library
 * http://code.google.com/p/simple-openni
 * --------------------------------------------------------------------------
 * prog:  Max Rheiner / Interaction Design / Zhdk / http://iad.zhdk.ch/
 * date:  12/12/2012 (m/d/y)
 * ----------------------------------------------------------------------------
 */

import SimpleOpenNI.*;


SimpleOpenNI  context;
int [] depthValues;
PImage depthThresholded;
PGraphics    canvas;
int minDistance=200;
int maxDistance=1000;

void setup()
{
  size(640, 480,P3D);
  context = new SimpleOpenNI(this);
  if (context.isInit() == false)
  {
    println("Can't init SimpleOpenNI, maybe the camera is not connected!"); 
    exit();
    return;
  }

  // mirror is by default enabled
  context.setMirror(true);

  // enable depthMap generation 
  context.enableDepth();

  // enable rgb generation
  context.enableRGB();
  
  //match up the depth with color
//  context.alternativeViewPointDepthToImage();
  
  depthThresholded = createImage(640, 480, RGB);
  setupSyphonServer("Depth");
  prepareExitHandler();
  canvas = createGraphics(640, 480, P3D);
}

void draw()
{
  // update the cam
  context.update();
  canvas.beginDraw();
  canvas.background(0, 0, 0);
  
  depthValues=context.depthMap();
  if(mousePressed){
    int distance= depthValues[mouseX+(mouseY*640)];
   println(mouseX+ " " +mouseY+" "+distance); 
  }
  //*******change depthImage to rgbImage here*******
  depthThresholded=context.depthImage();
  depthThresholded.loadPixels();
  int maxDepth=0;
  for(int i=0;i<depthValues.length;i++){
    if (depthValues[i]>minDistance && depthValues[i]<maxDistance){
      
    } else{
      depthThresholded.pixels[i]=color(0);
    }
      if(depthValues[i]>maxDepth)
        maxDepth=depthValues[i];
  }

  depthThresholded.updatePixels();
  // draw depthImageMap
  canvas.image(depthThresholded, 0, 0);

  // draw irImageMap
  canvas.image(context.depthImage(), context.depthWidth() + 10, 0);
  canvas.endDraw();
  image(canvas,0,0);
  server.sendImage(canvas);
}

