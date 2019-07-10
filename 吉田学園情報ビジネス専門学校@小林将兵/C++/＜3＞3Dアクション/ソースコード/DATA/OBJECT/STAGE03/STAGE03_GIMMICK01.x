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
 297;
 -15.45085;47.55287;-8.79470;,
 -29.38930;40.45092;-8.79470;,
 -29.38930;40.45092;8.79470;,
 -15.45085;47.55287;8.79470;,
 -47.92980;38.68272;-9.04824;,
 -58.99140;27.62112;-9.04824;,
 -58.99140;27.62112;8.54116;,
 -47.92980;38.68272;8.54116;,
 -40.45085;29.38932;-8.79469;,
 -47.55285;15.45087;-8.79469;,
 -47.55285;15.45087;8.79471;,
 -40.45085;29.38932;8.79471;,
 -61.51315;3.12252;-9.04824;,
 -63.96030;-12.32833;-9.04824;,
 -63.96030;-12.32833;8.54116;,
 -61.51315;3.12252;8.54116;,
 -50.00000;0.00002;-8.79469;,
 -47.55285;-15.45083;-8.79469;,
 -47.55285;-15.45083;8.79471;,
 -50.00000;0.00002;8.79471;,
 -51.60055;-33.63033;-9.04824;,
 -44.49855;-47.56873;-9.04824;,
 -44.49855;-47.56873;8.54116;,
 -51.60055;-33.63033;8.54116;,
 -40.45085;-29.38923;-8.79469;,
 -29.38925;-40.45084;-8.79470;,
 -29.38925;-40.45084;8.79470;,
 -40.45085;-29.38923;8.79471;,
 -21.97830;-57.53753;-9.04825;,
 -8.03990;-64.63953;-9.04825;,
 -8.03990;-64.63953;8.54115;,
 -21.97830;-57.53753;8.54115;,
 -15.45085;-47.55283;-8.79470;,
 -0.00000;-49.99998;-8.79470;,
 0.00000;-49.99998;8.79470;,
 -15.45085;-47.55283;8.79470;,
 16.03890;-59.46738;-9.04825;,
 31.48975;-57.02019;-9.04825;,
 31.48975;-57.02019;8.54115;,
 16.03890;-59.46738;8.54115;,
 15.45085;-47.55283;-8.79470;,
 29.38925;-40.45084;-8.79470;,
 29.38925;-40.45084;8.79470;,
 15.45085;-47.55283;8.79470;,
 47.92980;-38.68268;-9.04826;,
 58.99140;-27.62108;-9.04826;,
 58.99140;-27.62108;8.54114;,
 47.92980;-38.68268;8.54114;,
 40.45085;-29.38923;-8.79471;,
 47.55285;-15.45083;-8.79471;,
 47.55285;-15.45083;8.79469;,
 40.45085;-29.38923;8.79469;,
 61.51311;-3.12248;-9.04826;,
 63.96030;12.32837;-9.04826;,
 63.96030;12.32837;8.54114;,
 61.51311;-3.12248;8.54114;,
 50.00000;0.00002;-8.79471;,
 47.55285;15.45087;-8.79471;,
 47.55285;15.45087;8.79469;,
 50.00000;0.00002;8.79469;,
 51.60055;33.63037;-9.04826;,
 44.49855;47.56877;-9.04826;,
 44.49855;47.56877;8.54114;,
 51.60055;33.63037;8.54114;,
 40.45085;29.38927;-8.79471;,
 29.38925;40.45087;-8.79470;,
 29.38925;40.45087;8.79470;,
 40.45085;29.38927;8.79469;,
 21.97830;57.53757;-9.04825;,
 8.03985;64.63952;-9.04825;,
 8.03985;64.63952;8.54115;,
 21.97830;57.53757;8.54115;,
 15.45085;47.55287;-8.79470;,
 -0.00000;50.00002;-8.79470;,
 0.00000;50.00002;8.79470;,
 15.45085;47.55287;8.79470;,
 -16.03890;59.46741;-9.04825;,
 -31.48975;57.02027;-9.04825;,
 -31.48975;57.02027;8.54115;,
 -16.03890;59.46741;8.54115;,
 -15.45085;47.55287;-8.79470;,
 -15.45085;47.55287;8.79470;,
 -29.38930;40.45092;8.79470;,
 -40.45085;29.38932;8.79471;,
 -10.05960;7.30877;12.18010;,
 -7.30875;10.05962;12.18010;,
 -47.55285;15.45087;8.79471;,
 -11.82580;3.84247;12.18010;,
 -50.00000;0.00002;8.79471;,
 -12.43435;0.00002;12.18010;,
 -47.55285;-15.45083;8.79471;,
 -11.82580;-3.84243;12.18010;,
 -40.45085;-29.38923;8.79471;,
 -10.05960;-7.30873;12.18010;,
 -29.38925;-40.45084;8.79470;,
 -7.30875;-10.05958;12.18010;,
 -15.45085;-47.55283;8.79470;,
 -3.84245;-11.82578;12.18010;,
 0.00000;-49.99998;8.79470;,
 0.00000;-12.43433;12.18010;,
 15.45085;-47.55283;8.79470;,
 3.84245;-11.82578;12.18010;,
 29.38925;-40.45084;8.79470;,
 7.30870;-10.05958;12.18010;,
 40.45085;-29.38923;8.79469;,
 10.05960;-7.30873;12.18010;,
 47.55285;-15.45083;8.79469;,
 11.82575;-3.84243;12.18010;,
 50.00000;0.00002;8.79469;,
 12.43435;0.00002;12.18010;,
 47.55285;15.45087;8.79469;,
 11.82575;3.84247;12.18010;,
 40.45085;29.38927;8.79469;,
 10.05960;7.30872;12.18010;,
 29.38925;40.45087;8.79470;,
 7.30870;10.05962;12.18010;,
 15.45085;47.55287;8.79470;,
 3.84245;11.82577;12.18010;,
 0.00000;50.00002;8.79470;,
 0.00000;12.43437;12.18010;,
 -15.45085;47.55287;8.79470;,
 -3.84245;11.82582;12.18010;,
 15.45085;47.55287;-8.79470;,
 29.38925;40.45087;-8.79470;,
 7.30870;10.05962;-12.18010;,
 3.84245;11.82577;-12.18010;,
 40.45085;29.38927;-8.79471;,
 10.05960;7.30872;-12.18010;,
 47.55285;15.45087;-8.79471;,
 11.82575;3.84247;-12.18010;,
 50.00000;0.00002;-8.79471;,
 12.43435;0.00002;-12.18010;,
 47.55285;-15.45083;-8.79471;,
 11.82575;-3.84243;-12.18010;,
 40.45085;-29.38923;-8.79471;,
 10.05960;-7.30873;-12.18010;,
 29.38925;-40.45084;-8.79470;,
 7.30870;-10.05958;-12.18010;,
 15.45085;-47.55283;-8.79470;,
 3.84245;-11.82578;-12.18010;,
 -0.00000;-49.99998;-8.79470;,
 -0.00000;-12.43433;-12.18010;,
 -15.45085;-47.55283;-8.79470;,
 -3.84245;-11.82578;-12.18010;,
 -29.38925;-40.45084;-8.79470;,
 -7.30875;-10.05958;-12.18010;,
 -40.45085;-29.38923;-8.79469;,
 -10.05960;-7.30873;-12.18010;,
 -47.55285;-15.45083;-8.79469;,
 -11.82580;-3.84243;-12.18010;,
 -50.00000;0.00002;-8.79469;,
 -12.43435;0.00002;-12.18010;,
 -47.55285;15.45087;-8.79469;,
 -11.82580;3.84247;-12.18010;,
 -40.45085;29.38932;-8.79469;,
 -10.05960;7.30877;-12.18010;,
 -29.38930;40.45092;-8.79470;,
 -7.30875;10.05962;-12.18010;,
 -15.45085;47.55287;-8.79470;,
 -3.84245;11.82582;-12.18010;,
 -0.00000;50.00002;-8.79470;,
 -0.00000;12.43437;-12.18010;,
 6.70640;7.30877;-8.12005;,
 4.11965;9.02342;-8.12005;,
 1.12965;9.85482;-8.12005;,
 -1.97095;9.72157;-8.12005;,
 -4.87865;8.63672;-8.12005;,
 -7.30875;6.70642;-8.12005;,
 -9.02340;4.11967;-8.12005;,
 -9.85480;1.12967;-8.12005;,
 -9.72155;-1.97093;-8.12005;,
 -8.63670;-4.87863;-8.12005;,
 -6.70640;-7.30873;-8.12005;,
 -4.11965;-9.02338;-8.12005;,
 -1.12965;-9.85478;-8.12005;,
 1.97095;-9.72153;-8.12005;,
 4.87860;-8.63668;-8.12005;,
 7.30870;-6.70638;-8.12005;,
 9.02340;-4.11963;-8.12005;,
 9.85480;-1.12963;-8.12005;,
 9.72155;1.97097;-8.12005;,
 8.63670;4.87867;-8.12005;,
 -8.63670;4.87867;8.12005;,
 -6.70640;7.30877;8.12005;,
 -9.72155;1.97097;8.12005;,
 -9.85480;-1.12963;8.12005;,
 -9.02340;-4.11963;8.12005;,
 -7.30875;-6.70638;8.12005;,
 -4.87865;-8.63668;8.12005;,
 -1.97095;-9.72153;8.12005;,
 1.12965;-9.85478;8.12005;,
 4.11965;-9.02338;8.12005;,
 6.70640;-7.30873;8.12005;,
 8.63670;-4.87863;8.12005;,
 9.72155;-1.97093;8.12005;,
 9.85480;1.12967;8.12005;,
 9.02340;4.11967;8.12005;,
 7.30870;6.70642;8.12005;,
 4.87860;8.63672;8.12005;,
 1.97095;9.72157;8.12005;,
 -1.12965;9.85482;8.12005;,
 -4.11965;9.02342;8.12005;,
 -5.44760;5.91482;4.06005;,
 -3.35320;7.30877;4.06005;,
 -7.00875;3.94192;4.06005;,
 -7.88385;1.58317;4.06005;,
 -7.98720;-0.93053;4.06005;,
 -7.30875;-3.35318;4.06005;,
 -5.91485;-5.44758;4.06005;,
 -3.94195;-7.00873;4.06005;,
 -1.58315;-7.88383;4.06005;,
 0.93055;-7.98718;4.06005;,
 3.35320;-7.30873;4.06005;,
 5.44760;-5.91483;4.06005;,
 7.00875;-3.94193;4.06005;,
 7.88385;-1.58313;4.06005;,
 7.98720;0.93057;4.06005;,
 7.30870;3.35322;4.06005;,
 5.91480;5.44762;4.06005;,
 3.94190;7.00877;4.06005;,
 1.58315;7.88387;4.06005;,
 -0.93055;7.98722;4.06005;,
 -2.25855;6.95102;0.00000;,
 0.00000;7.30877;0.00000;,
 -4.29595;5.91292;0.00000;,
 -7.00875;3.94192;4.06005;,
 -7.88385;1.58317;4.06005;,
 -5.91290;4.29597;0.00000;,
 -4.29595;5.91292;0.00000;,
 -7.98720;-0.93053;4.06005;,
 -6.95100;2.25852;0.00000;,
 -7.98720;-0.93053;4.06005;,
 -7.30875;-3.35318;4.06005;,
 -7.30875;0.00002;0.00000;,
 -6.95100;2.25852;0.00000;,
 -7.30875;-3.35318;4.06005;,
 -5.91485;-5.44758;4.06005;,
 -6.95105;-2.25848;0.00000;,
 -7.30875;0.00002;0.00000;,
 -5.91485;-5.44758;4.06005;,
 -3.94195;-7.00873;4.06005;,
 -5.91290;-4.29593;0.00000;,
 -6.95105;-2.25848;0.00000;,
 -1.58315;-7.88383;4.06005;,
 -4.29595;-5.91288;0.00000;,
 0.93055;-7.98718;4.06005;,
 -2.25855;-6.95098;0.00000;,
 3.35320;-7.30873;4.06005;,
 0.00000;-7.30873;-0.00000;,
 5.44760;-5.91483;4.06005;,
 2.25850;-6.95098;-0.00000;,
 7.00875;-3.94193;4.06005;,
 4.29595;-5.91288;-0.00000;,
 7.88385;-1.58313;4.06005;,
 5.91290;-4.29593;-0.00000;,
 7.98720;0.93057;4.06005;,
 6.95100;-2.25853;-0.00000;,
 7.98720;0.93057;4.06005;,
 7.30870;3.35322;4.06005;,
 7.30870;0.00002;-0.00000;,
 6.95100;-2.25853;-0.00000;,
 7.30870;3.35322;4.06005;,
 5.91480;5.44762;4.06005;,
 6.95100;2.25852;-0.00000;,
 7.30870;0.00002;-0.00000;,
 5.91480;5.44762;4.06005;,
 3.94190;7.00877;4.06005;,
 5.91290;4.29597;-0.00000;,
 6.95100;2.25852;-0.00000;,
 1.58315;7.88387;4.06005;,
 4.29595;5.91292;-0.00000;,
 2.25850;6.95102;-0.00000;,
 4.29595;5.91292;-0.00000;,
 0.93055;7.98722;-4.06005;,
 3.35320;7.30877;-4.06005;,
 -1.58315;7.88387;-4.06005;,
 -3.94195;7.00877;-4.06005;,
 -6.95100;2.25852;0.00000;,
 -5.91485;5.44762;-4.06005;,
 -7.30875;3.35322;-4.06005;,
 -6.95105;-2.25848;0.00000;,
 -7.98720;0.93057;-4.06005;,
 -7.88385;-1.58313;-4.06005;,
 -7.00875;-3.94193;-4.06005;,
 -5.44760;-5.91478;-4.06005;,
 -3.35320;-7.30873;-4.06005;,
 -0.93055;-7.98718;-4.06005;,
 1.58315;-7.88383;-4.06005;,
 3.94190;-7.00873;-4.06005;,
 6.95100;-2.25853;-0.00000;,
 5.91480;-5.44758;-4.06005;,
 7.30870;-3.35318;-4.06005;,
 6.95100;2.25852;-0.00000;,
 7.98720;-0.93053;-4.06005;,
 7.88385;1.58317;-4.06005;,
 7.00875;3.94192;-4.06005;,
 5.44760;5.91487;-4.06005;;
 
 220;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;1,8,5,4;,
 4;8,11,6,5;,
 4;11,2,7,6;,
 4;2,1,4,7;,
 4;9,16,13,12;,
 4;16,19,14,13;,
 4;19,10,15,14;,
 4;10,9,12,15;,
 4;17,24,21,20;,
 4;24,27,22,21;,
 4;27,18,23,22;,
 4;18,17,20,23;,
 4;25,32,29,28;,
 4;32,35,30,29;,
 4;35,26,31,30;,
 4;26,25,28,31;,
 4;33,40,37,36;,
 4;40,43,38,37;,
 4;43,34,39,38;,
 4;34,33,36,39;,
 4;41,48,45,44;,
 4;48,51,46,45;,
 4;51,42,47,46;,
 4;42,41,44,47;,
 4;49,56,53,52;,
 4;56,59,54,53;,
 4;59,50,55,54;,
 4;50,49,52,55;,
 4;57,64,61,60;,
 4;64,67,62,61;,
 4;67,58,63,62;,
 4;58,57,60,63;,
 4;65,72,69,68;,
 4;72,75,70,69;,
 4;75,66,71,70;,
 4;66,65,68,71;,
 4;73,80,77,76;,
 4;80,81,78,77;,
 4;81,74,79,78;,
 4;74,73,76,79;,
 4;82,83,84,85;,
 4;83,86,87,84;,
 4;86,88,89,87;,
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
 4;120,82,85,121;,
 4;122,123,124,125;,
 4;123,126,127,124;,
 4;126,128,129,127;,
 4;128,130,131,129;,
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
 4;160,122,125,161;,
 4;162,163,124,127;,
 4;163,164,125,124;,
 4;164,165,161,125;,
 4;165,166,159,161;,
 4;166,167,157,159;,
 4;167,168,155,157;,
 4;168,169,153,155;,
 4;169,170,151,153;,
 4;170,171,149,151;,
 4;171,172,147,149;,
 4;172,173,145,147;,
 4;173,174,143,145;,
 4;174,175,141,143;,
 4;175,176,139,141;,
 4;176,177,137,139;,
 4;177,178,135,137;,
 4;178,179,133,135;,
 4;179,180,131,133;,
 4;180,181,129,131;,
 4;181,162,127,129;,
 4;84,87,182,183;,
 4;87,89,184,182;,
 4;89,91,185,184;,
 4;91,93,186,185;,
 4;93,95,187,186;,
 4;95,97,188,187;,
 4;97,99,189,188;,
 4;99,101,190,189;,
 4;101,103,191,190;,
 4;103,105,192,191;,
 4;105,107,193,192;,
 4;107,109,194,193;,
 4;109,111,195,194;,
 4;111,113,196,195;,
 4;113,115,197,196;,
 4;115,117,198,197;,
 4;117,119,199,198;,
 4;119,121,200,199;,
 4;121,85,201,200;,
 4;85,84,183,201;,
 4;183,182,202,203;,
 4;182,184,204,202;,
 4;184,185,205,204;,
 4;185,186,206,205;,
 4;186,187,207,206;,
 4;187,188,208,207;,
 4;188,189,209,208;,
 4;189,190,210,209;,
 4;190,191,211,210;,
 4;191,192,212,211;,
 4;192,193,213,212;,
 4;193,194,214,213;,
 4;194,195,215,214;,
 4;195,196,216,215;,
 4;196,197,217,216;,
 4;197,198,218,217;,
 4;198,199,219,218;,
 4;199,200,220,219;,
 4;200,201,221,220;,
 4;201,183,203,221;,
 4;203,202,222,223;,
 4;202,204,224,222;,
 4;225,226,227,228;,
 4;226,229,230,227;,
 4;231,232,233,234;,
 4;235,236,237,238;,
 4;239,240,241,242;,
 4;240,243,244,241;,
 4;243,245,246,244;,
 4;245,247,248,246;,
 4;247,249,250,248;,
 4;249,251,252,250;,
 4;251,253,254,252;,
 4;253,255,256,254;,
 4;257,258,259,260;,
 4;261,262,263,264;,
 4;265,266,267,268;,
 4;266,269,270,267;,
 4;220,221,271,272;,
 4;221,203,223,271;,
 4;223,222,273,274;,
 4;222,228,275,273;,
 4;228,227,276,275;,
 4;227,277,278,276;,
 4;277,233,279,278;,
 4;233,280,281,279;,
 4;280,241,282,281;,
 4;241,244,283,282;,
 4;244,246,284,283;,
 4;246,248,285,284;,
 4;248,250,286,285;,
 4;250,252,287,286;,
 4;252,254,288,287;,
 4;254,289,290,288;,
 4;289,264,291,290;,
 4;264,292,293,291;,
 4;292,267,294,293;,
 4;267,270,295,294;,
 4;270,271,296,295;,
 4;271,223,274,296;,
 4;274,273,163,162;,
 4;273,275,164,163;,
 4;275,276,165,164;,
 4;276,278,166,165;,
 4;278,279,167,166;,
 4;279,281,168,167;,
 4;281,282,169,168;,
 4;282,283,170,169;,
 4;283,284,171,170;,
 4;284,285,172,171;,
 4;285,286,173,172;,
 4;286,287,174,173;,
 4;287,288,175,174;,
 4;288,290,176,175;,
 4;290,291,177,176;,
 4;291,293,178,177;,
 4;293,294,179,178;,
 4;294,295,180,179;,
 4;295,296,181,180;,
 4;296,274,162,181;;
 
 MeshMaterialList {
  1;
  220;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "�S_�f��.jpg";
   }
  }
 }
 MeshNormals {
  290;
  -0.453988;0.891008;0.000000;,
  -0.279390;0.960178;0.000000;,
  -0.891006;0.453991;0.000000;,
  -0.790410;0.612578;0.000000;,
  -0.987689;-0.156433;0.000000;,
  -0.999520;0.030995;0.000000;,
  -0.707107;-0.707107;0.000000;,
  -0.826847;-0.562427;0.000000;,
  -0.156433;-0.987689;0.000000;,
  -0.338346;-0.941022;0.000000;,
  0.453992;-0.891006;-0.000000;,
  0.279391;-0.960177;-0.000000;,
  0.891006;-0.453992;-0.000000;,
  0.790410;-0.612578;-0.000000;,
  0.987689;0.156433;0.000000;,
  0.999520;-0.030995;-0.000000;,
  0.707107;0.707107;0.000000;,
  0.826847;0.562427;0.000000;,
  0.156433;0.987689;-0.000000;,
  0.338346;0.941022;-0.000000;,
  -0.426157;0.904649;0.000000;,
  -0.707107;0.707107;0.000000;,
  -0.876508;0.481388;0.000000;,
  -0.987689;0.156433;0.000000;,
  -0.992062;-0.125747;0.000000;,
  -0.891006;-0.453992;0.000000;,
  -0.728685;-0.684849;0.000000;,
  -0.453992;-0.891006;0.000000;,
  -0.186972;-0.982365;0.000000;,
  0.156436;-0.987688;-0.000000;,
  0.426155;-0.904650;-0.000000;,
  0.707107;-0.707107;-0.000000;,
  0.876507;-0.481388;-0.000000;,
  0.987688;-0.156436;-0.000000;,
  0.992062;0.125747;0.000000;,
  0.891006;0.453992;0.000000;,
  0.728683;0.684851;-0.000000;,
  0.453988;0.891008;-0.000000;,
  0.186974;0.982365;-0.000000;,
  -0.156433;0.987689;0.000000;,
  -0.052757;0.072614;0.995964;,
  -0.072614;0.052757;0.995964;,
  -0.085363;0.027736;0.995964;,
  -0.089756;0.000000;0.995964;,
  -0.085363;-0.027736;0.995964;,
  -0.072614;-0.052757;0.995964;,
  -0.052757;-0.072614;0.995964;,
  -0.027736;-0.085363;0.995964;,
  0.000000;-0.089756;0.995964;,
  0.027736;-0.085363;0.995964;,
  0.052757;-0.072614;0.995964;,
  0.072614;-0.052757;0.995964;,
  0.085363;-0.027736;0.995964;,
  0.089756;0.000000;0.995964;,
  0.085363;0.027736;0.995964;,
  0.072614;0.052757;0.995964;,
  0.052757;0.072614;0.995964;,
  0.027736;0.085363;0.995964;,
  0.000000;0.089756;0.995964;,
  -0.027736;0.085363;0.995964;,
  0.027736;0.085363;-0.995964;,
  0.052757;0.072614;-0.995964;,
  0.072614;0.052757;-0.995964;,
  0.085363;0.027736;-0.995964;,
  0.089756;0.000000;-0.995964;,
  0.085363;-0.027736;-0.995964;,
  0.072614;-0.052757;-0.995964;,
  0.052757;-0.072614;-0.995964;,
  0.027736;-0.085363;-0.995964;,
  -0.000000;-0.089756;-0.995964;,
  -0.027736;-0.085363;-0.995964;,
  -0.052757;-0.072614;-0.995964;,
  -0.072614;-0.052757;-0.995964;,
  -0.085363;-0.027736;-0.995964;,
  -0.089756;0.000000;-0.995964;,
  -0.085363;0.027736;-0.995964;,
  -0.072614;0.052757;-0.995964;,
  -0.052757;0.072614;-0.995964;,
  -0.027736;0.085363;-0.995964;,
  0.000000;0.089756;-0.995964;,
  0.571983;-0.664246;0.481261;,
  0.749253;-0.454977;0.481266;,
  0.853178;-0.201178;0.481264;,
  0.873589;0.072313;0.481263;,
  0.808487;0.338726;0.481261;,
  0.664248;0.571982;0.481260;,
  0.454979;0.749253;0.481263;,
  0.201177;0.853179;0.481263;,
  -0.072314;0.873588;0.481263;,
  -0.338726;0.808488;0.481260;,
  -0.571983;0.664249;0.481259;,
  -0.749254;0.454980;0.481261;,
  -0.853179;0.201177;0.481262;,
  -0.873589;-0.072315;0.481261;,
  -0.808485;-0.338730;0.481262;,
  -0.664244;-0.571986;0.481261;,
  -0.454981;-0.749253;0.481261;,
  -0.201181;-0.853178;0.481262;,
  0.072313;-0.873588;0.481263;,
  0.338726;-0.808487;0.481262;,
  0.363496;-0.878830;0.309077;,
  0.617283;-0.723484;0.309082;,
  0.810639;-0.497329;0.309076;,
  0.924647;-0.222485;0.309077;,
  0.948144;0.074131;0.309075;,
  0.878833;0.363491;0.309073;,
  0.723488;0.617280;0.309079;,
  0.497326;0.810640;0.309079;,
  0.222485;0.924647;0.309078;,
  -0.074130;0.948145;0.309074;,
  -0.363494;0.878831;0.309076;,
  -0.617280;0.723487;0.309082;,
  -0.810639;0.497328;0.309079;,
  -0.924647;0.222485;0.309078;,
  -0.948142;-0.074138;0.309081;,
  -0.878828;-0.363499;0.309079;,
  -0.723491;-0.617278;0.309076;,
  -0.497331;-0.810639;0.309075;,
  -0.222485;-0.924647;0.309077;,
  0.074131;-0.948144;0.309075;,
  0.000001;-1.000000;-0.000001;,
  0.309022;-0.951055;0.000003;,
  0.587784;-0.809018;-0.000004;,
  0.809018;-0.587783;-0.000001;,
  0.951056;-0.309019;-0.000005;,
  1.000000;-0.000005;-0.000004;,
  0.951056;0.309018;0.000005;,
  0.809016;0.587786;0.000003;,
  0.587783;0.809018;0.000002;,
  0.309021;0.951055;-0.000003;,
  0.000001;1.000000;0.000001;,
  -0.309019;0.951056;0.000005;,
  -0.587783;0.809018;0.000001;,
  -0.809018;0.587784;0.000004;,
  -0.951058;0.309013;0.000005;,
  -1.000000;-0.000001;0.000001;,
  -0.951058;-0.309012;-0.000005;,
  -0.809019;-0.587783;-0.000003;,
  -0.587784;-0.809018;0.000000;,
  -0.309020;-0.951056;-0.000005;,
  -0.363494;-0.878831;-0.309076;,
  -0.074130;-0.948145;-0.309074;,
  0.222485;-0.924647;-0.309078;,
  0.497328;-0.810639;-0.309079;,
  0.723487;-0.617280;-0.309082;,
  0.878830;-0.363496;-0.309077;,
  0.948145;-0.074131;-0.309072;,
  0.924647;0.222486;-0.309076;,
  0.810638;0.497330;-0.309077;,
  0.617282;0.723487;-0.309080;,
  0.363496;0.878830;-0.309078;,
  0.074131;0.948144;-0.309075;,
  -0.222485;0.924647;-0.309077;,
  -0.497330;0.810639;-0.309075;,
  -0.723491;0.617279;-0.309075;,
  -0.878829;0.363499;-0.309077;,
  -0.948142;0.074139;-0.309081;,
  -0.924647;-0.222485;-0.309077;,
  -0.810640;-0.497327;-0.309078;,
  -0.617282;-0.723485;-0.309083;,
  -0.571984;-0.664249;-0.481257;,
  -0.338727;-0.808489;-0.481259;,
  -0.072315;-0.873589;-0.481261;,
  0.201176;-0.853179;-0.481263;,
  0.454979;-0.749253;-0.481263;,
  0.664248;-0.571982;-0.481260;,
  0.808487;-0.338726;-0.481262;,
  0.873588;-0.072313;-0.481263;,
  0.853178;0.201178;-0.481263;,
  0.749252;0.454978;-0.481265;,
  0.571983;0.664246;-0.481261;,
  0.338726;0.808487;-0.481262;,
  0.072313;0.873588;-0.481263;,
  -0.201179;0.853178;-0.481263;,
  -0.454981;0.749252;-0.481263;,
  -0.664243;0.571985;-0.481262;,
  -0.808485;0.338730;-0.481263;,
  -0.873590;0.072313;-0.481261;,
  -0.853179;-0.201176;-0.481262;,
  -0.749254;-0.454979;-0.481261;,
  -0.030174;0.043429;-0.998601;,
  -0.043429;0.030173;-0.998601;,
  0.015114;-0.015114;-0.999772;,
  0.094939;-0.995483;-0.000000;,
  -0.053474;0.040230;0.997759;,
  -0.040230;0.053474;0.997759;,
  -0.015114;0.015114;0.999772;,
  -0.049938;0.017399;-0.998601;,
  -0.052870;-0.001116;-0.998601;,
  0.021111;-0.003344;-0.999772;,
  0.661937;-0.749560;-0.000000;,
  -0.066908;0.001115;0.997759;,
  -0.063978;0.019615;0.997759;,
  -0.021111;0.003344;0.999772;,
  -0.050628;-0.015276;-0.998601;,
  -0.042117;-0.031979;-0.998601;,
  0.019044;0.009704;-0.999772;,
  0.976098;-0.217330;-0.000000;,
  -0.054785;-0.038425;0.997759;,
  -0.063288;-0.021736;0.997759;,
  -0.019044;-0.009704;0.999772;,
  -0.031980;-0.042117;-0.998601;,
  -0.015276;-0.050627;-0.998601;,
  0.009703;0.019044;-0.999772;,
  0.917424;0.397911;-0.000000;,
  -0.021736;-0.063289;0.997759;,
  -0.038425;-0.054785;0.997759;,
  -0.009703;-0.019044;0.999772;,
  -0.001116;-0.052870;-0.998601;,
  0.017399;-0.049938;-0.998601;,
  -0.003344;0.021111;-0.999772;,
  0.508324;0.861166;-0.000000;,
  0.019615;-0.063978;0.997759;,
  0.001115;-0.066908;0.997758;,
  0.003344;-0.021111;0.999772;,
  0.030173;-0.043429;-0.998601;,
  0.043429;-0.030173;-0.998601;,
  -0.015114;0.015114;-0.999772;,
  -0.094936;0.995483;0.000000;,
  0.053474;-0.040230;0.997759;,
  0.040230;-0.053474;0.997758;,
  0.015114;-0.015114;0.999772;,
  0.049937;-0.017399;-0.998601;,
  0.052870;0.001116;-0.998601;,
  -0.021111;0.003344;-0.999772;,
  -0.661937;0.749560;0.000000;,
  0.066908;-0.001115;0.997758;,
  0.063978;-0.019615;0.997758;,
  0.021111;-0.003344;0.999772;,
  0.050627;0.015276;-0.998601;,
  0.042117;0.031979;-0.998601;,
  -0.019044;-0.009704;-0.999772;,
  -0.976098;0.217330;0.000000;,
  0.054785;0.038425;0.997759;,
  0.063289;0.021736;0.997759;,
  0.019044;0.009704;0.999772;,
  0.031979;0.042117;-0.998601;,
  0.015276;0.050627;-0.998601;,
  -0.009704;-0.019044;-0.999772;,
  -0.917423;-0.397914;0.000000;,
  0.021737;0.063288;0.997759;,
  0.038425;0.054785;0.997758;,
  0.009704;0.019044;0.999772;,
  0.001116;0.052870;-0.998601;,
  -0.017399;0.049938;-0.998601;,
  0.003343;-0.021111;-0.999772;,
  -0.508326;-0.861165;0.000000;,
  -0.019615;0.063978;0.997759;,
  -0.001115;0.066908;0.997759;,
  -0.003343;0.021111;0.999772;,
  -0.428341;-0.731554;-0.530427;,
  -0.633439;-0.563387;-0.530424;,
  -0.181316;-0.828112;-0.530429;,
  0.083455;-0.843610;-0.530432;,
  0.340064;-0.776530;-0.530432;,
  0.563386;-0.633436;-0.530429;,
  0.731550;-0.428341;-0.530432;,
  0.828109;-0.181314;-0.530434;,
  0.843609;0.083458;-0.530433;,
  0.776530;0.340064;-0.530432;,
  0.633436;0.563386;-0.530429;,
  0.428341;0.731550;-0.530432;,
  0.181314;0.828110;-0.530434;,
  -0.083459;0.843609;-0.530433;,
  -0.340066;0.776528;-0.530433;,
  -0.563382;0.633438;-0.530431;,
  -0.731550;0.428342;-0.530432;,
  -0.828112;0.181315;-0.530429;,
  -0.843611;-0.083458;-0.530429;,
  -0.776532;-0.340067;-0.530426;,
  0.633436;-0.563386;0.530429;,
  0.776530;-0.340064;0.530432;,
  0.843609;-0.083458;0.530432;,
  0.828110;0.181314;0.530433;,
  0.731550;0.428341;0.530432;,
  0.563386;0.633436;0.530429;,
  0.340064;0.776530;0.530432;,
  0.083458;0.843609;0.530432;,
  -0.181315;0.828110;0.530433;,
  -0.428341;0.731552;0.530430;,
  -0.633437;0.563386;0.530427;,
  -0.776532;0.340065;0.530428;,
  -0.843611;0.083458;0.530430;,
  -0.828112;-0.181316;0.530430;,
  -0.731551;-0.428343;0.530429;,
  -0.563383;-0.633439;0.530429;,
  -0.340067;-0.776531;0.530429;,
  -0.083462;-0.843610;0.530430;,
  0.181314;-0.828110;0.530433;,
  0.428341;-0.731550;0.530432;;
  220;
  4;0,1,1,0;,
  4;20,21,21,20;,
  4;2,3,3,2;,
  4;22,23,23,22;,
  4;4,5,5,4;,
  4;24,25,25,24;,
  4;6,7,7,6;,
  4;26,27,27,26;,
  4;8,9,9,8;,
  4;28,29,29,28;,
  4;10,11,11,10;,
  4;30,31,31,30;,
  4;12,13,13,12;,
  4;32,33,33,32;,
  4;14,15,15,14;,
  4;34,35,35,34;,
  4;16,17,17,16;,
  4;36,37,37,36;,
  4;18,19,19,18;,
  4;38,39,39,38;,
  4;180,181,182,182;,
  4;183,183,183,183;,
  4;184,185,186,186;,
  4;1,1,20,20;,
  4;187,188,189,189;,
  4;190,190,190,190;,
  4;191,192,193,193;,
  4;3,3,22,22;,
  4;194,195,196,196;,
  4;197,197,197,197;,
  4;198,199,200,200;,
  4;5,5,24,24;,
  4;201,202,203,203;,
  4;204,204,204,204;,
  4;205,206,207,207;,
  4;7,7,26,26;,
  4;208,209,210,210;,
  4;211,211,211,211;,
  4;212,213,214,214;,
  4;9,9,28,28;,
  4;215,216,217,217;,
  4;218,218,218,218;,
  4;219,220,221,221;,
  4;11,11,30,30;,
  4;222,223,224,224;,
  4;225,225,225,225;,
  4;226,227,228,228;,
  4;13,13,32,32;,
  4;229,230,231,231;,
  4;232,232,232,232;,
  4;233,234,235,235;,
  4;15,15,34,34;,
  4;236,237,238,238;,
  4;239,239,239,239;,
  4;240,241,242,242;,
  4;17,17,36,36;,
  4;243,244,245,245;,
  4;246,246,246,246;,
  4;247,248,249,249;,
  4;19,19,38,38;,
  4;185,184,41,40;,
  4;184,192,42,41;,
  4;192,191,43,42;,
  4;191,199,44,43;,
  4;199,198,45,44;,
  4;198,206,46,45;,
  4;206,205,47,46;,
  4;205,213,48,47;,
  4;213,212,49,48;,
  4;212,220,50,49;,
  4;220,219,51,50;,
  4;219,227,52,51;,
  4;227,226,53,52;,
  4;226,234,54,53;,
  4;234,233,55,54;,
  4;233,241,56,55;,
  4;241,240,57,56;,
  4;240,248,58,57;,
  4;248,247,59,58;,
  4;247,185,40,59;,
  4;237,236,61,60;,
  4;236,230,62,61;,
  4;230,229,63,62;,
  4;229,223,64,63;,
  4;223,222,65,64;,
  4;222,216,66,65;,
  4;216,215,67,66;,
  4;215,209,68,67;,
  4;209,208,69,68;,
  4;208,202,70,69;,
  4;202,201,71,70;,
  4;201,195,72,71;,
  4;195,194,73,72;,
  4;194,188,74,73;,
  4;188,187,75,74;,
  4;187,181,76,75;,
  4;181,180,77,76;,
  4;180,244,78,77;,
  4;244,243,79,78;,
  4;243,237,60,79;,
  4;160,161,250,251;,
  4;161,162,252,250;,
  4;162,163,253,252;,
  4;163,164,254,253;,
  4;164,165,255,254;,
  4;165,166,256,255;,
  4;166,167,257,256;,
  4;167,168,258,257;,
  4;168,169,259,258;,
  4;169,170,260,259;,
  4;170,171,261,260;,
  4;171,172,262,261;,
  4;172,173,263,262;,
  4;173,174,264,263;,
  4;174,175,265,264;,
  4;175,176,266,265;,
  4;176,177,267,266;,
  4;177,178,268,267;,
  4;178,179,269,268;,
  4;179,160,251,269;,
  4;270,271,81,80;,
  4;271,272,82,81;,
  4;272,273,83,82;,
  4;273,274,84,83;,
  4;274,275,85,84;,
  4;275,276,86,85;,
  4;276,277,87,86;,
  4;277,278,88,87;,
  4;278,279,89,88;,
  4;279,280,90,89;,
  4;280,281,91,90;,
  4;281,282,92,91;,
  4;282,283,93,92;,
  4;283,284,94,93;,
  4;284,285,95,94;,
  4;285,286,96,95;,
  4;286,287,97,96;,
  4;287,288,98,97;,
  4;288,289,99,98;,
  4;289,270,80,99;,
  4;80,81,101,100;,
  4;81,82,102,101;,
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
  4;99,80,100,119;,
  4;100,101,121,120;,
  4;101,102,122,121;,
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
  4;119,100,120,139;,
  4;120,121,141,140;,
  4;121,122,142,141;,
  4;122,123,143,142;,
  4;123,124,144,143;,
  4;124,125,145,144;,
  4;125,126,146,145;,
  4;126,127,147,146;,
  4;127,128,148,147;,
  4;128,129,149,148;,
  4;129,130,150,149;,
  4;130,131,151,150;,
  4;131,132,152,151;,
  4;132,133,153,152;,
  4;133,134,154,153;,
  4;134,135,155,154;,
  4;135,136,156,155;,
  4;136,137,157,156;,
  4;137,138,158,157;,
  4;138,139,159,158;,
  4;139,120,140,159;,
  4;140,141,161,160;,
  4;141,142,162,161;,
  4;142,143,163,162;,
  4;143,144,164,163;,
  4;144,145,165,164;,
  4;145,146,166,165;,
  4;146,147,167,166;,
  4;147,148,168,167;,
  4;148,149,169,168;,
  4;149,150,170,169;,
  4;150,151,171,170;,
  4;151,152,172,171;,
  4;152,153,173,172;,
  4;153,154,174,173;,
  4;154,155,175,174;,
  4;155,156,176,175;,
  4;156,157,177,176;,
  4;157,158,178,177;,
  4;158,159,179,178;,
  4;159,140,160,179;;
 }
 MeshTextureCoords {
  297;
  0.375000;0.687500;,
  0.387500;0.687500;,
  0.245059;0.679962;,
  0.216732;0.679962;,
  0.387500;0.687500;,
  0.400000;0.687500;,
  0.400000;0.311560;,
  0.387500;0.311560;,
  0.400000;0.687500;,
  0.412500;0.687500;,
  0.301712;0.679962;,
  0.273386;0.679962;,
  0.412500;0.687500;,
  0.425000;0.687500;,
  0.425000;0.311560;,
  0.412500;0.311560;,
  0.425000;0.687500;,
  0.437500;0.687500;,
  0.358366;0.679962;,
  0.330039;0.679962;,
  0.437500;0.687500;,
  0.450000;0.687500;,
  0.450000;0.311560;,
  0.437500;0.311560;,
  0.450000;0.687500;,
  0.462500;0.687500;,
  0.415019;0.679962;,
  0.386693;0.679962;,
  0.462500;0.687500;,
  0.475000;0.687500;,
  0.475000;0.311560;,
  0.462500;0.311560;,
  0.475000;0.687500;,
  0.487500;0.687500;,
  0.471673;0.679962;,
  0.443346;0.679962;,
  0.487500;0.687500;,
  0.500000;0.687500;,
  0.500000;0.311560;,
  0.487500;0.311560;,
  0.500000;0.687500;,
  0.512500;0.687500;,
  0.528327;0.679962;,
  0.500000;0.679962;,
  0.512500;0.687500;,
  0.525000;0.687500;,
  0.525000;0.311560;,
  0.512500;0.311560;,
  0.525000;0.687500;,
  0.537500;0.687500;,
  0.584980;0.679962;,
  0.556653;0.679962;,
  0.537500;0.687500;,
  0.550000;0.687500;,
  0.550000;0.311560;,
  0.537500;0.311560;,
  0.550000;0.687500;,
  0.562500;0.687500;,
  0.641634;0.679962;,
  0.613307;0.679962;,
  0.562500;0.687500;,
  0.575000;0.687500;,
  0.575000;0.311560;,
  0.562500;0.311560;,
  0.575000;0.687500;,
  0.587500;0.687500;,
  0.698287;0.679962;,
  0.669960;0.679962;,
  0.587500;0.687500;,
  0.600000;0.687500;,
  0.600000;0.311560;,
  0.587500;0.311560;,
  0.600000;0.687500;,
  0.612500;0.687500;,
  0.754941;0.679962;,
  0.726614;0.679962;,
  0.612500;0.687500;,
  0.625000;0.687500;,
  0.625000;0.311560;,
  0.612500;0.311560;,
  0.625000;0.687500;,
  0.783267;0.679962;,
  0.786461;0.158259;,
  0.708126;0.085292;,
  0.604063;0.225304;,
  0.643230;0.261788;,
  0.609418;0.038444;,
  0.554709;0.201880;,
  0.500000;0.022302;,
  0.500000;0.193809;,
  0.390582;0.038444;,
  0.445291;0.201880;,
  0.291874;0.085292;,
  0.395937;0.225304;,
  0.213539;0.158259;,
  0.356770;0.261788;,
  0.163245;0.250203;,
  0.331623;0.307760;,
  0.145915;0.352124;,
  0.322958;0.358720;,
  0.163245;0.454045;,
  0.331623;0.409681;,
  0.213539;0.545989;,
  0.356770;0.455653;,
  0.291874;0.618956;,
  0.395937;0.492136;,
  0.390582;0.665804;,
  0.445291;0.515560;,
  0.500000;0.681946;,
  0.500000;0.523632;,
  0.609418;0.665804;,
  0.554709;0.515560;,
  0.708126;0.618956;,
  0.604063;0.492136;,
  0.786461;0.545989;,
  0.643231;0.455653;,
  0.836755;0.454045;,
  0.668378;0.409681;,
  0.854085;0.352124;,
  0.677042;0.358720;,
  0.836755;0.250203;,
  0.668377;0.307760;,
  0.648603;0.795466;,
  0.626409;0.751909;,
  0.563204;0.800954;,
  0.574301;0.822733;,
  0.591841;0.717341;,
  0.545921;0.783671;,
  0.548284;0.695147;,
  0.524142;0.772574;,
  0.500000;0.687500;,
  0.500000;0.768750;,
  0.451716;0.695147;,
  0.475858;0.772574;,
  0.408159;0.717341;,
  0.454079;0.783671;,
  0.373591;0.751909;,
  0.436796;0.800954;,
  0.351397;0.795466;,
  0.425699;0.822733;,
  0.343750;0.843750;,
  0.421875;0.846875;,
  0.351397;0.892034;,
  0.425699;0.871017;,
  0.373591;0.935591;,
  0.436796;0.892796;,
  0.408159;0.914560;,
  0.454079;0.854480;,
  0.451716;0.936754;,
  0.475858;0.865577;,
  0.500000;0.944401;,
  0.500000;0.869401;,
  0.548284;0.936754;,
  0.524142;0.865577;,
  0.591842;0.914560;,
  0.545921;0.854481;,
  0.626409;0.935592;,
  0.563205;0.892796;,
  0.648603;0.892034;,
  0.574301;0.871017;,
  0.656250;0.843750;,
  0.578125;0.846875;,
  0.545921;0.669087;,
  0.556694;0.681641;,
  0.561918;0.699153;,
  0.561080;0.719908;,
  0.554264;0.741876;,
  0.542136;0.762906;,
  0.525884;0.780938;,
  0.507097;0.794209;,
  0.487616;0.801420;,
  0.469348;0.801863;,
  0.454079;0.795496;,
  0.443306;0.782943;,
  0.438082;0.765431;,
  0.438919;0.744675;,
  0.445736;0.722707;,
  0.457864;0.701678;,
  0.474116;0.683645;,
  0.492902;0.670374;,
  0.512384;0.663164;,
  0.530652;0.662720;,
  0.569463;0.453735;,
  0.604063;0.467174;,
  0.528063;0.454671;,
  0.483916;0.469890;,
  0.441344;0.497903;,
  0.404513;0.535968;,
  0.377029;0.580359;,
  0.361583;0.626730;,
  0.359685;0.670542;,
  0.371523;0.707507;,
  0.395937;0.734006;,
  0.430537;0.747445;,
  0.471937;0.746509;,
  0.516084;0.731290;,
  0.558656;0.703277;,
  0.595487;0.665212;,
  0.622971;0.620821;,
  0.638417;0.574450;,
  0.640314;0.530638;,
  0.628477;0.493673;,
  0.584216;0.705589;,
  0.604063;0.709044;,
  0.556126;0.715532;,
  0.522541;0.737900;,
  0.486751;0.770503;,
  0.452257;0.810149;,
  0.422436;0.852958;,
  0.400208;0.894740;,
  0.387748;0.931404;,
  0.386277;0.959361;,
  0.395937;0.975876;,
  0.415784;0.979330;,
  0.443874;0.969387;,
  0.477459;0.947020;,
  0.513250;0.914417;,
  0.547744;0.874770;,
  0.577564;0.831961;,
  0.599792;0.790180;,
  0.612252;0.753516;,
  0.613723;0.725558;,
  0.598970;0.957443;,
  0.604063;0.950913;,
  0.584189;0.976394;,
  0.556126;0.659933;,
  0.522541;0.682301;,
  0.561167;0.950310;,
  0.584189;0.920795;,
  0.486751;0.714904;,
  0.532157;0.987503;,
  0.486751;0.642952;,
  0.452257;0.682598;,
  0.500000;0.956779;,
  0.532157;0.915551;,
  0.452257;0.610647;,
  0.422436;0.653456;,
  0.467843;0.926055;,
  0.500000;0.884827;,
  0.422436;0.768903;,
  0.400208;0.787727;,
  0.438833;0.908476;,
  0.467843;0.891720;,
  0.387748;0.804246;,
  0.415811;0.921774;,
  0.386277;0.816842;,
  0.401030;0.930312;,
  0.395937;0.824282;,
  0.395937;0.933254;,
  0.415784;0.825839;,
  0.401030;0.930312;,
  0.443874;0.821359;,
  0.415811;0.921774;,
  0.477459;0.811281;,
  0.438833;0.908476;,
  0.513250;0.796592;,
  0.467843;0.891720;,
  0.513250;0.714915;,
  0.547744;0.675268;,
  0.500000;0.884827;,
  0.467843;0.926055;,
  0.547744;0.747220;,
  0.577564;0.704411;,
  0.532157;0.915551;,
  0.500000;0.956779;,
  0.577564;0.776362;,
  0.599792;0.734581;,
  0.561167;0.950310;,
  0.532157;0.987503;,
  0.612252;0.697917;,
  0.584189;0.920795;,
  0.598970;0.957443;,
  0.584189;0.976394;,
  0.550184;0.562327;,
  0.545921;0.554504;,
  0.549534;0.519973;,
  0.544036;0.537342;,
  0.532157;0.859952;,
  0.534227;0.429585;,
  0.521068;0.505465;,
  0.467843;0.764169;,
  0.505847;0.550721;,
  0.490053;0.685230;,
  0.475233;0.690004;,
  0.462837;0.692127;,
  0.454079;0.691389;,
  0.449816;0.687864;,
  0.450466;0.681897;,
  0.455964;0.674072;,
  0.467843;0.764169;,
  0.465773;0.537603;,
  0.478932;0.474851;,
  0.532157;0.859952;,
  0.494153;0.400470;,
  0.509947;0.512575;,
  0.524767;0.501979;,
  0.537163;0.552867;;
 }
}
