#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D ambientMap;
uniform sampler2D specularMap;

varying vec3 baseColor;
varying vec3 fragPosition;
varying vec2 UV;
varying vec3 N, T;

vec3 BumpNormal;

void CalcBumpedNormal()
{
    vec3 norm = normalize(N);
    vec3 Tangent = normalize(T);
    Tangent = normalize(Tangent - dot(Tangent, norm) * norm);
    vec3 Bitangent = cross(Tangent, norm);
    vec3 BumpMapNormal = texture2D(normalMap, UV).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    mat3 TBN = mat3(Tangent, Bitangent, norm);
    BumpNormal = TBN * BumpMapNormal;
    BumpNormal = normalize(BumpNormal);
}

void main()
{
    /* Color */
    vec3 color = texture2D(diffuseMap, UV).xyz;

    /* Normals */
    CalcBumpedNormal();
    vec3 normal = BumpNormal;

    /* Ambient */
    vec3 ambient = texture2D(ambientMap, UV).xyz * color;

    /* Diffuse */
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    /* Specular */
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = texture2D(specularMap, UV).xyz * spec;

    gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}





















