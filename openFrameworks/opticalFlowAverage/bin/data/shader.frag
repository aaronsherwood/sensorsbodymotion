#version 120

uniform vec2 loc;

void main()
{
    float dist = 50./distance(gl_FragCoord.xy, loc);
    gl_FragColor = vec4(.6*dist,.3*dist,.5*dist,1.);
}
