fill(255, 150, 100);
noStroke();
rect(0, 0, width, height);
int c = get(2, 3);
int r = c >> 16 & 0xFF;
int g = c >> 8 & 0xFF;
int b = c & 0xFF;
print("r: "+r+" g: "+g+" b: "+b);