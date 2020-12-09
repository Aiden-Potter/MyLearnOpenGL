#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 cameraPos;
uniform float mixValue;

void main()
{
    //FragColor = mix(texture(texture1, TexCoord),texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)),mixValue);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 cameraDir= normalize(cameraPos - FragPos);

    vec3 reflectVec = reflect(-lightDir,norm);
    float specAmount = pow(max( dot(reflectVec,cameraDir),0),32) ; 
    vec3 specColor = specAmount*lightColor;

    vec3 result = (ambientColor+diffuse+specColor) * objectColor;
    FragColor = vec4(result, 1.0);
}