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
 250;
 -5.06057;-10.90449;1.31273;,
 -4.31726;-10.90449;2.49702;,
 -3.91264;-3.62139;2.49702;,
 -4.58549;-3.62139;1.31273;,
 -3.15911;-10.90449;3.43582;,
 -2.86474;-3.62139;3.43582;,
 -1.69977;-10.90449;4.03934;,
 -1.54519;-3.62139;4.03934;,
 -0.08244;-10.90449;4.24733;,
 -0.08244;-3.62139;4.24733;,
 1.53602;-10.90449;4.03934;,
 1.38145;-3.62139;4.03934;,
 2.99537;-10.90449;3.43582;,
 2.70100;-3.62139;3.43582;,
 4.15239;-10.90449;2.49702;,
 3.74891;-3.62139;2.49702;,
 4.89684;-10.90449;1.31273;,
 4.42176;-3.62139;1.31273;,
 5.15257;-10.90449;-0.00000;,
 4.65361;-3.62139;-0.00000;,
 4.89684;-10.90449;-1.31273;,
 4.42176;-3.62139;-1.31273;,
 4.15239;-10.90449;-2.49702;,
 3.74891;-3.62139;-2.49702;,
 2.99537;-10.90449;-3.43582;,
 2.70100;-3.62139;-3.43582;,
 1.53602;-10.90449;-4.03934;,
 1.38145;-3.62139;-4.03934;,
 -0.08244;-10.90449;-4.24733;,
 -0.08244;-3.62139;-4.24733;,
 -1.69977;-10.90449;-4.03934;,
 -1.54519;-3.62139;-4.03934;,
 -3.15911;-10.90449;-3.43582;,
 -2.86474;-3.62139;-3.43582;,
 -4.31726;-10.90449;-2.49702;,
 -3.91264;-3.62139;-2.49702;,
 -5.06057;-10.90449;-1.31273;,
 -4.58549;-3.62139;-1.31273;,
 -5.31630;-10.90449;0.00000;,
 -4.81735;-3.62139;0.00000;,
 -5.06057;-10.90449;1.31273;,
 -4.58549;-3.62139;1.31273;,
 -3.79330;-23.98402;2.49702;,
 -4.44569;-23.98402;1.31273;,
 -0.08244;-23.98402;0.00000;,
 -2.77836;-23.98402;3.43582;,
 -1.49973;-23.98402;4.03934;,
 -0.08244;-23.98402;4.24733;,
 1.33599;-23.98402;4.03934;,
 2.61462;-23.98402;3.43582;,
 3.62957;-23.98402;2.49702;,
 4.28196;-23.98402;1.31273;,
 4.50586;-23.98402;-0.00000;,
 4.28196;-23.98402;-1.31273;,
 3.62957;-23.98402;-2.49702;,
 2.61462;-23.98402;-3.43582;,
 1.33599;-23.98402;-4.03934;,
 -0.08244;-23.98402;-4.24733;,
 -1.49973;-23.98402;-4.03934;,
 -2.77836;-23.98402;-3.43582;,
 -3.79330;-23.98402;-2.49702;,
 -4.44569;-23.98402;-1.31273;,
 -4.66960;-23.98402;0.00000;,
 -4.58549;-3.62139;1.31273;,
 -3.91264;-3.62139;2.49702;,
 -0.08244;-3.62139;0.00000;,
 -2.86474;-3.62139;3.43582;,
 -1.54519;-3.62139;4.03934;,
 -0.08244;-3.62139;4.24733;,
 1.38145;-3.62139;4.03934;,
 2.70100;-3.62139;3.43582;,
 3.74891;-3.62139;2.49702;,
 4.42176;-3.62139;1.31273;,
 4.65361;-3.62139;-0.00000;,
 4.42176;-3.62139;-1.31273;,
 3.74891;-3.62139;-2.49702;,
 2.70100;-3.62139;-3.43582;,
 1.38145;-3.62139;-4.03934;,
 -0.08244;-3.62139;-4.24733;,
 -1.54519;-3.62139;-4.03934;,
 -2.86474;-3.62139;-3.43582;,
 -3.91264;-3.62139;-2.49702;,
 -4.58549;-3.62139;-1.31273;,
 -4.81735;-3.62139;0.00000;,
 -4.44569;-23.98402;1.31273;,
 -3.79330;-23.98402;2.49702;,
 -4.35023;-17.07259;2.49702;,
 -5.09353;-17.16805;1.31273;,
 -2.77836;-23.98402;3.43582;,
 -3.18525;-16.99531;3.43582;,
 -1.49973;-23.98402;4.03934;,
 -1.71454;-16.94303;4.03934;,
 -0.08244;-23.98402;4.24733;,
 -0.08017;-16.92144;4.24733;,
 1.33599;-23.98402;4.03934;,
 1.55421;-16.93169;4.03934;,
 2.61462;-23.98402;3.43582;,
 3.02606;-16.97255;3.43582;,
 3.62957;-23.98402;2.49702;,
 4.19103;-17.04075;2.49702;,
 4.28196;-23.98402;1.31273;,
 4.93548;-17.13054;1.31273;,
 4.50586;-23.98402;-0.00000;,
 5.18667;-17.23059;-0.00000;,
 4.28196;-23.98402;-1.31273;,
 4.92185;-17.33402;-1.31273;,
 3.62957;-23.98402;-2.49702;,
 4.16945;-17.42832;-2.49702;,
 2.61462;-23.98402;-3.43582;,
 3.00446;-17.50562;-3.43582;,
 1.33599;-23.98402;-4.03934;,
 1.54057;-17.55792;-4.03934;,
 -0.08244;-23.98402;-4.24733;,
 -0.08017;-17.58063;-4.24733;,
 -1.49973;-23.98402;-4.03934;,
 -1.70090;-17.57040;-4.03934;,
 -2.77836;-23.98402;-3.43582;,
 -3.16365;-17.52947;-3.43582;,
 -3.79330;-23.98402;-2.49702;,
 -4.32862;-17.46015;-2.49702;,
 -4.44569;-23.98402;-1.31273;,
 -5.07989;-17.37153;-1.31273;,
 -4.66960;-23.98402;0.00000;,
 -5.34471;-17.27036;0.00000;,
 -4.44569;-23.98402;1.31273;,
 -5.09353;-17.16805;1.31273;,
 -1.27469;-7.12087;0.38757;,
 -1.09511;-7.12087;0.73763;,
 -2.73972;-5.64331;1.93215;,
 -3.20684;-5.64331;1.01609;,
 -0.81779;-7.12087;1.01609;,
 -2.01232;-5.64331;2.65955;,
 -0.46887;-7.12087;1.19453;,
 -1.09511;-5.64331;3.12668;,
 -0.08017;-7.12087;1.25590;,
 -0.08017;-5.64331;3.28807;,
 0.30854;-7.12087;1.19453;,
 0.93592;-5.64331;3.12668;,
 0.65860;-7.12087;1.01609;,
 1.85199;-5.64331;2.65955;,
 0.93592;-7.12087;0.73763;,
 2.57939;-5.64331;1.93215;,
 1.11436;-7.12087;0.38757;,
 3.04652;-5.64331;1.01609;,
 1.17573;-7.12087;-0.00000;,
 3.20677;-5.64331;-0.00000;,
 1.11436;-7.12087;-0.38757;,
 3.04652;-5.64331;-1.01609;,
 0.93592;-7.12087;-0.73763;,
 2.57939;-5.64331;-1.93215;,
 0.65860;-7.12087;-1.01609;,
 1.85199;-5.64331;-2.65955;,
 0.30854;-7.12087;-1.19453;,
 0.93592;-5.64331;-3.12668;,
 -0.08017;-7.12087;-1.25590;,
 -0.08017;-5.64331;-3.28807;,
 -0.46887;-7.12087;-1.19453;,
 -1.09511;-5.64331;-3.12668;,
 -0.81779;-7.12087;-1.01609;,
 -2.01232;-5.64331;-2.65955;,
 -1.09511;-7.12087;-0.73763;,
 -2.73972;-5.64331;-1.93215;,
 -1.27469;-7.12087;-0.38757;,
 -3.20684;-5.64331;-1.01609;,
 -1.33493;-7.12087;0.00000;,
 -3.36596;-5.64331;0.00000;,
 -1.27469;-7.12087;0.38757;,
 -3.20684;-5.64331;1.01609;,
 -3.36596;-3.25541;2.38791;,
 -3.94447;-3.25541;1.25590;,
 -2.46808;-3.25541;3.28807;,
 -1.33493;-3.25541;3.86431;,
 -0.08017;-3.25541;4.06434;,
 1.17573;-3.25541;3.86431;,
 2.30775;-3.25541;3.28807;,
 3.20677;-3.25541;2.38791;,
 3.78529;-3.25541;1.25590;,
 3.98418;-3.25541;-0.00000;,
 3.78529;-3.25541;-1.25590;,
 3.20677;-3.25541;-2.38791;,
 2.30775;-3.25541;-3.28807;,
 1.17573;-3.25541;-3.86431;,
 -0.08017;-3.25541;-4.06434;,
 -1.33493;-3.25541;-3.86431;,
 -2.47035;-3.25541;-3.28807;,
 -3.36596;-3.25541;-2.38791;,
 -3.94447;-3.25541;-1.25590;,
 -4.14450;-3.25541;0.00000;,
 -3.94447;-3.25541;1.25590;,
 -2.73972;-0.86749;1.93215;,
 -3.20684;-0.86749;1.01609;,
 -2.01232;-0.86749;2.65955;,
 -1.09511;-0.86749;3.12668;,
 -0.08017;-0.86749;3.28807;,
 0.93592;-0.86749;3.12668;,
 1.85199;-0.86749;2.65955;,
 2.57939;-0.86749;1.93215;,
 3.04652;-0.86749;1.01609;,
 3.20677;-0.86749;-0.00000;,
 3.04652;-0.86749;-1.01609;,
 2.57939;-0.86749;-1.93215;,
 1.85199;-0.86749;-2.65955;,
 0.93592;-0.86749;-3.12668;,
 -0.08017;-0.86749;-3.28807;,
 -1.09511;-0.86749;-3.12668;,
 -2.01232;-0.86749;-2.65955;,
 -2.73972;-0.86749;-1.93215;,
 -3.20684;-0.86749;-1.01609;,
 -3.36596;-0.86749;0.00000;,
 -3.20684;-0.86749;1.01609;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;-7.31862;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;,
 -0.08017;0.80782;0.00000;;
 
 200;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 3;42,43,44;,
 3;45,42,44;,
 3;46,45,44;,
 3;47,46,44;,
 3;48,47,44;,
 3;49,48,44;,
 3;50,49,44;,
 3;51,50,44;,
 3;52,51,44;,
 3;53,52,44;,
 3;54,53,44;,
 3;55,54,44;,
 3;56,55,44;,
 3;57,56,44;,
 3;58,57,44;,
 3;59,58,44;,
 3;60,59,44;,
 3;61,60,44;,
 3;62,61,44;,
 3;43,62,44;,
 3;63,64,65;,
 3;64,66,65;,
 3;66,67,65;,
 3;67,68,65;,
 3;68,69,65;,
 3;69,70,65;,
 3;70,71,65;,
 3;71,72,65;,
 3;72,73,65;,
 3;73,74,65;,
 3;74,75,65;,
 3;75,76,65;,
 3;76,77,65;,
 3;77,78,65;,
 3;78,79,65;,
 3;79,80,65;,
 3;80,81,65;,
 3;81,82,65;,
 3;82,83,65;,
 3;83,63,65;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 4;87,86,1,0;,
 4;86,89,4,1;,
 4;89,91,6,4;,
 4;91,93,8,6;,
 4;93,95,10,8;,
 4;95,97,12,10;,
 4;97,99,14,12;,
 4;99,101,16,14;,
 4;101,103,18,16;,
 4;103,105,20,18;,
 4;105,107,22,20;,
 4;107,109,24,22;,
 4;109,111,26,24;,
 4;111,113,28,26;,
 4;113,115,30,28;,
 4;115,117,32,30;,
 4;117,119,34,32;,
 4;119,121,36,34;,
 4;121,123,38,36;,
 4;123,125,40,38;,
 4;126,127,128,129;,
 4;127,130,131,128;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;129,128,168,169;,
 4;128,131,170,168;,
 4;131,133,171,170;,
 4;133,135,172,171;,
 4;135,137,173,172;,
 4;137,139,174,173;,
 4;139,141,175,174;,
 4;141,143,176,175;,
 4;143,145,177,176;,
 4;145,147,178,177;,
 4;147,149,179,178;,
 4;149,151,180,179;,
 4;151,153,181,180;,
 4;153,155,182,181;,
 4;155,157,183,182;,
 4;157,159,184,183;,
 4;159,161,185,184;,
 4;161,163,186,185;,
 4;163,165,187,186;,
 4;165,167,188,187;,
 4;169,168,189,190;,
 4;168,170,191,189;,
 4;170,171,192,191;,
 4;171,172,193,192;,
 4;172,173,194,193;,
 4;173,174,195,194;,
 4;174,175,196,195;,
 4;175,176,197,196;,
 4;176,177,198,197;,
 4;177,178,199,198;,
 4;178,179,200,199;,
 4;179,180,201,200;,
 4;180,181,202,201;,
 4;181,182,203,202;,
 4;182,183,204,203;,
 4;183,184,205,204;,
 4;184,185,206,205;,
 4;185,186,207,206;,
 4;186,187,208,207;,
 4;187,188,209,208;,
 3;127,126,210;,
 3;130,127,211;,
 3;132,130,212;,
 3;134,132,213;,
 3;136,134,214;,
 3;138,136,215;,
 3;140,138,216;,
 3;142,140,217;,
 3;144,142,218;,
 3;146,144,219;,
 3;148,146,220;,
 3;150,148,221;,
 3;152,150,222;,
 3;154,152,223;,
 3;156,154,224;,
 3;158,156,225;,
 3;160,158,226;,
 3;162,160,227;,
 3;164,162,228;,
 3;166,164,229;,
 3;190,189,230;,
 3;189,191,231;,
 3;191,192,232;,
 3;192,193,233;,
 3;193,194,234;,
 3;194,195,235;,
 3;195,196,236;,
 3;196,197,237;,
 3;197,198,238;,
 3;198,199,239;,
 3;199,200,240;,
 3;200,201,241;,
 3;201,202,242;,
 3;202,203,243;,
 3;203,204,244;,
 3;204,205,245;,
 3;205,206,246;,
 3;206,207,247;,
 3;207,208,248;,
 3;208,209,249;;
 
 MeshMaterialList {
  1;
  200;
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
   0.511200;0.511200;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.421740;0.421740;0.421740;;
   TextureFilename {
    "data/MODEL/TEXTURE/MAHOUTUKAI.jpg";
   }
  }
 }
 MeshNormals {
  164;
  0.000000;-1.000000;0.000000;,
  -0.933823;0.059595;0.352737;,
  -0.762992;0.041903;0.645049;,
  -0.529511;0.021792;0.848023;,
  -0.269186;0.006811;0.963064;,
  -0.000049;0.001365;0.999999;,
  0.269138;0.006810;0.963078;,
  0.529612;0.021773;0.847960;,
  0.762960;0.041841;0.645091;,
  0.933764;0.059556;0.352898;,
  0.997772;0.066718;0.000000;,
  0.933764;0.059556;-0.352898;,
  0.762960;0.041841;-0.645091;,
  0.529612;0.021773;-0.847960;,
  0.269138;0.006810;-0.963078;,
  -0.000049;0.001365;-0.999999;,
  -0.269186;0.006811;-0.963064;,
  -0.529511;0.021792;-0.848023;,
  -0.762992;0.041903;-0.645049;,
  -0.933823;0.059595;-0.352737;,
  -0.997772;0.066718;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.932454;0.032186;0.359852;,
  -0.755717;0.022866;0.654499;,
  -0.519862;0.011985;0.854166;,
  -0.262660;0.003761;0.964881;,
  -0.000036;0.000769;1.000000;,
  0.262592;0.003846;0.964899;,
  0.519934;0.012176;0.854119;,
  0.755623;0.023175;0.654597;,
  0.932352;0.032605;0.360078;,
  0.999350;0.036015;-0.001336;,
  0.931659;0.031665;-0.361951;,
  0.755192;0.021942;-0.655136;,
  0.520114;0.011301;-0.854022;,
  0.262944;0.003519;-0.964805;,
  -0.000036;0.000696;-1.000000;,
  -0.263013;0.003442;-0.964786;,
  -0.520047;0.011128;-0.854065;,
  -0.755294;0.021658;-0.655028;,
  -0.931769;0.031264;-0.361702;,
  -0.999367;0.035553;-0.001319;,
  -0.932569;-0.041136;0.358640;,
  -0.757058;-0.028564;0.652723;,
  -0.521856;-0.014706;0.852907;,
  -0.264064;-0.004550;0.964495;,
  -0.000023;-0.000891;1.000000;,
  0.263994;-0.004528;0.964514;,
  0.521898;-0.014614;0.852883;,
  0.756984;-0.028349;0.652818;,
  0.932511;-0.040833;0.358825;,
  0.998921;-0.046428;-0.000755;,
  0.932212;-0.042172;-0.359446;,
  0.757374;-0.030156;-0.652285;,
  0.522934;-0.015916;-0.852224;,
  0.264870;-0.005017;-0.964271;,
  -0.000022;-0.001001;-0.999999;,
  -0.264939;-0.005025;-0.964252;,
  -0.522899;-0.015984;-0.852245;,
  -0.757455;-0.030342;-0.652182;,
  -0.932275;-0.042454;-0.359249;,
  -0.998906;-0.046750;-0.000744;,
  -0.363282;-0.924190;0.117895;,
  -0.309026;-0.924140;0.224652;,
  -0.224854;-0.924160;0.308820;,
  -0.118193;-0.924154;0.363276;,
  -0.000016;-0.924154;0.382021;,
  0.118075;-0.924154;0.363314;,
  0.224795;-0.924139;0.308923;,
  0.309238;-0.924120;0.224443;,
  0.363346;-0.924145;0.118046;,
  0.382092;-0.924124;-0.000000;,
  0.363346;-0.924145;-0.118046;,
  0.309238;-0.924120;-0.224443;,
  0.224795;-0.924139;-0.308923;,
  0.118075;-0.924154;-0.363314;,
  -0.000016;-0.924154;-0.382021;,
  -0.118193;-0.924154;-0.363276;,
  -0.224854;-0.924160;-0.308820;,
  -0.309026;-0.924140;-0.224652;,
  -0.363282;-0.924190;-0.117895;,
  -0.382245;-0.924061;0.000000;,
  -0.768868;-0.588605;0.249774;,
  -0.654060;-0.588439;0.475338;,
  -0.475438;-0.588545;0.653891;,
  -0.250024;-0.588491;0.768873;,
  -0.000056;-0.588554;0.808458;,
  0.250024;-0.588504;0.768863;,
  0.475449;-0.588479;0.653943;,
  0.654111;-0.588463;0.475237;,
  0.768812;-0.588624;0.249899;,
  0.808410;-0.588620;-0.000000;,
  0.768812;-0.588624;-0.249899;,
  0.654111;-0.588463;-0.475238;,
  0.475449;-0.588479;-0.653943;,
  0.250024;-0.588504;-0.768863;,
  -0.000056;-0.588554;-0.808458;,
  -0.249920;-0.588520;-0.768886;,
  -0.475430;-0.588668;-0.653786;,
  -0.654122;-0.588495;-0.475182;,
  -0.768868;-0.588605;-0.249774;,
  -0.808467;-0.588541;0.000000;,
  -0.951000;0.000029;0.309190;,
  -0.808982;-0.000001;0.587833;,
  -0.587848;0.000006;0.808972;,
  -0.309170;0.000001;0.951007;,
  -0.000079;-0.000006;1.000000;,
  0.309311;0.000007;0.950961;,
  0.587900;-0.000001;0.808934;,
  0.808884;-0.000019;0.587969;,
  0.950987;-0.000012;0.309230;,
  1.000000;-0.000001;-0.000000;,
  0.950987;-0.000012;-0.309230;,
  0.808884;-0.000019;-0.587969;,
  0.587900;-0.000001;-0.808934;,
  0.309311;0.000007;-0.950961;,
  -0.000079;-0.000006;-1.000000;,
  -0.308973;0.000011;-0.951071;,
  -0.587939;-0.000014;-0.808905;,
  -0.809173;-0.000031;-0.587571;,
  -0.951000;0.000029;-0.309190;,
  -1.000000;0.000060;0.000000;,
  -0.722081;0.650842;0.234528;,
  -0.614302;0.650659;0.446404;,
  -0.446295;0.650788;0.614244;,
  -0.234760;0.650769;0.722072;,
  -0.000063;0.650847;0.759209;,
  0.234861;0.650800;0.722011;,
  0.446369;0.650795;0.614183;,
  0.614181;0.650760;0.446422;,
  0.721982;0.650903;0.234663;,
  0.759152;0.650914;0.000000;,
  0.721982;0.650903;-0.234663;,
  0.614181;0.650760;-0.446422;,
  0.446369;0.650795;-0.614183;,
  0.234861;0.650800;-0.722011;,
  -0.000063;0.650847;-0.759209;,
  -0.234650;0.650802;-0.722078;,
  -0.446290;0.650891;-0.614138;,
  -0.614379;0.650688;-0.446255;,
  -0.722081;0.650842;-0.234528;,
  -0.759173;0.650889;0.000000;,
  -0.000029;-1.000000;0.000000;,
  -0.000003;1.000000;0.000000;,
  -0.932781;-0.086820;0.349830;,
  -0.765110;-0.060892;0.641013;,
  -0.533370;-0.031595;0.845291;,
  -0.271985;-0.009819;0.962251;,
  -0.000022;-0.001957;0.999998;,
  0.271934;-0.009946;0.962264;,
  0.533404;-0.031813;0.845262;,
  0.765085;-0.061142;0.641020;,
  0.932738;-0.087084;0.349880;,
  0.995203;-0.097829;0.001162;,
  0.933588;-0.087893;-0.347403;,
  0.766760;-0.062298;-0.638904;,
  0.535122;-0.032669;-0.844143;,
  0.272984;-0.010270;-0.961964;,
  -0.000021;-0.002031;-0.999998;,
  -0.273030;-0.010133;-0.961952;,
  -0.535090;-0.032439;-0.844172;,
  -0.766782;-0.062037;-0.638903;,
  -0.933624;-0.087622;-0.347375;,
  -0.995230;-0.097551;0.001150;;
  200;
  4;22,23,2,1;,
  4;23,24,3,2;,
  4;24,25,4,3;,
  4;25,26,5,4;,
  4;26,27,6,5;,
  4;27,28,7,6;,
  4;28,29,8,7;,
  4;29,30,9,8;,
  4;30,31,10,9;,
  4;31,32,11,10;,
  4;32,33,12,11;,
  4;33,34,13,12;,
  4;34,35,14,13;,
  4;35,36,15,14;,
  4;36,37,16,15;,
  4;37,38,17,16;,
  4;38,39,18,17;,
  4;39,40,19,18;,
  4;40,41,20,19;,
  4;41,22,1,20;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  4;144,145,43,42;,
  4;145,146,44,43;,
  4;146,147,45,44;,
  4;147,148,46,45;,
  4;148,149,47,46;,
  4;149,150,48,47;,
  4;150,151,49,48;,
  4;151,152,50,49;,
  4;152,153,51,50;,
  4;153,154,52,51;,
  4;154,155,53,52;,
  4;155,156,54,53;,
  4;156,157,55,54;,
  4;157,158,56,55;,
  4;158,159,57,56;,
  4;159,160,58,57;,
  4;160,161,59,58;,
  4;161,162,60,59;,
  4;162,163,61,60;,
  4;163,144,42,61;,
  4;42,43,23,22;,
  4;43,44,24,23;,
  4;44,45,25,24;,
  4;45,46,26,25;,
  4;46,47,27,26;,
  4;47,48,28,27;,
  4;48,49,29,28;,
  4;49,50,30,29;,
  4;50,51,31,30;,
  4;51,52,32,31;,
  4;52,53,33,32;,
  4;53,54,34,33;,
  4;54,55,35,34;,
  4;55,56,36,35;,
  4;56,57,37,36;,
  4;57,58,38,37;,
  4;58,59,39,38;,
  4;59,60,40,39;,
  4;60,61,41,40;,
  4;61,42,22,41;,
  4;62,63,83,82;,
  4;63,64,84,83;,
  4;64,65,85,84;,
  4;65,66,86,85;,
  4;66,67,87,86;,
  4;67,68,88,87;,
  4;68,69,89,88;,
  4;69,70,90,89;,
  4;70,71,91,90;,
  4;71,72,92,91;,
  4;72,73,93,92;,
  4;73,74,94,93;,
  4;74,75,95,94;,
  4;75,76,96,95;,
  4;76,77,97,96;,
  4;77,78,98,97;,
  4;78,79,99,98;,
  4;79,80,100,99;,
  4;80,81,101,100;,
  4;81,62,82,101;,
  4;82,83,103,102;,
  4;83,84,104,103;,
  4;84,85,105,104;,
  4;85,86,106,105;,
  4;86,87,107,106;,
  4;87,88,108,107;,
  4;88,89,109,108;,
  4;89,90,110,109;,
  4;90,91,111,110;,
  4;91,92,112,111;,
  4;92,93,113,112;,
  4;93,94,114,113;,
  4;94,95,115,114;,
  4;95,96,116,115;,
  4;96,97,117,116;,
  4;97,98,118,117;,
  4;98,99,119,118;,
  4;99,100,120,119;,
  4;100,101,121,120;,
  4;101,82,102,121;,
  4;102,103,123,122;,
  4;103,104,124,123;,
  4;104,105,125,124;,
  4;105,106,126,125;,
  4;106,107,127,126;,
  4;107,108,128,127;,
  4;108,109,129,128;,
  4;109,110,130,129;,
  4;110,111,131,130;,
  4;111,112,132,131;,
  4;112,113,133,132;,
  4;113,114,134,133;,
  4;114,115,135,134;,
  4;115,116,136,135;,
  4;116,117,137,136;,
  4;117,118,138,137;,
  4;118,119,139,138;,
  4;119,120,140,139;,
  4;120,121,141,140;,
  4;121,102,122,141;,
  3;63,62,142;,
  3;64,63,142;,
  3;65,64,142;,
  3;66,65,142;,
  3;67,66,142;,
  3;68,67,142;,
  3;69,68,142;,
  3;70,69,142;,
  3;71,70,142;,
  3;72,71,142;,
  3;73,72,142;,
  3;74,73,142;,
  3;75,74,142;,
  3;76,75,142;,
  3;77,76,142;,
  3;78,77,142;,
  3;79,78,142;,
  3;80,79,142;,
  3;81,80,142;,
  3;62,81,142;,
  3;122,123,143;,
  3;123,124,143;,
  3;124,125,143;,
  3;125,126,143;,
  3;126,127,143;,
  3;127,128,143;,
  3;128,129,143;,
  3;129,130,143;,
  3;130,131,143;,
  3;131,132,143;,
  3;132,133,143;,
  3;133,134,143;,
  3;134,135,143;,
  3;135,136,143;,
  3;136,137,143;,
  3;137,138,143;,
  3;138,139,143;,
  3;139,140,143;,
  3;140,141,143;,
  3;141,122,143;;
 }
 MeshTextureCoords {
  250;
  0.836250;0.304930;,
  0.837780;0.304930;,
  0.837780;0.288990;,
  0.836250;0.288990;,
  0.839300;0.304930;,
  0.839300;0.288990;,
  0.840830;0.304930;,
  0.840830;0.288990;,
  0.842350;0.304930;,
  0.842350;0.288990;,
  0.843880;0.304930;,
  0.843880;0.288990;,
  0.845400;0.304930;,
  0.845400;0.288990;,
  0.846930;0.304930;,
  0.846930;0.288990;,
  0.848460;0.304930;,
  0.848460;0.288990;,
  0.849980;0.304930;,
  0.849980;0.288990;,
  0.888370;0.304930;,
  0.888370;0.288990;,
  0.889900;0.304930;,
  0.889900;0.288990;,
  0.891420;0.304930;,
  0.891420;0.288990;,
  0.892950;0.304930;,
  0.892950;0.288990;,
  0.894470;0.304930;,
  0.894470;0.288990;,
  0.896000;0.304930;,
  0.896000;0.288990;,
  0.897530;0.304930;,
  0.897530;0.288990;,
  0.899050;0.304930;,
  0.899050;0.288990;,
  0.863720;0.304930;,
  0.863720;0.288990;,
  0.865240;0.304930;,
  0.865240;0.288990;,
  0.866770;0.304930;,
  0.866770;0.288990;,
  0.866940;0.333660;,
  0.906510;0.330540;,
  0.851510;0.327530;,
  0.862720;0.336140;,
  0.857400;0.337720;,
  0.851510;0.338270;,
  0.845620;0.337720;,
  0.840300;0.336140;,
  0.836080;0.333660;,
  0.870230;0.330540;,
  0.869300;0.327090;,
  0.870230;0.323630;,
  0.872940;0.320510;,
  0.877160;0.318040;,
  0.882480;0.316450;,
  0.888370;0.315900;,
  0.894260;0.316450;,
  0.899580;0.318040;,
  0.903800;0.320510;,
  0.906510;0.323630;,
  0.907440;0.327090;,
  0.906510;0.274410;,
  0.903800;0.271300;,
  0.888370;0.278320;,
  0.899580;0.268820;,
  0.894260;0.267230;,
  0.888370;0.266690;,
  0.882480;0.267230;,
  0.877160;0.268820;,
  0.872940;0.271300;,
  0.870230;0.274410;,
  0.869300;0.277870;,
  0.870230;0.281330;,
  0.872940;0.284440;,
  0.877160;0.286920;,
  0.882480;0.288510;,
  0.888370;0.289050;,
  0.894260;0.288510;,
  0.899580;0.286920;,
  0.903800;0.284440;,
  0.906510;0.281330;,
  0.907440;0.277870;,
  0.836250;0.315900;,
  0.837780;0.315900;,
  0.837780;0.310300;,
  0.836250;0.310400;,
  0.839300;0.315900;,
  0.839300;0.310210;,
  0.840830;0.315900;,
  0.840830;0.310160;,
  0.842350;0.315900;,
  0.842350;0.310130;,
  0.843880;0.315900;,
  0.843880;0.310140;,
  0.845400;0.315900;,
  0.845400;0.310190;,
  0.846930;0.315900;,
  0.846930;0.310260;,
  0.848460;0.315900;,
  0.848460;0.310360;,
  0.849980;0.315900;,
  0.849980;0.310470;,
  0.888370;0.315900;,
  0.888370;0.310580;,
  0.889900;0.315900;,
  0.889900;0.310690;,
  0.891420;0.315900;,
  0.891420;0.310770;,
  0.892950;0.315900;,
  0.892950;0.310830;,
  0.894470;0.315900;,
  0.894470;0.310850;,
  0.896000;0.315900;,
  0.896000;0.310840;,
  0.897530;0.315900;,
  0.897530;0.310800;,
  0.899050;0.315900;,
  0.899050;0.310720;,
  0.863720;0.315900;,
  0.863720;0.310620;,
  0.865240;0.315900;,
  0.865240;0.310510;,
  0.866770;0.315900;,
  0.866770;0.310400;,
  0.564150;0.534310;,
  0.568440;0.534310;,
  0.568440;0.517150;,
  0.564150;0.517150;,
  0.572720;0.534310;,
  0.572720;0.517150;,
  0.577010;0.534310;,
  0.577010;0.517150;,
  0.581300;0.534310;,
  0.581300;0.517150;,
  0.585590;0.534310;,
  0.585590;0.517150;,
  0.589880;0.534310;,
  0.589880;0.517150;,
  0.594170;0.534310;,
  0.594170;0.517150;,
  0.598460;0.534310;,
  0.598460;0.517150;,
  0.602750;0.534310;,
  0.602750;0.517150;,
  0.607030;0.534310;,
  0.607030;0.517150;,
  0.611320;0.534310;,
  0.611320;0.517150;,
  0.615610;0.534310;,
  0.615610;0.517150;,
  0.619900;0.534310;,
  0.619900;0.517150;,
  0.624190;0.534310;,
  0.624190;0.517150;,
  0.628480;0.534310;,
  0.628480;0.517150;,
  0.632770;0.534310;,
  0.632770;0.517150;,
  0.637060;0.534310;,
  0.637060;0.517150;,
  0.641350;0.534310;,
  0.641350;0.517150;,
  0.645630;0.534310;,
  0.645630;0.517150;,
  0.649920;0.534310;,
  0.649920;0.517150;,
  0.568440;0.500000;,
  0.564150;0.500000;,
  0.572720;0.500000;,
  0.577010;0.500000;,
  0.581300;0.500000;,
  0.585590;0.500000;,
  0.589880;0.500000;,
  0.594170;0.500000;,
  0.598460;0.500000;,
  0.602750;0.500000;,
  0.607030;0.500000;,
  0.611320;0.500000;,
  0.615610;0.500000;,
  0.619900;0.500000;,
  0.624190;0.500000;,
  0.628480;0.500000;,
  0.632770;0.500000;,
  0.637060;0.500000;,
  0.641350;0.500000;,
  0.645630;0.500000;,
  0.649920;0.500000;,
  0.568440;0.482850;,
  0.564150;0.482850;,
  0.572720;0.482850;,
  0.577010;0.482850;,
  0.581300;0.482850;,
  0.585590;0.482850;,
  0.589880;0.482850;,
  0.594170;0.482850;,
  0.598460;0.482850;,
  0.602750;0.482850;,
  0.607030;0.482850;,
  0.611320;0.482850;,
  0.615610;0.482850;,
  0.619900;0.482850;,
  0.624190;0.482850;,
  0.628480;0.482850;,
  0.632770;0.482850;,
  0.637060;0.482850;,
  0.641350;0.482850;,
  0.645630;0.482850;,
  0.649920;0.482850;,
  0.566290;0.542890;,
  0.570580;0.542890;,
  0.574870;0.542890;,
  0.579160;0.542890;,
  0.583450;0.542890;,
  0.587730;0.542890;,
  0.592020;0.542890;,
  0.596310;0.542890;,
  0.600600;0.542890;,
  0.604890;0.542890;,
  0.609180;0.542890;,
  0.613470;0.542890;,
  0.617760;0.542890;,
  0.622050;0.542890;,
  0.626330;0.542890;,
  0.630620;0.542890;,
  0.634910;0.542890;,
  0.639200;0.542890;,
  0.643490;0.542890;,
  0.647780;0.542890;,
  0.566290;0.457110;,
  0.570580;0.457110;,
  0.574870;0.457110;,
  0.579160;0.457110;,
  0.583450;0.457110;,
  0.587730;0.457110;,
  0.592020;0.457110;,
  0.596310;0.457110;,
  0.600600;0.457110;,
  0.604890;0.457110;,
  0.609180;0.457110;,
  0.613470;0.457110;,
  0.617760;0.457110;,
  0.622050;0.457110;,
  0.626330;0.457110;,
  0.630620;0.457110;,
  0.634910;0.457110;,
  0.639200;0.457110;,
  0.643490;0.457110;,
  0.647780;0.457110;;
 }
}
