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
 89;
 0.80320;-7.62960;-9.48720;,
 -0.49040;-7.58720;-10.11040;,
 1.38080;-7.18880;-13.47200;,
 -0.70000;-6.32320;-13.54640;,
 0.16640;-5.97920;-13.64400;,
 2.36320;-7.58720;-7.98800;,
 2.86720;-6.32320;-8.20240;,
 2.70400;-5.97200;-13.17360;,
 1.13280;-7.16400;-22.55040;,
 1.12000;-5.56640;-18.48480;,
 1.87600;-6.22480;-18.29040;,
 0.67120;-4.36960;-9.19440;,
 1.38000;-4.76560;-13.48880;,
 -0.50480;-4.99280;-9.76080;,
 0.30720;-0.34560;-5.98560;,
 0.46560;-2.67920;-7.37760;,
 -1.22800;-0.36720;-5.97200;,
 -2.13360;-4.32480;-8.52240;,
 2.23200;-0.54960;-5.98880;,
 2.28880;-1.38800;-6.85680;,
 -3.17440;-4.79600;-8.72240;,
 -2.76960;-0.72160;-5.95040;,
 -3.34400;-5.08800;-8.68560;,
 -2.97440;-1.29840;-5.93920;,
 -1.92400;3.27440;-0.15840;,
 -2.06640;2.59920;0.00720;,
 0.02560;2.56000;0.98240;,
 0.04000;2.99040;0.86800;,
 -2.66880;-0.26320;0.70880;,
 -2.10960;-2.15200;0.06480;,
 0.05040;-2.01680;1.19360;,
 -0.03520;0.73840;1.46640;,
 -4.06320;-6.32320;-8.53040;,
 -3.03760;-7.40400;-8.24160;,
 -2.77280;-5.01440;-5.87360;,
 -3.84000;-3.74480;-5.89440;,
 -0.80560;-5.44720;-5.88080;,
 -0.64960;-5.44240;-6.59200;,
 -2.28080;-7.92240;-8.74880;,
 2.11280;-2.13120;-1.01280;,
 -0.30000;-5.44560;-5.88560;,
 2.28880;-5.14560;-5.91520;,
 0.80320;-7.62960;-9.48720;,
 2.32080;-5.08640;-6.81440;,
 2.36320;-7.58720;-7.98800;,
 -0.49040;-7.58720;-10.11040;,
 2.93120;-3.74480;-6.92960;,
 2.98000;-3.74480;-5.95360;,
 2.28880;-5.14560;-5.91520;,
 2.32080;-5.08640;-6.81440;,
 2.11280;-2.13120;-1.01280;,
 2.52400;-0.40800;-0.46880;,
 -0.03520;0.73840;1.46640;,
 0.05040;-2.01680;1.19360;,
 2.03120;2.56960;-0.18493;,
 1.91440;3.27200;-0.31293;,
 0.04000;2.99040;0.86800;,
 0.02560;2.56000;0.98240;,
 2.28880;-1.38800;-6.85680;,
 2.23200;-0.54960;-5.98880;,
 2.37520;-1.16000;-5.98240;,
 2.41120;-1.83760;-6.87040;,
 -3.03760;-7.40400;-8.24160;,
 -4.06320;-6.32320;-8.53040;,
 -2.28080;-7.92240;-8.74880;,
 -4.18800;-6.46480;-10.64880;,
 -3.17840;-7.55120;-12.19840;,
 -1.69680;-6.46480;-13.01360;,
 -4.41600;-7.11040;-22.03280;,
 -3.98000;-5.60640;-16.96560;,
 -3.40400;-6.46480;-18.11680;,
 -2.13360;-4.32480;-8.52240;,
 -2.99760;-4.73840;-11.12800;,
 -3.17440;-4.79600;-8.72240;,
 -3.34400;-5.08800;-8.68560;,
 0.16640;-5.97920;-13.64400;,
 0.48320;-6.22960;-18.64160;,
 1.12160;-6.88880;-18.47680;,
 1.38080;-7.18880;-13.47200;,
 2.70400;-5.97200;-13.17360;,
 2.36320;-5.05920;-7.98800;,
 2.45920;-5.30000;-8.02960;,
 1.38000;-4.76560;-13.48880;,
 -4.18800;-6.46480;-10.64880;,
 -4.58400;-6.46480;-16.92560;,
 -4.13120;-7.18960;-17.86400;,
 -3.17840;-7.55120;-12.19840;,
 -1.69680;-6.46480;-13.01360;,
 -2.99760;-4.73840;-11.12800;;
 
 88;
 3;0,1,2;,
 3;1,3,2;,
 3;2,3,4;,
 3;5,0,6;,
 3;6,0,7;,
 3;7,0,2;,
 3;8,9,10;,
 3;11,12,13;,
 3;13,12,3;,
 3;3,12,4;,
 3;14,15,16;,
 3;16,15,17;,
 3;15,11,17;,
 3;17,11,13;,
 4;15,14,18,19;,
 4;17,20,21,16;,
 4;20,22,23,21;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 3;34,33,36;,
 3;36,33,37;,
 3;37,33,38;,
 3;30,29,39;,
 3;29,36,39;,
 3;39,36,40;,
 3;40,37,41;,
 3;37,42,41;,
 3;41,42,43;,
 3;43,42,44;,
 4;38,45,42,37;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 3;62,63,64;,
 3;63,65,64;,
 3;64,65,66;,
 3;64,66,1;,
 3;1,66,3;,
 3;3,66,67;,
 3;68,69,70;,
 3;71,72,73;,
 3;73,72,74;,
 3;74,72,63;,
 3;63,72,65;,
 4;75,76,77,78;,
 4;78,77,10,79;,
 3;80,81,11;,
 3;81,6,11;,
 3;6,7,11;,
 3;11,7,12;,
 4;82,9,76,75;,
 4;9,82,79,10;,
 3;76,8,77;,
 3;77,8,10;,
 3;9,8,76;,
 4;83,84,85,86;,
 4;86,85,70,87;,
 3;71,13,72;,
 3;13,3,72;,
 3;72,3,67;,
 4;88,69,84,83;,
 4;69,88,87,70;,
 3;84,68,85;,
 3;85,68,70;,
 3;69,68,84;,
 4;25,24,21,23;,
 4;34,29,28,35;,
 3;36,29,34;,
 3;36,37,40;,
 3;41,39,40;,
 4;47,51,50,48;,
 4;59,55,54,60;,
 4;61,60,47,46;,
 4;54,51,47,60;,
 4;51,54,57,52;,
 4;25,28,31,26;,
 4;35,28,25,23;,
 4;22,32,35,23;,
 4;11,15,19,80;,
 4;81,80,58,61;,
 4;6,81,61,46;,
 4;5,6,46,49;,
 4;24,16,21,55;,
 3;55,18,14;,
 4;55,14,16,24;,
 3;24,27,55;;
 
 MeshMaterialList {
  1;
  88;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\MODEL\\normal\\TEXTURE\\normalUV.jpg";
   }
  }
 }
 MeshNormals {
  100;
  0.028282;-0.996463;-0.079127;,
  0.648604;-0.371318;-0.664407;,
  -0.133734;0.933062;-0.333932;,
  0.526014;0.380531;-0.760595;,
  -0.645862;0.670516;-0.365062;,
  0.047659;0.276771;0.959754;,
  -0.267750;-0.653496;0.707992;,
  0.178053;-0.271024;0.945961;,
  0.742245;-0.356933;-0.567161;,
  -0.088299;0.790891;-0.605554;,
  -0.102039;0.810829;-0.576320;,
  0.492019;0.221518;0.841931;,
  -0.694765;0.209441;0.688067;,
  -0.704270;-0.696633;0.136770;,
  0.141236;-0.024852;0.989664;,
  -0.334697;-0.701889;0.628753;,
  -0.246844;-0.920546;0.302760;,
  0.344651;-0.786460;0.512538;,
  0.414776;-0.892556;0.176930;,
  -0.052009;-0.938265;-0.341986;,
  0.670936;0.690860;-0.269365;,
  -0.564427;-0.177530;0.806167;,
  0.145747;-0.927485;0.344282;,
  0.861735;-0.073543;0.502000;,
  0.584078;0.763064;-0.276742;,
  0.074047;-0.990341;-0.117222;,
  -0.148230;0.094018;-0.984474;,
  0.641492;-0.765756;-0.045896;,
  -0.532501;0.756966;-0.378742;,
  -0.717449;-0.696374;0.018170;,
  0.675814;0.706691;-0.209436;,
  -0.112806;-0.986347;-0.119980;,
  -0.689263;-0.719713;0.083241;,
  -0.483971;0.229480;-0.844459;,
  -0.762104;0.631338;-0.143562;,
  -0.783713;-0.618493;0.057094;,
  0.617880;0.746321;-0.247446;,
  -0.876868;0.407163;-0.255577;,
  -0.476445;-0.681917;0.554968;,
  0.034619;0.734350;-0.677888;,
  0.561618;-0.786016;0.258388;,
  0.008865;0.716843;-0.697178;,
  -0.030912;0.626546;-0.778771;,
  -0.978624;-0.103539;0.177696;,
  0.068548;-0.905851;0.418013;,
  0.060150;-0.961908;0.266674;,
  0.995278;-0.092610;0.029069;,
  0.624052;0.323791;-0.711139;,
  0.971196;0.219493;-0.092741;,
  0.524107;0.169903;0.834533;,
  0.071599;0.249199;0.965802;,
  -0.396391;0.271625;0.876980;,
  -0.925741;0.324930;-0.193453;,
  -0.873784;0.438589;-0.210096;,
  0.043088;0.587173;-0.808314;,
  0.314577;0.478559;-0.819770;,
  0.841599;0.279094;-0.462405;,
  0.995880;-0.049051;-0.076271;,
  0.888785;-0.420239;0.182920;,
  -0.039493;-0.179425;-0.982979;,
  -0.323157;0.165259;-0.931804;,
  -0.167998;0.932704;-0.319124;,
  0.578596;-0.806518;0.121470;,
  0.023775;-0.996981;0.073916;,
  -0.648842;-0.332254;0.684552;,
  0.956786;0.244017;-0.158168;,
  0.969348;0.217832;-0.113640;,
  -0.660997;-0.699690;-0.271142;,
  -0.468672;-0.023460;-0.883061;,
  -0.863533;0.488033;-0.127019;,
  -0.818882;0.573127;0.030934;,
  -0.711157;-0.702985;-0.008248;,
  0.666121;-0.745746;-0.012044;,
  0.709076;0.611309;-0.351444;,
  0.705785;0.613351;-0.354497;,
  0.669957;0.741971;-0.025224;,
  0.675915;0.735014;-0.053789;,
  -0.685753;0.705577;-0.178616;,
  -0.704768;0.705058;-0.078710;,
  -0.723181;-0.689219;0.044573;,
  0.652383;-0.756043;0.052870;,
  -0.659644;0.698800;-0.276674;,
  0.646169;-0.753479;-0.121384;,
  0.593779;-0.784039;-0.180856;,
  0.390834;0.881790;-0.263998;,
  -0.818078;0.574617;-0.023733;,
  0.650273;0.727875;-0.217585;,
  -0.819913;-0.570703;0.045172;,
  0.693897;-0.717483;-0.061036;,
  -0.815990;0.569553;-0.098839;,
  -0.962417;0.271006;-0.017564;,
  -0.962091;0.270199;-0.037051;,
  0.979171;0.191031;-0.068790;,
  0.979060;0.194198;-0.061064;,
  -0.962377;0.271711;0.001930;,
  0.791194;-0.267601;0.549911;,
  -0.898810;0.120933;0.421327;,
  0.028368;0.952861;-0.302079;,
  -0.004465;0.987884;-0.155127;,
  0.010582;0.968753;0.247801;;
  88;
  3;18,0,25;,
  3;0,19,25;,
  3;59,60,26;,
  3;1,1,8;,
  3;8,18,27;,
  3;27,18,25;,
  3;20,30,30;,
  3;9,28,2;,
  3;2,28,61;,
  3;60,28,26;,
  3;41,54,42;,
  3;42,54,10;,
  3;54,9,10;,
  3;10,9,2;,
  4;54,41,39,55;,
  4;10,4,37,42;,
  4;4,53,52,37;,
  4;12,51,50,5;,
  4;21,15,7,14;,
  4;13,6,38,43;,
  3;38,6,44;,
  3;44,62,22;,
  3;22,6,16;,
  3;63,63,17;,
  3;15,44,17;,
  3;17,44,45;,
  3;45,22,40;,
  3;22,18,40;,
  3;40,18,58;,
  3;64,64,64;,
  4;16,0,18,22;,
  4;57,46,40,58;,
  4;17,23,14,7;,
  4;49,11,5,50;,
  4;65,66,48,56;,
  3;67,13,67;,
  3;13,32,16;,
  3;16,32,31;,
  3;16,31,0;,
  3;0,31,19;,
  3;60,68,33;,
  3;24,36,36;,
  3;10,34,4;,
  3;4,34,53;,
  3;53,34,69;,
  3;69,34,70;,
  4;71,29,29,25;,
  4;25,72,72,27;,
  3;3,47,73;,
  3;47,74,73;,
  3;74,75,73;,
  3;73,75,76;,
  4;28,77,77,78;,
  4;30,76,75,30;,
  3;29,79,29;,
  3;72,80,72;,
  3;77,81,77;,
  4;32,35,35,31;,
  4;31,82,82,83;,
  3;10,2,84;,
  3;2,61,84;,
  3;34,60,33;,
  4;34,85,85,70;,
  4;36,84,86,36;,
  3;35,87,35;,
  3;82,88,82;,
  3;85,89,85;,
  4;90,91,37,52;,
  4;38,15,21,43;,
  3;44,15,38;,
  3;44,22,45;,
  3;40,17,45;,
  4;46,23,17,40;,
  4;66,92,93,48;,
  4;56,48,46,57;,
  4;93,23,46,48;,
  4;23,49,50,14;,
  4;51,21,14,50;,
  4;43,94,90,52;,
  4;53,69,43,52;,
  4;9,54,55,3;,
  4;47,3,55,56;,
  4;8,47,56,57;,
  4;95,95,57,58;,
  4;12,96,37,96;,
  3;97,39,41;,
  4;97,41,42,98;,
  3;98,99,97;;
 }
 MeshTextureCoords {
  89;
  0.107890;0.143360;,
  0.098480;0.143360;,
  0.107890;0.140630;,
  0.098480;0.133950;,
  0.101630;0.133950;,
  0.117310;0.143360;,
  0.117310;0.133950;,
  0.115030;0.133950;,
  0.713270;0.597730;,
  0.713270;0.574330;,
  0.738840;0.597730;,
  0.107890;0.124540;,
  0.107890;0.127280;,
  0.098480;0.124540;,
  0.107890;0.119890;,
  0.107890;0.121910;,
  0.102600;0.115130;,
  0.098480;0.115130;,
  0.117310;0.121790;,
  0.117310;0.122980;,
  0.098480;0.105710;,
  0.101530;0.105710;,
  0.098480;0.103920;,
  0.101420;0.103920;,
  0.107890;0.105710;,
  0.107890;0.103920;,
  0.117310;0.103920;,
  0.117310;0.105710;,
  0.107890;0.096300;,
  0.107890;0.086890;,
  0.117310;0.086890;,
  0.117310;0.096300;,
  0.098480;0.096300;,
  0.098480;0.086890;,
  0.101160;0.086890;,
  0.100990;0.096300;,
  0.107890;0.078480;,
  0.107890;0.077480;,
  0.098480;0.077480;,
  0.117310;0.077480;,
  0.109090;0.077480;,
  0.117310;0.070860;,
  0.107890;0.068070;,
  0.117310;0.069650;,
  0.117310;0.068070;,
  0.098480;0.068070;,
  0.118770;0.133950;,
  0.119890;0.133950;,
  0.120100;0.143360;,
  0.118890;0.143360;,
  0.126720;0.143360;,
  0.126720;0.133950;,
  0.136130;0.133950;,
  0.136130;0.143360;,
  0.126720;0.126330;,
  0.126720;0.124540;,
  0.136130;0.124540;,
  0.136130;0.126330;,
  0.118860;0.124540;,
  0.120050;0.124540;,
  0.120020;0.126330;,
  0.118840;0.126330;,
  0.079660;0.143360;,
  0.079660;0.133950;,
  0.089070;0.143360;,
  0.082760;0.133950;,
  0.089070;0.140470;,
  0.096150;0.133950;,
  0.585960;0.597730;,
  0.585960;0.573570;,
  0.608720;0.597730;,
  0.089070;0.124540;,
  0.089070;0.126760;,
  0.079660;0.124540;,
  0.079660;0.126330;,
  0.670890;0.597730;,
  0.691680;0.597730;,
  0.713270;0.621160;,
  0.713270;0.642910;,
  0.761560;0.597730;,
  0.117310;0.124540;,
  0.117310;0.126330;,
  0.713270;0.552630;,
  0.543310;0.597730;,
  0.565450;0.597730;,
  0.585960;0.618120;,
  0.585960;0.641830;,
  0.633830;0.597730;,
  0.585960;0.549140;;
 }
}
