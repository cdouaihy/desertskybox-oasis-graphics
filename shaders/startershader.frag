#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
//in vec2 Tex;

//uniform vec3 cameraPos;
uniform samplerCube skybox;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
  
uniform Material material;
uniform vec3 color;
uniform vec3 lightAttr1; // light color
uniform vec3 lightAttr2; // light position
uniform vec3 viewPos; 

void main()
{
    vec3 I = normalize(Position - viewPos);
    vec3 R = reflect(I, normalize(Normal));
	R.y = -1.0 * R.y;
    //FragColor = vec4(texture(skybox, R).rgb, 1.0);
    //FragColor = vec4(0.695f,0.375f,0.18f,1.0);
	//FragColor = vec4(texture(tex1,Tex), 1.0);
	
	vec3 result;
    float atten = 1/(0.2*(length(lightAttr2 - Position)));
    vec3 ambient = material.ambient * lightAttr1;
        
    vec3 lightDir = normalize(lightAttr2 - Position);
    //float diff = max(dot(Normal,lightDir), 0.0);
    vec3 diffuse = lightAttr1 /* diff  */ * material.diffuse;
        
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * lightAttr1;
    result = normalize((ambient + diffuse  ))  ; 
	FragColor = vec4(texture(skybox, R).rgb, 1.0) * vec4(0.695f,0.375f,0.18f,1.0); //-  vec4(result,1.0);
}
