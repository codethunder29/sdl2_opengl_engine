#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec2 scale;
layout(location = 3) in float angle;
layout(location = 4) in vec2 pivotPoint;
layout(location = 5) in uint color;
layout(location = 6) in int slot;

out vec2 vTexCoord;
out vec4 vColor;
flat out int vSlot;

// uniform vec2 uScreenSize;
uniform mat4 uPV;  // projection view matrix
// uniform float uAngle;
uniform vec4 uCamOffset;
// uniform mat4 uProjection;
uniform vec4 uRotation;

vec4 color2vec4(uint color)
{
	vec4 vec;
	uint mask = uint(0x000000ff);
	vec.w = float(color & mask);
	color = color >> 8;
	vec.z = float(color & mask);
	color = color >> 8;
	vec.y = float(color & mask);
	color = color >> 8;
	vec.x = float(color & mask);

	return vec;
}

mat4 rotationFromPivot(float angle, vec2 pivot)
{
	float x = pivot.x;
	float y = pivot.y;
	mat4 rot = mat4(
		cos(angle), 				   sin(angle),					0, 0,
		-sin(angle), 				   cos(angle), 					0, 0,
		0, 							   0, 							1, 0,
		-x*cos(angle)+y*sin(angle)+x, -x*sin(angle)-y*cos(angle)+y, 0, 1
	);

	return rot;
}

mat4 scaleAroundPoint(vec2 scale, vec2 pivot)
{
	mat4 scaleMat = mat4(
		scale.x, 	  			  0, 		  				0, 0,
		0, 			  			  scale.y, 				    0, 0,
		0, 			  			  0, 	 			        1, 0,
		-pivot.x*scale.x+pivot.x, -pivot.y*scale.y+pivot.y, 0, 1
	);

	return scaleMat;
}

void main()
{
	mat4 model = rotationFromPivot(angle, pivotPoint) * scaleAroundPoint(scale, pivotPoint);

	gl_Position = uPV * model * position;
	vTexCoord = texCoord;
	vColor = color2vec4(color)/255;  // unpacking color

	vSlot = slot;
}