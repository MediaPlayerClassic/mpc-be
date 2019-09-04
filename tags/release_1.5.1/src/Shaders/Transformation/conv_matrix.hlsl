// http://www.itu.int/rec/R-REC-BT.709-6-201506-I/en
static float4x4 rgb_ycbcr709 = {
	 0.2126,  0.7152,  0.0722, 0.0,
	-0.1146, -0.3854,  0.5,    0.0,
	 0.5,    -0.4542, -0.0458, 0.0,
	 0.0,     0.0,     0.0,    0.0
};

static float4x4 ycbcr709_rgb = {
	1.0,  0.0,     1.5748, 0.0,
	1.0, -0.1873, -0.4681, 0.0,
	1.0,  1.8556,  0.0,    0.0,
	0.0,  0.0,     0.0,    0.0
};

// https://en.wikipedia.org/wiki/YCoCg
static float4x4 ycgco_rgb = {
	1.0, -1.0,  1.0, 0.0,
	1.0,  1.0,  0.0, 0.0,
	1.0, -1.0, -1.0, 0.0,
	0.0,  0.0,  0.0, 0.0
};