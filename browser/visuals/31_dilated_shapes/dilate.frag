precision mediump float;

uniform vec2 resolution;
uniform sampler2D tex0;
uniform sampler2D tex1;
vec2 offset [9];
float spread = 0.75;
float decay = 0.02;

void main() {
  vec2 res = resolution.xy;
  vec2 step = spread / res;
  vec2 uv = gl_FragCoord.xy / res;
  vec4 sum = texture2D(tex0, vec2(uv.x,1.-uv.y));

  // 49 taps gives us better results but you could probably find settings that work with less
  for(int y = -7; y <= 7; y++){
      for(int x = -7; x <= 7; x++){
        vec4 color;
        color = texture2D(tex1, vec2(1.-uv.x,uv.y) + vec2(x, y) * step);
        sum = max(color, sum);
      }
  }

  gl_FragColor = sum - decay;
}
