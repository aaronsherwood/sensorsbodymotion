uniform vec2 resolution;

void main(void) {
	vec2 pos = gl_FragCoord.xy/resolution;
	
	//two ways of making a gradient from the center
	
	
	//method 1: invert any y values above the halfway point
	//i.e. .6 now become 1.-.6, so .4
	//.7 now become 1.-.7, so .3
	//as the numbers go up the inverse goes down
	
	/*
	if (pos.y >= .5)
		pos.y = 1.- pos.y;
	pos.y+=.5;
	gl_FragColor = vec4(0.,pos.y,0.,1.);
	*/
	
	
	//method 2: calculate the distance from the halfway point, take absolute value
	//invert that
	float dist = abs(.5-pos.y);
	float green = 1.-dist;
  	gl_FragColor = vec4(0.,green,0.,1.);
}
