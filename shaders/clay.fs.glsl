#version 330

uniform vec3 lightPosition;
uniform vec4 lightColor;

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragPos;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord);

    vec3 lightDirection = normalize(lightPosition - fragPos);
    float diffuse = max(dot(fragNormal, lightDirection), 0.0);

    vec3 baseColor = vec3(0.167, 0.439, 0.015);

    vec3 ambientColor = vec3(0.8, 0.6, 0.4);
    vec3 diffuseColor = vec3(0.9, 0.7, 0.5);
    vec3 specularColor = vec3(1.0, 0.8, 0.6);


    vec3 finalClayColor =
        ambientColor * baseColor +
        diffuseColor * baseColor * diffuse +
        specularColor *  lightColor.rgb * pow(max(dot(reflect(-lightDirection, fragNormal), normalize(-fragPos)), 0.0), 32.0);

    // Output the final color
    finalColor = vec4( mix(finalClayColor, texelColor.rgb, 0.7), 1.0);
}

//#version 330
//
//// Input vertex attributes (from vertex shader)
//in vec2 fragTexCoord;
//in vec4 fragColor;
//
//// Input uniform values
//uniform sampler2D texture0;
//uniform vec4 colDiffuse;
//
//// Output fragment color
//out vec4 finalColor;
//
//// NOTE: Add here your custom variables
//
//void main()
//{
//    // Texel color fetching from texture sampler
//    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
//
//    // Convert texel color to grayscale using NTSC conversion weights
//    float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));
//    vec3 grayscaled = vec3(gray, gray, gray);
//
//    // Calculate final fragment color
//    finalColor = vec4(mix(texelColor.rgb, grayscaled, 0.36), texelColor.a);
//}

