#version 330

in vec2 fragTexCoord;
uniform sampler2D texture0;
uniform float bloomThreshold;
uniform float bloomIntensity;
uniform float bloomRadius;
uniform vec3 sunDir;
uniform vec3 sunColor;
uniform float sunIntensity;

// Output fragment color
out vec4 finalColor;

void main()
{
    // Apply bloom effect
    vec4 oldc = texture(texture0, fragTexCoord);
    vec4 color = texture(texture0, fragTexCoord);
    vec3 brightness = color.rgb * 0.5 + 0.5;
    float luminance = dot(brightness, vec3(0.2126, 0.7152, 0.0722));

    //    if (luminance > bloomThreshold) {
    vec4 bloomColor = vec4(vec3(brightness * bloomIntensity), 1.0);
    for (int i = 0; i < 5; i++) {
        float blurRadius = bloomRadius * float(i + 1);
        bloomColor += texture(texture0, fragTexCoord + vec2(0.0, blurRadius) / textureSize(texture0, 0)).rgba;
        bloomColor += texture(texture0, fragTexCoord + vec2(blurRadius, 0.0) / textureSize(texture0, 0)).rgba;
        bloomColor += texture(texture0, fragTexCoord - vec2(0.0, blurRadius) / textureSize(texture0, 0)).rgba;
        bloomColor += texture(texture0, fragTexCoord - vec2(blurRadius, 0.0) / textureSize(texture0, 0)).rgba;
    }

    bloomColor = vec4(20.0, 10.0, 10.0, 20.0);

    color = mix(color, bloomColor / 20.0, clamp(luminance - bloomThreshold, 0.0, 1.0));
    //    }

    // Apply sun lighting effect
    vec3 normal = normalize(vec3(fwidth(brightness.r), fwidth(brightness.g), 1.0));
    float sunDot = max(dot(normal, sunDir), 0.0);
    vec3 sunColorIntensity = sunColor * sunIntensity * sunDot;
    color.rgb += sunColorIntensity;

    finalColor = color;
}