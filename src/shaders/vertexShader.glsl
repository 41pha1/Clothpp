#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvLocation;
layout(location = 2) in vec3 normalDirection_modelspace;

out vec3 position;
out vec3 normal;
out vec2 uv;

uniform mat4 MODEL;
uniform mat4 VP;

void main()
{
	uv = uvLocation;
	position = (MODEL * vec4(vertexPosition_modelspace, 1.)).xyz;
	normal = (MODEL * vec4(normalDirection_modelspace, 1.)).xyz;
	gl_Position = VP * MODEL * vec4(vertexPosition_modelspace, 1.);
}