/*
 taken from here:
 http://pixelshaders.com/examples/
*/

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;


void main(void) {
	//fragment position
	vec2 pos = gl_FragCoord.xy/resolution;
	pos.x = pos.x + sin(pos.y*20.+time*2.)*0.05;
  	gl_FragColor = texture2D(tex0, pos);
}


