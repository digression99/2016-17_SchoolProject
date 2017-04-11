#version 150

uniform vec4 uColor;

in vec4 vColor;
out vec4 gl_FragColor;

in vec2 vTexCoord;
uniform sampler2D sampler;

void main() 
{ 
		gl_FragColor = vColor * texture(sampler, vTexCoord);
} 




