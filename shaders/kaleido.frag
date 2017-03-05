/*
 taken from here:
 http://pixelshaders.com/editor/
*/
// ISADORA_FLOAT_PARAM(amount, amnt, 0.1, 24., 6., "How many sides");
uniform float amount;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;

void main(void) {
	
	// normalize to the center
  vec2 p = gl_FragCoord.xy/resolution - 0.5;
  
  // cartesian to polar coordinates
  float r = length(p);
  float a = atan(p.y, p.x);
  
  // kaleidoscope
  float sides = (amount);
  float tau = 2. * 3.1416;
  a = mod(a, tau/sides);
  a = abs(a - tau/sides/2.);
  
  // polar to cartesian coordinates
  p = r * vec2(cos(a), sin(a));
  
  // sample the webcam
  vec4 color = texture2D(tex0, p + 0.5);
  gl_FragColor = color;
}