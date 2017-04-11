#version 150

uniform mat4 trans;
uniform mat4 proj;

in vec4 vtxPosition;
in vec4 vtxColor;
in vec3 vNormal;

out vec4 vColor;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform mat4 modelView;
uniform mat4 projection;
uniform vec4 lightPosition;
uniform vec4 lightColor;
uniform float shininess;

uniform mat4 projMat;
uniform mat4 transMat;
uniform mat4 rotMat;

out vec2 vTexCoord;
in vec2 texCoord;

/*
void main()
{
	vColor = vtxColor;
	vTexCoord = texCoord;
	gl_Position = projMat * rotMat * transMat * vtxPosition; // rotMat for view rotation
	gl_PointSize = 30.0;
} */

void main()
{
	vTexCoord = texCoord;
	
	vec4 vPos = vtxPosition;//projMat * rotMat * transMat * vtxPosition;
	vec4 vLight = lightPosition;
	//vtxColor = vec4(1.0, 1.0, 1.0, 1.0);

	vec3 L = normalize(vLight.xyz - vPos.xyz); // light Diretion
	vec4 N = projMat * rotMat * transMat * vec4(vNormal, 0.0);
	vec3 Nn = normalize(N.xyz);
	float diffuse = dot(Nn, L);
	
	//vColor = vtxColor;
	//vColor = diffuse * vtxColor * lightColor ;

	if (diffuse >= 0)
	{
		vColor = diffuse * vtxColor * lightColor ;
	} 
	else
	{
		vColor = vec4(0.0, 0.0, 0.0, 1.0);
	}

	vec3 R = reflect(-L, Nn);
	vec3 V = normalize(-vPos.xyz);
	float specular = pow(dot(R, V), shininess);

	//vColor += (specular * vec4(1.0, 1.0, 1.0, 1.0));

	if (specular >= 0)
	{
		vColor += (specular * vec4(1.0, 1.0, 1.0, 1.0));
	}
	else
	{
		vColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	gl_Position = projMat *rotMat* transMat * vPos;
}
