#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec3 VertexPosition;
attribute vec3 VertexColor;
attribute vec3 VertexNormal;
attribute vec2 TextureCoordinate;
attribute vec3 VertexTangents;

uniform mat4 MVMat;
uniform mat4 ProjMat;
uniform float time;

varying vec3 baseColor;
varying vec3 fragPosition;
varying vec2 UV;
varying vec3 N, T;

void main()
{
    gl_Position = ProjMat * MVMat * vec4(VertexPosition, 1.0);
    baseColor = VertexColor;
    fragPosition = VertexPosition;
    UV = TextureCoordinate;
    N = VertexNormal;
    T = VertexTangents;
}

















