/*
 taken from here:
 http://pixelshaders.com/editor/
*/
// ISADORA_FLOAT_PARAM(amount, amnt, 0., 10., 6., "How many sides");
uniform float amount;
// ISADORA_FLOAT_PARAM(size, amn2, 0., 10., 6., "How many sides");
uniform float size;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;

float rand(vec2 co){
return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
vec2 p = gl_FragCoord.xy/resolution;
vec4 color = texture2D(tex0, p);
float xs = floor(gl_FragCoord.x / size);
float ys = floor(gl_FragCoord.y / size);
vec4 snow = vec4(rand(vec2(xs * time,ys * time))*amount);

//"gl_FragColor = color + amount * ( snow - color );", //interpolate

gl_FragColor = color+ snow;

}