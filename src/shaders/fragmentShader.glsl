#version 330 core

in vec3 position;
in vec3 normal;
in vec2 uv;

out vec3 color;

void main()
{
	color = vec3(0.01, 0.1, 0.01);

	vec3 facing = normal;
	if(!gl_FrontFacing)
		facing = -facing;

	vec3  sun_lig = normalize( vec3(0.6, 0.35, 0.5) );
    float sun_dif = clamp(dot( facing, sun_lig ), 0.0, 1.0 );
	float sky_dif = sqrt(clamp( 0.5+0.5*facing.y, 0.0, 1.0 ));

	vec3 lin = vec3(0.0);
    lin += sun_dif*vec3(8.10,8.00,8.20) * 0.1;
    lin += sky_dif*vec3(0.50,0.70,1.00);
	color = color*lin;

//	color = pow(color,vec3(0.8,0.9,1.0) );
//    color = color*vec3(1.11,0.89,0.79);    
    color = 1.35*color/(1.0+color);
    color = pow( color, vec3(0.4545) );
}
