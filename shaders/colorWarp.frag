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
	vec3 crazyColor;
  	crazyColor.r = wave(color.r, 10.);
  	crazyColor.g = wave(color.g, 20.);
  	crazyColor.b = wave(color.b, 40.);
  	
  	gl_FragColor = vec4(crazyColor,1.);
}
