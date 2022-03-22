#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;
in vec4 vColor;
flat in int vSlot;

uniform sampler2D uTextures[10];

vec4 getTextureColor(int slot)
{
    // GLSL 3.3 doesn't support uTextures[slot] so instead im doing this dumb way
    switch(slot)
    {
        case 0:
            return texture(uTextures[0], vTexCoord);
        case 1:
            return texture(uTextures[1], vTexCoord);
        case 2:
            return texture(uTextures[2], vTexCoord);
        case 3:
            return texture(uTextures[3], vTexCoord);
        case 4:
            return texture(uTextures[4], vTexCoord);
        case 5:
            return texture(uTextures[5], vTexCoord);
        case 6:
            return texture(uTextures[6], vTexCoord);
        case 7:
            return texture(uTextures[7], vTexCoord);
        case 8:
            return texture(uTextures[8], vTexCoord);
        case 9:
            return texture(uTextures[9], vTexCoord);
        default:
            return vec4(0,0,0,1);
    }
}

void main()
{
    if(vSlot != -1)
    {
        vec4 texColor = getTextureColor(vSlot);
        color = texColor * vColor;
    }
    else
    {
        color = vColor;
    }
}