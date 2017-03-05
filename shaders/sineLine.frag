uniform float time;
uniform vec2 resolution;

void main(void) {
	vec2 pos = gl_FragCoord.xy/resolution;
	pos.y-=.5;
	float sineWave = sin(pos.x*10.+time*.25)*.15;
	sineWave*=sin(time*.25);
	
  	float dist = distance(pos.y,sineWave)*20.;
  	
  	gl_FragColor = vec4(.6/dist,.3/dist,.5/dist,1.);
}
