#version 330

in vec4 PositionInProjection;

void main()
{
	gl_Position = PositionInProjection;
}
