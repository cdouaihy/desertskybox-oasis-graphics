#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    float ratio = 1.00 / 1.33;
    vec3 I = normalize(Position - cameraPos);
    vec3 R1 = reflect(I, normalize(Normal));
    vec3 R2 = refract(I, normalize(Normal), ratio);
    vec4 FragColorReflect = vec4(texture(skybox, R1).rgb, 1.0);
    vec4 FragColorRefract = vec4(texture(skybox, R2).rgb, 1.0);
    FragColor = mix(FragColorReflect, FragColorRefract, 0.5);
    
}
