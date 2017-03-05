/*
 taken from the tutorial here, by Inigo Quilez:
 https://www.youtube.com/watch?v=0ifChJ0nJfM
*/

uniform vec2 resolution;

void main(void) {
	//fragment position
	vec2 pos = gl_FragCoord.xy/resolution;
	//center of drawing coords
	float xPos = .34;
	float yPos = .7;
	//distance of the fragment to the center of our drawing
	vec2 loc = pos - vec2(xPos,yPos);
	//base color, mix between orange and yello, and take square root of fragment y position
	//to get sunset effect, square root pushes down the orange
	vec3 col = mix(vec3(1.,.3,.1), vec3(1.,.8,.1),sqrt(pos.y));
	//radius from which we're drawing
	//we start of with a base radius of .2
	//using cosine multiplied by .1, we will get distances between .3 and .1 (.2 +- .1)
	//atan gives points on a circle at a freq of 10
	//then we droop the leaves and rotate a little
	float radius = .2 + .1*(cos(atan(loc.y,loc.x)*10. + loc.x*20. +1.));
	//smooth step the color to get black when it is below radius, and our color when above
	//use the length of the vector of our current fragment to the center of the drawing to decide
	col *= smoothstep(radius,radius+.01,length(loc));
	
	//reset radius for a thin trunk
	radius = 0.015;
	//put ripples in the trunk using cosine on the y axis
	radius += .002*cos(loc.y*100.);
	//build a ground with an exponential curve
	radius += exp(-70.*pos.y);
	//if the fragment position is less the the center of our drawing, draw the trunk
	if (pos.y<yPos)
		//curve the trunk with sine
		col *= smoothstep(radius,radius+.002,abs(loc.x-.25*sin(2.*loc.y)));
	//output our color
  	gl_FragColor= vec4(col, 1.0);
}
