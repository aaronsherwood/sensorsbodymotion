#version 300 es
precision mediump float;

// grab texcoords from vert shader
in vec2 vTexCoord;

in vec2 gl_FragColor;

// our textures coming from p5
uniform sampler2D tex0;
uniform vec2 resolution;

uniform float amount;

uniform float power;

const vec3 palette[6] = vec3[](1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.5), vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 0.5, 1.0), vec3(0.0, 0.0, 1.0));
const bool PALETTE_MODE = false;

vec2 characterSize = vec2(10.0, 50.0);


float amt = 0.1; // the amount of displacement, higher is more
float squares = 20.0; // the number of squares to render vertically

void main() {

      vec2 windowSizeInCharacters = resolution.xy / characterSize;
      vec2 uv = floor((gl_FragCoord.xy / resolution.xy) * windowSizeInCharacters) / windowSizeInCharacters;

      vec3 webcamPixel = texture(cam, uv).rgb;
      vec3 outputColor = webcamPixel;

      if (PALETTE_MODE) {
          float minimumError = 5.0; // Arbitrary value greater than 3 (the sum of all channels in the brightest color, white).
          for (int color=0; color < palette.length(); color++) {
              vec3 colorError = abs(palette[color] - webcamPixel); // Absolute difference between the actual color and palette color.
              float totalError = colorError.r + colorError.g + colorError.b;
              if (totalError < minimumError) {
                  minimumError = totalError;
                  outputColor = palette[color];
              }
          }
      }

      gl_FragColor = vec4(outputColor, 1.0);
  }
}
