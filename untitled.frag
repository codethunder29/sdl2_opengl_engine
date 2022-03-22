
// uint rgba2color(uint r, uint g, uint b, uint a)
// {
// 	uint color = r;
// 	color = color << 8;
// 	color = color | g;
// 	color = color << 8;
// 	color = color | b;
// 	color = color << 8;
// 	return color | a;
// }

// vec4 color2vec4(uint color)
// {
// 	vec4 vec;
// 	uint mask = uint(0x000000ff);
// 	// uint tmp = color;

// 	vec.w = float(color & mask);
// 	color = color >> 8;
// 	vec.z = float(color & mask);
// 	color = color >> 8;
// 	vec.y = float(color & mask);
// 	color = color >> 8;
// 	vec.x = float(color & mask);

// 	return vec;
// }

void main()
{
	// uint vColor = rgba2color(uint(255), uint(150), uint(255), uint(255));
	// vec4 col = color2vec4(vColor);
	// col /= 255.0;

	// if(vColor == uint(255))
	// {
	// 	gl_FragColor = vec4(1, 0, 0, 1);
	// }
	// else
	// {
	// 	gl_FragColor = vec4(0, 0, 1, 1);
	// }

	gl_FragColor = vec4(0.5608, 0.1216, 0.1216, 1.0);
}


