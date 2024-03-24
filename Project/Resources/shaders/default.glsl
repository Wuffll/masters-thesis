#shader VERT
#version 460

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
// layout(location = 2) in vec4 aColor;

uniform vec4 uDefaultColor;

out vec4 vColor;

void main()
{
	gl_Position = vec4(aPosition, 1.0f);
	vColor = vec4(aNormal, 1.0f);
}

#shader FRAG
#version 460

in vec4 vColor;

out vec4 fColor;

void main()
{
	fColor = vColor;
}