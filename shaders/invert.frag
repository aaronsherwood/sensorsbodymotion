/*
 taken from the tutorial here, by Inigo Quilez:
 https://www.youtube.com/watch?v=0ifChJ0nJfM
*/

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;

float wave(float x, float amount){
	return (sin(x * amount) + 1.) *.5;
}

void main(void) {
	//fragment position
	vec2 pos = gl_FragCoord.xy/resolution;
	vec4 color = texture2D(tex0, pos);
  	
  	gl_FragColor = vec4(1.-color.rgb,1.);
}
