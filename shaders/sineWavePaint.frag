//from https://www.shadertoy.com/view/ltX3Wn
//im not good at math so i cant explain how it works.
//i just optimized the code.the original code i saw was for WAha_06_36
//however i tried to explain the affect of constants
const int ls= 1;			// i++;
const int cp= 8;			//for loop up to 8.
const float sc= 3.3;		//u can reduce loop if u put correct value here.
const float aa= 4.5;		//u can reduce loop if u put correct value here.
const float ma= 2.0;		//makes more diffrent colors.reduces the waves width.
const float d= 0.02;		//adding iGlobalTime to coordinates affect the whole surface.movement.reduce this constant to reduce these effects
const float sp= 0.3;		//affects speed of movement
const float dt= 0.0075;		//distance.
const float st= 32.0;		//shape of waves
const float c= 0.5;			//contrast and brightness
const float b= 0.575;		//contrast and brightness,white background
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    float ad=sc,qu=aa;
    vec2 p=(fragCoord.xy)*dt+iGlobalTime*d;
    for(int i=1;i<cp;i+=ls)
    {
        float k=ma/qu;
        float s=iGlobalTime*sp*(sin(float(i))+1.0);//movement of the waves,sin(i) adds some extra movement at the edge of waves
        p.x+=k*sin(ad*p.y-s)+st;// p.x+i*sin(i*p.y)+1.0 this algorithm makes the waves like what you see.
        p.y+=k*sin(ad*p.x+s)+st;// p.y+i*sin(i*p.x)+1.0
        qu+=aa;
        ad+=sc;
   }
    vec3 col=vec3(sin(p.y*ma),sin(p.x*ma),cos(p.y+p.x));// red vertical wave.green horizontal wave.blue diagonal wave.ma changes the width of waves
    fragColor=vec4(b-col*c,1.0);
}