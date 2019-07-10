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
 30;
 -0.40683;-0.45979;-1.69947;,
 -0.83806;-4.72617;-0.75585;,
 -1.06732;-4.72629;-0.12374;,
 -1.53237;-0.11478;-0.13483;,
 0.73888;-0.11478;-0.13483;,
 -0.62763;-4.72612;-0.12374;,
 -1.06732;-4.72629;-0.12374;,
 -0.83806;-4.72616;0.42716;,
 -0.40683;-0.39728;0.92767;,
 -1.53237;-0.11478;-0.13483;,
 -0.62763;-4.72612;-0.12374;,
 0.73888;-0.11478;-0.13483;,
 -0.31800;0.07704;-1.82717;,
 -0.31386;0.16451;1.04461;,
 -0.83806;-4.72616;0.42716;,
 -1.15683;-5.01506;-0.11745;,
 -0.83715;-5.02347;-0.99616;,
 -0.40684;-0.54148;-2.24337;,
 -2.08205;-0.12867;-0.12264;,
 -0.53084;-4.97544;-0.11691;,
 1.27642;-0.23080;-0.12509;,
 -0.40571;-0.47088;1.47272;,
 -0.83717;-5.01370;0.67311;,
 -1.15683;-5.01506;-0.11745;,
 -2.08205;-0.12867;-0.12264;,
 1.27642;-0.23080;-0.12509;,
 -0.53084;-4.97544;-0.11691;,
 -0.32739;-0.03817;-2.36488;,
 -0.31932;0.05909;1.58438;,
 -0.83717;-5.01370;0.67311;;
 
 18;
 4;0,1,2,3;,
 4;0,4,5,1;,
 4;6,7,8,9;,
 4;10,11,8,7;,
 3;12,0,3;,
 3;4,0,12;,
 3;9,8,13;,
 3;13,8,11;,
 4;1,5,14,2;,
 4;15,16,17,18;,
 4;19,20,17,16;,
 4;21,22,23,24;,
 4;21,25,26,22;,
 3;17,27,24;,
 3;17,25,27;,
 3;21,24,28;,
 3;21,28,25;,
 4;29,19,16,15;;
 
 MeshMaterialList {
  1;
  18;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game114\\Desktop\\2年生後期_3Dスクロールアクション\\素材\\MODEL\\PLAYER\\Nejiko.png";
   }
  }
 }
 MeshNormals {
  30;
  -0.690771;-0.036014;0.722176;,
  -0.812230;-0.004353;-0.583321;,
  -0.762869;-0.023445;0.646128;,
  0.960697;-0.267274;0.075011;,
  -0.850619;-0.037696;-0.524430;,
  0.786804;0.024686;0.616709;,
  0.831755;0.080681;0.549249;,
  0.868632;0.135893;0.476458;,
  0.693012;0.038711;-0.719886;,
  0.822656;0.119083;-0.555929;,
  0.762630;0.079396;-0.641944;,
  -0.954456;0.292917;-0.056683;,
  -0.965391;0.256658;-0.046335;,
  -0.826469;-0.010614;0.562883;,
  0.974805;-0.214717;0.060432;,
  -0.883858;-0.070810;-0.462364;,
  0.844808;-0.232538;-0.481898;,
  0.880002;-0.203970;-0.428943;,
  0.763291;-0.214856;0.609281;,
  0.827280;-0.172088;0.534784;,
  0.805508;-0.259977;-0.532512;,
  0.690545;-0.255159;0.676788;,
  0.000382;-1.000000;0.000009;,
  -0.820525;0.250819;0.513643;,
  -0.861920;0.238655;0.447369;,
  -0.758119;0.233659;-0.608818;,
  -0.822906;0.209272;-0.528234;,
  -0.773998;0.261414;0.576706;,
  -0.684775;0.255410;-0.682531;,
  -0.063151;0.997995;-0.004344;;
  18;
  4;4,15,15,4;,
  4;16,3,14,17;,
  4;13,13,2,2;,
  4;14,3,18,19;,
  3;1,4,4;,
  3;3,16,20;,
  3;2,2,0;,
  3;21,18,3;,
  4;22,22,22,22;,
  4;7,7,6,6;,
  4;12,11,23,24;,
  4;10,9,9,10;,
  4;25,11,12,26;,
  3;6,5,6;,
  3;23,11,27;,
  3;10,10,8;,
  3;25,28,11;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  30;
  0.218269;0.807688;,
  0.203665;0.990209;,
  0.250402;0.990216;,
  0.266470;0.791060;,
  0.169203;0.791060;,
  0.160769;0.990206;,
  0.342324;0.990216;,
  0.389060;0.990209;,
  0.374457;0.807688;,
  0.326256;0.791060;,
  0.431957;0.990206;,
  0.423523;0.791060;,
  0.214464;0.781815;,
  0.378439;0.780612;,
  0.203665;0.990209;,
  0.043040;0.980409;,
  0.038367;0.980408;,
  0.039827;0.973108;,
  0.044647;0.972442;,
  0.034077;0.980408;,
  0.034920;0.972442;,
  0.055446;0.973108;,
  0.056906;0.980408;,
  0.052232;0.980409;,
  0.050626;0.972442;,
  0.060352;0.972442;,
  0.061196;0.980408;,
  0.039446;0.972073;,
  0.055844;0.972024;,
  0.038367;0.980408;;
 }
}
