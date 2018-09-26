PGraphics pg;
void setup(){
 size(640,640); 
 pg = createGraphics(640,640);
 pg.beginDraw();
 pg.background(0);
 pg.endDraw();
}

void draw(){
 pg.loadPixels();
 for (int i=0;i<pg.pixels.length;i++){
  pg.pixels[i]=color(random(255)); 
 }
 pg.updatePixels();
 noStroke();
 fill(255);
 ellipse(mouseX,mouseY,10,10);
 blend(pg,0,0,width,height,0,0,width,height,DARKEST);
}