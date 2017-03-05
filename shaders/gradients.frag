uniform vec2 resolution;

void main(void) {
	vec2 pos = gl_FragCoord.xy/resolution;
	
  	gl_FragColor.r = pos.x;
  	gl_FragColor.g = 0.0;
  	gl_FragColor.b = pos.y;
  	gl_FragColor.a = 1.;
}