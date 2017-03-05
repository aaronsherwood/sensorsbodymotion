uniform vec2 resolution;

void main(void) {
	vec2 pos = gl_FragCoord.xy/resolution;
	pos.y-=.5;
	
  	float dist = abs(pos.y)*20.;
  	
  	gl_FragColor = vec4(.6/dist,.3/dist,.5/dist,1.);
}
