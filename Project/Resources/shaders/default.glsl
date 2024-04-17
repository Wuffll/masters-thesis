#shader VERT
#version 460

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aTexCoord;

uniform vec4 uDefaultColor;
uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec4 vColor;

void main()
{
	float color = 0.85f * (aPosition.y / 255.0f);
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0f);// uProjection * vec4(aPosition, 1.0f);
	vColor = vec4(color, 0.0f, 0.2f, 1.0f);
	vColor = vec4(abs(aNormal), 1.0f);
}

#shader FRAG
#version 460

in vec4 vColor;

out vec4 fColor;

void main()
{
	fColor = vColor;
}