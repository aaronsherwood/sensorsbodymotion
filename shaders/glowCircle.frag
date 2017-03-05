uniform vec2 mouse;
uniform vec2 resolution;

void main(void) {
  	float dist = 50./distance(gl_FragCoord.xy, mouse*resolution);
  	gl_FragColor = vec4(.6*dist,.3*dist,.5*dist,1.);
}

