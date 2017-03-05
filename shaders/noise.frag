/*
Iterated Fractional Brownian Motion
Based on:
  http://pixelshaders.com/examples/
*/

// ISADORA_FLOAT_PARAM(zoom, amnt, 0.1, 100., 6., "How many sides");
uniform float zoom;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;


float random(float p) {
  return fract(sin(p)*10000.);
}

float noise(vec2 p) {
  return random(p.x + p.y*10000.);
}

vec2 sw(vec2 p) {return vec2( floor(p.x) , floor(p.y) );}
vec2 se(vec2 p) {return vec2( ceil(p.x)  , floor(p.y) );}
vec2 nw(vec2 p) {return vec2( floor(p.x) , ceil(p.y)  );}
vec2 ne(vec2 p) {return vec2( ceil(p.x)  , ceil(p.y)  );}

float smoothNoise(vec2 p) {
  vec2 inter = smoothstep(0., 1., fract(p));
  float s = mix(noise(sw(p)), noise(se(p)), inter.x);
  float n = mix(noise(nw(p)), noise(ne(p)), inter.x);
  return mix(s, n, inter.y);
  return noise(nw(p));
}

float movingNoise(vec2 p) {
  float total = 0.0;
  total += smoothNoise(p     - time);
  total += smoothNoise(p*2.  + time) / 2.;
  total += smoothNoise(p*4.  - time) / 4.;
  total += smoothNoise(p*8.  + time) / 8.;
  total += smoothNoise(p*16. - time) / 16.;
  total /= 1. + 1./2. + 1./4. + 1./8. + 1./16.;
  return total;
}

float nestedNoise(vec2 p) {
  float x = movingNoise(p);
  float y = movingNoise(p + 100.);
  return movingNoise(p + vec2(x, y));
}

void main() {
  vec2 p = gl_FragCoord.xy/resolution * zoom;
  float brightness = nestedNoise(p);
  gl_FragColor.rgb = vec3(brightness);
  gl_FragColor.a = 1.;
}