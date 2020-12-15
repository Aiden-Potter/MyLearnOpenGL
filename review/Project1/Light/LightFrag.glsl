#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material {
	vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
};

struct LightPoint{
	float constant;
	float linear;
	float quadratic;
};

struct LightSpot{
	float cosPhyInner;
	float cosPhyOutter;
};
uniform LightSpot lightS;
uniform LightPoint lightPoint;
uniform Material material;

uniform vec3 lightPosUniform;
uniform vec3 lightDirection;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform float mixValue;

void main()
{
	float dist = length(lightPosUniform-FragPos);
    float attenuation = 1.0/(lightPoint.constant+lightPoint.linear*dist+lightPoint.quadratic*(dist*dist));
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightDirection);
	vec3 lightDir = normalize(lightPosUniform-FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = material.diffuse *  diff * lightColor;
	vec3 diffuse = diff* lightColor * vec3(texture(material.diffuse, TexCoord));

    vec3 cameraDir= normalize(cameraPos - FragPos);
    vec3 reflectVec = reflect(-lightDir,norm);
    float specAmount = pow(max(dot(reflectVec,cameraDir),0),material.shininess); 
    vec3 specColor = vec3(texture(material.specular, TexCoord)) * specAmount*lightColor;

	vec3 ambient =  material.ambient * ambientColor * vec3(texture(material.diffuse, TexCoord));
	vec3 emission = texture(material.emission,TexCoord).rgb;

	float cosTheta = dot(normalize(FragPos-lightPosUniform),-1*normalize(lightDirection));
	
	float spotRatio;
	if(cosTheta>lightS.cosPhyInner)
	{
		
		spotRatio = 1.0;
	}else if(cosTheta>lightS.cosPhyOutter)
	{
		spotRatio = (cosTheta-lightS.cosPhyOutter) / (lightS.cosPhyInner-lightS.cosPhyOutter);
	}
	else
	{
		spotRatio = 0;
	}
	spotRatio = 1;
	vec3 result = ( ambient+(specColor+diffuse)*spotRatio ) * objectColor;
    
    FragColor = vec4(result, 1.0);
}