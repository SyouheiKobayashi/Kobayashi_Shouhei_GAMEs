xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 26;
 499.99996;0.00000;-999.99992;,
 -500.00011;0.00000;-999.99992;,
 -500.00011;0.00000;1000.00021;,
 499.99996;0.00000;1000.00021;,
 -475.52828;154.50850;1500.00002;,
 -500.00001;0.00000;1500.00002;,
 -500.00001;0.00000;-1500.00002;,
 -475.52828;154.50850;-1500.00002;,
 -404.50853;293.89266;1500.00002;,
 -404.50853;293.89266;-1500.00002;,
 -293.89261;404.50853;1500.00002;,
 -293.89261;404.50853;-1500.00002;,
 -154.50849;475.52833;1500.00002;,
 -154.50849;475.52833;-1500.00002;,
 0.00001;500.00011;1500.00002;,
 0.00001;500.00011;-1500.00002;,
 154.50854;475.52833;1500.00002;,
 154.50854;475.52833;-1500.00002;,
 293.89270;404.50855;1500.00002;,
 293.89270;404.50855;-1500.00002;,
 404.50860;293.89270;1500.00002;,
 404.50860;293.89270;-1500.00002;,
 475.52838;154.50854;1500.00002;,
 475.52838;154.50854;-1500.00002;,
 500.00011;-0.00000;1500.00002;,
 500.00011;0.00000;-1500.00002;;
 
 11;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;14,12,13,15;,
 4;16,14,15,17;,
 4;18,16,17,19;,
 4;20,18,19,21;,
 4;22,20,21,23;,
 4;24,22,23,25;;
 
 MeshMaterialList {
  1;
  11;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  12;
  0.000000;1.000000;0.000000;,
  0.987688;-0.156434;-0.000000;,
  0.951057;-0.309017;-0.000000;,
  0.809017;-0.587785;-0.000000;,
  0.587785;-0.809017;-0.000000;,
  0.309017;-0.951056;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.309017;-0.951056;0.000000;,
  -0.587785;-0.809017;0.000000;,
  -0.809017;-0.587785;0.000000;,
  -0.951057;-0.309017;0.000000;,
  -0.987688;-0.156434;0.000000;;
  11;
  4;0,0,0,0;,
  4;2,1,1,2;,
  4;3,2,2,3;,
  4;4,3,3,4;,
  4;5,4,4,5;,
  4;6,5,5,6;,
  4;7,6,6,7;,
  4;8,7,7,8;,
  4;9,8,8,9;,
  4;10,9,9,10;,
  4;11,10,10,11;;
 }
 MeshTextureCoords {
  26;
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  0.050000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.050000;0.250000;,
  0.100000;0.000000;,
  0.100000;0.250000;,
  0.150000;0.000000;,
  0.150000;0.250000;,
  0.200000;0.000000;,
  0.200000;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.300000;0.000000;,
  0.300000;0.250000;,
  0.350000;0.000000;,
  0.350000;0.250000;,
  0.400000;0.000000;,
  0.400000;0.250000;,
  0.450000;0.000000;,
  0.450000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;;
 }
}
