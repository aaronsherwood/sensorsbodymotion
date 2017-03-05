/*
 taken from here:
 http://pixelshaders.com/editor/
*/
// ISADORA_FLOAT_PARAM(amount, amnt, 0., 1., .1, "How many sides");
uniform float amount;
// ISADORA_FLOAT_PARAM(angle, amn2, 0., 360, 6., "How many sides");
uniform float angle;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D tex0;

 
void main() {
 
vec2 vUv = gl_FragCoord.xy/resolution;
vec2 offset = amount * vec2( cos(angle), sin(angle));
vec4 cr = texture2D(tex0, vUv + offset);
vec4 cga = texture2D(tex0, vUv);
vec4 cb = texture2D(tex0, vUv - offset);
gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);
 
}