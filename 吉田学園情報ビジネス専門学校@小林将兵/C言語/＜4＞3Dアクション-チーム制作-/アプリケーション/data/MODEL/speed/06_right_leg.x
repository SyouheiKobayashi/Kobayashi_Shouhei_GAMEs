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
 104;
 1.99650;-19.03900;-9.17950;,
 1.31100;-18.64150;-9.98850;,
 3.02150;-12.79750;-10.31500;,
 6.18850;-8.41200;-8.33050;,
 1.94400;-19.13050;-8.99300;,
 3.98400;-13.85200;-7.32350;,
 1.41200;-20.57800;-6.04700;,
 1.96950;-19.52900;-8.18200;,
 3.97900;-14.61900;-5.79450;,
 2.80650;-16.82500;-1.30450;,
 1.51900;-20.01750;-7.18850;,
 3.03100;-15.64600;-3.70500;,
 0.80300;-20.40800;-6.39350;,
 1.52550;-16.46700;-2.03300;,
 0.14800;-20.17850;-6.86000;,
 0.14800;-15.98500;-3.01450;,
 -1.22250;-20.01750;-7.18850;,
 -2.73450;-15.64600;-3.70500;,
 -1.11600;-20.57800;-6.04700;,
 -2.51050;-16.82500;-1.30450;,
 -6.82950;-12.98350;-2.52850;,
 -4.44300;-17.96000;-1.93800;,
 -9.18050;-3.33450;4.76250;,
 -1.70000;-19.03900;-9.17950;,
 -1.64800;-19.13050;-8.99300;,
 -3.68800;-13.85200;-7.32350;,
 -5.89200;-8.41200;-8.33050;,
 -1.01500;-18.64150;-9.98850;,
 -2.72550;-12.79750;-10.31500;,
 0.14800;-18.49800;-10.28050;,
 0.14800;-6.70400;-11.86400;,
 1.31100;-18.64150;-9.98850;,
 3.02150;-12.79750;-10.31500;,
 1.99650;-19.03900;-9.17950;,
 1.94400;-19.13050;-8.99300;,
 1.31100;-18.64150;-9.98850;,
 1.96950;-19.52900;-8.18200;,
 1.41200;-20.57800;-6.04700;,
 1.51900;-20.01750;-7.18850;,
 0.80300;-20.40800;-6.39350;,
 0.14800;-18.49800;-10.28050;,
 0.14800;-20.17850;-6.86000;,
 -1.22250;-20.01750;-7.18850;,
 -1.01500;-18.64150;-9.98850;,
 -1.64800;-19.13050;-8.99300;,
 -1.11600;-20.57800;-6.04700;,
 -1.67350;-19.52900;-8.18200;,
 -1.70000;-19.03900;-9.17950;,
 2.46000;1.27250;-0.57550;,
 1.60300;1.76950;-1.58700;,
 2.39450;1.15750;-0.34200;,
 2.42650;0.65900;0.67300;,
 1.72950;-0.65300;3.34350;,
 1.86250;0.04850;1.91550;,
 0.96700;-0.44000;2.91000;,
 0.14800;1.94900;-1.95200;,
 0.14800;-0.15350;2.32600;,
 -1.30650;1.76950;-1.58700;,
 -1.56650;0.04850;1.91550;,
 -2.16400;1.27250;-0.57550;,
 -2.09850;1.15750;-0.34200;,
 -1.43300;-0.65300;3.34350;,
 -2.13050;0.65900;0.67300;,
 0.14800;-12.45050;-10.20750;,
 0.14800;0.84100;-5.77100;,
 3.35000;0.44600;-4.96700;,
 2.59400;-12.75250;-9.59350;,
 -2.29750;-12.75250;-9.59350;,
 -3.05400;0.44600;-4.96700;,
 -3.73900;-13.58800;-7.89300;,
 -4.94050;-0.64800;-2.74050;,
 -3.62900;-13.78100;-7.50000;,
 -4.79650;-0.90050;-2.22650;,
 -3.68300;-14.61900;-5.79450;,
 -4.86700;-1.99750;0.00700;,
 -3.33250;-4.88550;5.88500;,
 -3.62600;-3.34150;2.74250;,
 0.14800;-3.78550;3.64600;,
 1.95100;-4.41700;4.93100;,
 3.92200;-3.34150;2.74250;,
 3.62850;-4.88600;5.88500;,
 5.16350;-1.99750;0.00700;,
 3.92500;-13.78100;-7.50000;,
 5.09300;-0.90050;-2.22650;,
 4.03500;-13.58800;-7.89300;,
 5.23700;-0.64800;-2.74050;,
 2.59400;-12.75250;-9.59350;,
 3.35000;0.44600;-4.96700;,
 0.14800;0.84100;-5.77100;,
 3.35000;0.44600;-4.96700;,
 5.23700;-0.64800;-2.74050;,
 5.09300;-0.90050;-2.22650;,
 5.16350;-1.99750;0.00700;,
 3.62850;-4.88600;5.88500;,
 3.92200;-3.34150;2.74250;,
 1.95100;-4.41700;4.93100;,
 0.14800;-3.78550;3.64600;,
 -3.62600;-3.34150;2.74250;,
 -3.33250;-4.88550;5.88500;,
 -4.86700;-1.99750;0.00700;,
 -4.79650;-0.90050;-2.22650;,
 -4.94050;-0.64800;-2.74050;,
 -3.05400;0.44600;-4.96700;,
 -1.67350;-19.52900;-8.18200;;
 
 85;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,7,8,9;,
 4;10,6,9,11;,
 4;12,10,11,13;,
 4;14,12,13,15;,
 4;16,14,15,17;,
 4;18,16,17,19;,
 3;20,21,22;,
 4;23,24,25,26;,
 4;27,23,26,28;,
 4;29,27,28,30;,
 4;31,29,30,32;,
 3;33,34,35;,
 3;36,37,34;,
 3;34,37,38;,
 3;34,38,35;,
 3;38,39,35;,
 3;35,39,40;,
 3;39,41,40;,
 3;41,42,40;,
 3;40,42,43;,
 3;43,42,44;,
 3;45,46,42;,
 3;46,44,42;,
 3;44,47,43;,
 3;48,49,50;,
 3;51,50,52;,
 3;50,49,53;,
 3;53,49,54;,
 3;49,55,54;,
 3;54,55,56;,
 3;55,57,56;,
 3;56,57,58;,
 3;57,59,60;,
 3;57,60,58;,
 3;61,58,62;,
 3;58,60,62;,
 3;53,52,50;,
 4;63,64,65,66;,
 4;67,68,64,63;,
 4;69,70,68,67;,
 4;71,72,70,69;,
 4;73,74,72,71;,
 4;19,75,74,73;,
 4;17,76,75,19;,
 4;15,77,76,17;,
 4;13,78,77,15;,
 4;11,79,78,13;,
 4;9,80,79,11;,
 4;8,81,80,9;,
 4;82,83,81,8;,
 4;84,85,83,82;,
 4;86,87,85,84;,
 4;84,3,2,86;,
 4;82,5,3,84;,
 4;69,26,25,71;,
 4;67,28,26,69;,
 4;63,30,28,67;,
 4;66,32,30,63;,
 3;73,71,46;,
 3;25,24,71;,
 3;24,46,71;,
 3;34,5,7;,
 3;7,5,8;,
 3;5,82,8;,
 4;88,55,49,89;,
 4;89,49,48,90;,
 4;90,48,50,91;,
 4;91,50,51,92;,
 4;92,51,52,93;,
 4;93,52,53,94;,
 4;94,53,54,95;,
 4;95,54,56,96;,
 4;96,56,58,97;,
 4;97,58,61,98;,
 4;98,61,62,99;,
 4;99,62,60,100;,
 4;100,60,59,101;,
 4;101,59,57,102;,
 4;102,57,55,88;,
 4;103,20,22,73;,
 3;73,22,19;,
 4;19,22,21,18;,
 4;18,21,20,103;;
 
 MeshMaterialList {
  1;
  85;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\MODEL\\speed\\TEXTURE\\UV_speed.jpg";
   }
  }
 }
 MeshNormals {
  101;
  0.883296;-0.331381;-0.331626;,
  0.490811;-0.188814;-0.850561;,
  0.177728;-0.746464;-0.641252;,
  0.937540;-0.342256;-0.062286;,
  0.938805;-0.331776;-0.092577;,
  0.916818;-0.396824;0.044440;,
  0.952201;-0.285624;0.108316;,
  0.971025;-0.238977;-0.000216;,
  0.935767;-0.339215;-0.096295;,
  -0.955912;0.288943;0.052394;,
  -0.981066;0.193646;0.003336;,
  0.733234;-0.560449;0.385051;,
  0.761744;-0.452404;0.463764;,
  -0.435687;-0.608343;0.663397;,
  -0.444930;-0.521412;0.728126;,
  -0.248047;-0.654743;0.713992;,
  -0.254555;-0.562763;0.786448;,
  0.955963;0.288736;0.052596;,
  0.959714;0.280970;-0.002168;,
  -0.867363;-0.497453;0.014921;,
  -0.886277;-0.396642;0.239139;,
  -0.938872;-0.338762;-0.061308;,
  -0.925735;-0.374248;0.054345;,
  -0.883207;-0.331156;-0.332086;,
  -0.216284;-0.701852;-0.678694;,
  -0.490908;-0.188847;-0.850498;,
  -0.000033;-0.720898;-0.693041;,
  -0.000000;-0.128470;-0.991713;,
  -0.293080;-0.867930;-0.401002;,
  -0.000122;0.985967;0.166942;,
  0.129682;0.957615;0.257208;,
  0.462907;0.829309;0.312991;,
  0.254764;0.854714;0.452282;,
  0.491016;0.758927;0.427706;,
  0.239651;0.845156;0.477785;,
  0.136019;0.835264;0.532760;,
  0.007693;0.773323;0.633966;,
  -0.145197;0.727099;0.671003;,
  -0.038065;0.824542;0.564519;,
  -0.362805;0.795393;0.485513;,
  -0.371242;0.816314;0.442505;,
  -0.307838;0.837884;0.450762;,
  -0.462929;0.829303;0.312974;,
  -0.129625;0.957618;0.257226;,
  -0.000013;0.316613;-0.948555;,
  0.557433;0.246014;-0.792935;,
  0.524666;0.660875;-0.536628;,
  -0.000015;0.724576;-0.689195;,
  -0.557436;0.246013;-0.792933;,
  -0.524665;0.660874;-0.536630;,
  -0.974990;-0.002046;-0.222240;,
  -0.912096;0.409965;0.002968;,
  -0.976011;-0.210031;-0.057357;,
  -0.934475;0.259831;0.243400;,
  -0.972170;-0.079477;-0.220383;,
  -0.930452;0.276498;0.240434;,
  -0.909508;0.226324;0.348673;,
  0.947414;-0.243214;-0.207973;,
  -0.424659;-0.055997;0.903620;,
  -0.589357;-0.040746;0.806844;,
  0.719739;0.083534;0.689201;,
  -0.947432;-0.243163;-0.207952;,
  0.930453;0.276488;0.240440;,
  0.991187;-0.116040;0.063901;,
  0.934465;0.259857;0.243411;,
  0.974989;-0.002069;-0.222241;,
  0.912093;0.409973;0.002986;,
  -0.605934;-0.537657;0.586319;,
  -0.616536;-0.458666;0.639928;,
  0.981089;0.193525;0.003478;,
  -0.000580;-0.897706;-0.440594;,
  0.000751;-0.897609;-0.440792;,
  -0.000103;-0.897506;-0.441003;,
  0.001618;-0.897628;-0.440752;,
  0.001158;-0.897571;-0.440869;,
  -0.000217;-0.897506;-0.441002;,
  -0.000083;-0.897528;-0.440958;,
  -0.000474;-0.897534;-0.440945;,
  -0.000124;-0.897559;-0.440895;,
  -0.445221;-0.818369;-0.363387;,
  0.000581;-0.897707;-0.440593;,
  -0.970740;-0.169337;0.170259;,
  -0.240002;-0.069473;0.968283;,
  0.909520;0.226282;0.348669;,
  -0.843943;0.505045;0.180804;,
  -0.782716;0.597819;0.173110;,
  -0.630836;0.697513;0.339883;,
  0.843968;0.505029;0.180732;,
  0.902883;0.317280;0.290063;,
  0.782716;0.597853;0.172994;,
  0.000110;0.477360;0.878708;,
  -0.342605;0.448419;0.825556;,
  0.342811;0.448485;0.825434;,
  -0.910317;-0.128284;-0.393531;,
  0.894144;0.222695;0.388476;,
  -0.254565;0.864728;0.432945;,
  -0.764545;-0.547423;-0.340293;,
  0.764457;-0.547478;-0.340402;,
  -0.635101;0.242592;-0.733345;,
  0.893942;0.447984;-0.013340;,
  0.089910;-0.597729;0.796641;;
  85;
  4;0,2,1,0;,
  4;3,0,0,4;,
  4;5,8,7,6;,
  4;9,9,10,10;,
  4;11,11,12,12;,
  4;13,67,68,14;,
  4;15,13,14,16;,
  4;17,17,69,18;,
  3;19,19,20;,
  4;23,21,22,23;,
  4;24,23,23,25;,
  4;26,24,25,27;,
  4;2,26,27,1;,
  3;70,71,2;,
  3;72,73,71;,
  3;71,73,74;,
  3;71,74,2;,
  3;74,75,2;,
  3;2,75,26;,
  3;75,76,26;,
  3;76,77,26;,
  3;26,77,24;,
  3;24,77,78;,
  3;79,28,77;,
  3;28,78,77;,
  3;78,80,24;,
  3;31,30,32;,
  3;33,32,34;,
  3;32,30,35;,
  3;35,30,36;,
  3;30,29,36;,
  3;36,29,37;,
  3;29,43,37;,
  3;37,43,38;,
  3;43,42,41;,
  3;43,41,38;,
  3;39,38,40;,
  3;38,41,40;,
  3;35,34,32;,
  4;44,47,46,45;,
  4;48,49,47,44;,
  4;50,51,49,48;,
  4;52,53,51,50;,
  4;54,55,53,52;,
  4;81,56,55,54;,
  4;69,57,57,18;,
  4;14,58,82,16;,
  4;68,59,58,14;,
  4;12,60,60,12;,
  4;10,61,61,10;,
  4;7,62,83,6;,
  4;63,64,62,7;,
  4;65,66,64,63;,
  4;45,46,66,65;,
  4;84,84,85,85;,
  4;86,86,84,84;,
  4;87,87,88,88;,
  4;89,89,87,87;,
  4;90,90,91,91;,
  4;92,92,90,90;,
  3;54,52,93;,
  3;88,94,88;,
  3;21,93,52;,
  3;3,4,8;,
  3;8,4,7;,
  3;86,86,95;,
  4;47,29,30,46;,
  4;46,30,31,66;,
  4;66,31,32,64;,
  4;64,32,33,62;,
  4;62,33,34,83;,
  4;61,96,96,61;,
  4;60,35,36,60;,
  4;59,36,37,58;,
  4;58,37,38,82;,
  4;57,97,97,57;,
  4;56,39,40,55;,
  4;55,40,41,53;,
  4;53,41,42,51;,
  4;51,42,43,49;,
  4;49,43,29,47;,
  4;93,98,98,54;,
  3;99,99,18;,
  4;100,100,100,100;,
  4;79,19,19,28;;
 }
 MeshTextureCoords {
  104;
  0.593700;0.687020;,
  0.581400;0.687410;,
  0.579580;0.574720;,
  0.592080;0.574720;,
  0.611280;0.687610;,
  0.617080;0.574720;,
  0.437500;0.687500;,
  0.422490;0.687340;,
  0.741070;0.981990;,
  0.757070;0.981990;,
  0.450000;0.687500;,
  0.773070;0.981990;,
  0.462500;0.687500;,
  0.789060;0.981990;,
  0.487500;0.687500;,
  0.790870;0.921420;,
  0.480830;0.682640;,
  0.869040;0.981990;,
  0.788950;0.427730;,
  0.768930;0.981990;,
  0.827960;0.487640;,
  0.765780;0.488300;,
  0.793710;0.020910;,
  -0.003290;0.994170;,
  0.701870;0.747580;,
  0.690460;0.514810;,
  0.014680;0.513040;,
  0.070620;0.990420;,
  0.073740;0.513040;,
  0.127100;0.990110;,
  0.127270;0.513040;,
  0.171860;0.994370;,
  0.180800;0.513040;,
  0.844700;0.981350;,
  0.825360;0.983840;,
  0.901080;0.919690;,
  0.767800;0.988840;,
  0.712010;0.992350;,
  0.668450;0.970160;,
  0.633880;0.935590;,
  0.917150;0.830620;,
  0.604040;0.843750;,
  0.668450;0.717340;,
  0.894630;0.751040;,
  0.833380;0.713460;,
  0.712010;0.695150;,
  0.771790;0.708700;,
  0.842670;0.708810;,
  0.955480;0.616080;,
  0.987730;0.679390;,
  0.841940;0.533590;,
  0.771770;0.522480;,
  0.701600;0.533590;,
  0.638300;0.565850;,
  0.588070;0.616080;,
  0.998850;0.749560;,
  0.544700;0.749560;,
  0.987730;0.819730;,
  0.638300;0.933260;,
  0.955480;0.883030;,
  0.841940;0.965520;,
  0.701600;0.965520;,
  0.771770;0.976630;,
  0.799030;0.735980;,
  0.612500;0.532730;,
  0.625000;0.532730;,
  0.824790;0.735980;,
  0.773270;0.735980;,
  0.600000;0.532730;,
  0.747510;0.735980;,
  0.587500;0.532730;,
  0.695990;0.735980;,
  0.562500;0.532730;,
  1.004830;0.588800;,
  0.737250;0.879440;,
  0.724750;0.658270;,
  0.828370;0.658270;,
  0.790870;0.658270;,
  0.789060;0.645230;,
  0.773070;0.645230;,
  0.757070;0.645230;,
  0.741070;0.645230;,
  0.725080;0.981990;,
  0.725080;0.645230;,
  0.693090;0.981990;,
  0.693090;0.645230;,
  0.678370;0.921420;,
  0.678370;0.658270;,
  0.998850;0.749560;,
  0.987730;0.679390;,
  0.955480;0.616080;,
  0.841940;0.533590;,
  0.771770;0.522480;,
  0.701600;0.533590;,
  0.638300;0.565850;,
  0.588070;0.616080;,
  0.544700;0.749560;,
  0.638300;0.933260;,
  0.701600;0.965520;,
  0.771770;0.976630;,
  0.841940;0.965520;,
  0.955480;0.883030;,
  0.987730;0.819730;,
  0.827960;0.487640;;
 }
}
