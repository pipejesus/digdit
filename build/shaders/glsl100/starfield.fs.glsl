#version 100

precision mediump float;

#define RANDOM_SCALE vec4(443.897, 441.423, .0973, .1099)

#ifndef DIGITS_SIZE
#define DIGITS_SIZE float2(.025, .025)
#endif

#ifndef DIGITS_DECIMALS
#define DIGITS_DECIMALS 2.0
#endif

uniform float iTime;
uniform int bgStars;
uniform vec2 iResolution;
uniform vec3 iColor;
uniform float iBaseSpeed;
uniform float iSeedFactor;
uniform int iDrawingBg;

// Source: https://lygia.xyz/generative/srandom
float srandom(in float x) {
    return -1. + 2. * fract(sin(x) * 43758.5453);
}

float scaledrandom(in float x) {
    float r = 4.0 * srandom(pow(x, 3.0));
    return max(-2.0, r);
}

//  Function from Iñigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb(in vec3 c) {
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0, 4.0, 2.0),
    6.0)-3.0)-1.0,
    0.0,
    1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

vec4 starColor(vec2 uv, float satFactor, float brightnessFactor, float alpha) {
    vec3 c = iColor;
    c.y = c.y * satFactor;
    c.z = c.z * brightnessFactor;

    return vec4(hsb2rgb(c), alpha);
}

float getDecide(vec2 uv, float centerX, float yOffset, float speedFactor, float lengthFactor, float widthFactor) {
    //    Set the minimum width for 1 pixel
    float pixel = 1.0 / iResolution.x;
    float width = max(pixel * widthFactor, pixel);

    float height = 0.5 * lengthFactor;
    float scrollFactor = iBaseSpeed * speedFactor;
    float tailSize = max(0.03, 0.4 * lengthFactor);
    
    float startY = mod(iTime * speedFactor, 1.0 + height + yOffset) - height;
    startY = startY - yOffset;
    float endY = startY + height;

    // cool choices
    //    float val = uv.x + pow(sin(uv.y * 1.0), .99) / 10.0;
    //    float val = uv.x + pow(sin(uv.y * 2.0), 1.0) / 10.0;
    //    float val = uv.x + pow(sin(uv.y * 2.0), 3.0) / 10.0;
    float val = uv.x;

    float res =
    smoothstep(centerX - width, centerX, val)
    - smoothstep(centerX, centerX + width, val);

    /** Draw only a portion of the vertical line creating a star track **/
    res = res * (
    smoothstep(startY, startY + tailSize, uv.y)
    - smoothstep(endY - 0.02, endY, uv.y)
    );

    /** Darken towards the bottom and top of the screen **/
    float hideFactor = (smoothstep(0.0, 0.2, uv.y) - smoothstep(0.8, 1.0, uv.y));
    res = res * hideFactor;

    return res;
}

vec4 mixStarsLayer5(vec2 uv, vec4 c, vec4 bg, float speedFactor, float lengthFactor, float widthFactor, vec4 starColor, float offsetX) {
    const int starsCount = 5;
    float starsGap = 1.0 / float(starsCount);
    float centerX =  starsGap / 2.0 + offsetX;
    float offsetY = min(starsGap, starsGap * scaledrandom(centerX));

    for (int ox = 0; ox < starsCount; ox++) {
        float decide = getDecide(uv, centerX, offsetY, speedFactor, lengthFactor, widthFactor);
        c = c - (bg * decide) + (starColor * decide);
        centerX += starsGap;
        offsetY += min(starsGap, starsGap * scaledrandom(centerX));
        offsetY = mod(offsetY, 0.5);
    }

    return c;
}

vec4 mixStarsLayer10(vec2 uv, vec4 c, vec4 bg, float speedFactor, float lengthFactor, float widthFactor, vec4 starColor, float offsetX) {
    const int starsCount = 10;
    float starsGap = 1.0 / float(starsCount);
    float centerX =  starsGap / 2.0 + offsetX;
    float offsetY = min(starsGap, starsGap * scaledrandom(centerX));

    for (int ox = 0; ox < starsCount; ox++) {
        float decide = getDecide(uv, centerX, offsetY, speedFactor, lengthFactor, widthFactor);
        c = c - (bg * decide) + (starColor * decide);
        centerX += starsGap;
        offsetY += min(starsGap, starsGap * scaledrandom(centerX));
        offsetY = mod(offsetY, 0.5);
    }

    return c;
}

void main() {
    vec2 uv = (gl_FragCoord.xy / iResolution.xy);
    uv.y = 1.0 - uv.y;

    vec4 bg = vec4(0.01, 0.01, 0.09, 1.0);

    /**
    * If drawing foreground -- set the color to black to allow for unspoiled
    * color mixing in blend mode
    **/

    if (iDrawingBg == 0) {
        bg = vec4(0.0, 0.0, 0.0, 1.0);
    }

    vec4 c = bg;

    /**
     * Create and Mix Back layer of stars
    **/

    float speedFactor = 0.3;
    float widthFactor = 0.3;
    float lengthFactor = 0.4;
    float offsetX = 0.0;
    vec4 currentStarColor = starColor(uv, 0.4, 0.7, 1.0);

    /**
    * If drawing background -- draw the slower layer of stars with small tail
    **/

    if (iDrawingBg == 1) {
        c = mixStarsLayer10(uv, c, bg, speedFactor, 1.0, 1.0, currentStarColor, -.05);
    }

    /**
     * Create and Mix Front layer of stars
    **/

    if (iDrawingBg == 1) {
        speedFactor = 1.0;
        widthFactor = 1.0;
        lengthFactor = 0.8;
        currentStarColor = starColor(uv, 1.0, 3.0, 1.0);
        c = mixStarsLayer10(uv, c, bg, speedFactor, lengthFactor, widthFactor, currentStarColor, offsetX);
    } else {
        speedFactor = 1.4;
        widthFactor = 2.0;
        lengthFactor = 0.5;
        currentStarColor = starColor(uv, 1.0, 0.4, 1.0);
        offsetX = -0.17;
        c = mixStarsLayer5(uv, c, bg, speedFactor, lengthFactor, widthFactor, currentStarColor, offsetX);
    }

    gl_FragColor = vec4(c);
}