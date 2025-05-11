@echo off

call glslangvalidator -V -o bin/basic.vert.spirv basic.vert.glsl
call glslangvalidator -V -o bin/basic.frag.spirv basic.frag.glsl
pause