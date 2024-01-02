#version 460
//in vec3 color;
in vec2 texCoords;
out vec4 frag_color;
uniform sampler2D tex;
void main(){
   frag_color = texture(tex, texCoords);
}