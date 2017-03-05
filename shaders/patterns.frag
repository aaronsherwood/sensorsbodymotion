/*
 taken from here:
 http://pixelshaders.com/examples/
*/

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;


// ISADORA_FLOAT_PARAM(amount, amnt, 0., 1., .5, "How many wraps");
uniform float amount;

float wrap(float x) {
  return abs(mod(x, 2.)-1.);
}

void main(void) {
	//fragment position
	vec2 p = gl_FragCoord.xy/resolution;
	float size = amount;
  	p.x = mod(p.x, size);
  	p.x = abs(p.x - size/2.);
  	p.x = wrap(p.x + time/6.);

  	gl_FragColor = texture2D(tex0, p);
}