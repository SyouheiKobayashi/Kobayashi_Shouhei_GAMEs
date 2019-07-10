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
 290;
 -67.43408;150.71831;102.52402;,
 63.67588;150.71831;102.52400;,
 40.52829;188.44323;102.52400;,
 -44.28647;188.44323;102.52402;,
 -44.28647;188.44323;102.52402;,
 40.52829;188.44323;102.52400;,
 40.52827;188.44323;-69.35439;,
 -44.28648;188.44323;-69.35438;,
 -44.28648;188.44323;-69.35438;,
 40.52827;188.44323;-69.35439;,
 63.67587;150.71831;-69.35439;,
 -67.43410;150.71831;-69.35438;,
 -67.43410;150.71831;-69.35438;,
 63.67587;150.71831;-69.35439;,
 63.67588;150.71831;102.52400;,
 -67.43408;150.71831;102.52402;,
 63.67588;150.71831;102.52400;,
 63.67587;150.71831;-69.35439;,
 40.52827;188.44323;-69.35439;,
 -67.43410;150.71831;-69.35438;,
 -67.43408;150.71831;102.52402;,
 -44.28648;188.44323;-69.35438;,
 -90.69474;-0.16635;102.81712;,
 83.31760;-0.16635;102.81710;,
 83.31760;160.46045;102.81710;,
 -90.69474;160.46045;102.81712;,
 -90.69474;160.46045;102.81712;,
 83.31760;160.46045;102.81710;,
 83.31759;160.46045;-69.64749;,
 -90.69475;160.46045;-69.64747;,
 -90.69475;160.46045;-69.64747;,
 83.31759;160.46045;-69.64749;,
 83.31759;-0.16635;-69.64749;,
 -90.69475;-0.16635;-69.64747;,
 -90.69475;-0.16635;-69.64747;,
 83.31759;-0.16635;-69.64749;,
 83.31760;-0.16635;102.81710;,
 -90.69474;-0.16635;102.81712;,
 83.31760;-0.16635;102.81710;,
 83.31759;-0.16635;-69.64749;,
 83.31759;160.46045;-69.64749;,
 83.31760;160.46045;102.81710;,
 -90.69475;-0.16635;-69.64747;,
 -90.69474;-0.16635;102.81712;,
 -90.69474;160.46045;102.81712;,
 -90.69475;160.46045;-69.64747;,
 -6.70915;52.67659;-70.75289;,
 -6.70915;56.68473;-70.64478;,
 1.75899;52.67659;-70.75289;,
 -6.70915;60.69290;-70.53662;,
 -6.70915;64.70106;-70.42850;,
 -6.70915;68.70921;-70.32036;,
 -6.70915;72.71737;-70.21223;,
 -6.70915;76.72554;-70.10409;,
 -6.70915;80.73369;-69.99597;,
 -6.70915;84.74185;-69.88782;,
 -6.70915;88.75002;-69.77970;,
 -6.70915;92.75817;-69.67155;,
 1.75899;92.75817;-69.67155;,
 10.22712;92.75817;-69.67155;,
 10.22712;52.67659;-70.75289;,
 18.69526;92.75817;-69.67155;,
 18.69526;52.67659;-70.75289;,
 27.16339;92.75817;-69.67155;,
 27.16339;52.67659;-70.75289;,
 35.63153;92.75817;-69.67155;,
 35.63153;52.67659;-70.75290;,
 44.09968;92.75817;-69.67155;,
 44.09968;52.67659;-70.75290;,
 52.56781;92.75817;-69.67155;,
 52.56781;52.67659;-70.75290;,
 61.03595;92.75817;-69.67155;,
 61.03595;52.67659;-70.75290;,
 69.50408;92.75817;-69.67155;,
 69.50408;52.67659;-70.75290;,
 77.97223;92.75817;-69.67155;,
 77.97223;88.75002;-69.77971;,
 77.97223;84.74185;-69.88782;,
 77.97223;80.73369;-69.99597;,
 77.97223;76.72554;-70.10410;,
 77.97223;52.67659;-70.75290;,
 77.97223;72.71737;-70.21224;,
 77.97223;68.70921;-70.32036;,
 77.97223;64.70106;-70.42851;,
 77.97223;60.69290;-70.53663;,
 77.97223;56.68473;-70.64479;,
 -62.59178;100.47581;-74.13526;,
 -58.24885;100.43264;-74.13634;,
 -62.68294;92.65950;-74.13455;,
 -62.77409;84.84320;-74.13383;,
 -62.86525;77.02693;-74.13310;,
 -62.95640;69.21063;-74.13239;,
 -63.04757;61.39434;-74.13167;,
 -63.13872;53.57804;-74.13094;,
 -63.22988;45.76177;-74.13023;,
 -63.32103;37.94547;-74.12951;,
 -63.41219;30.12918;-74.12878;,
 -63.50335;22.31288;-74.12807;,
 -59.16040;22.26973;-74.12911;,
 -53.90591;100.38947;-74.13742;,
 -54.81748;22.22659;-74.13019;,
 -49.56298;100.34631;-74.13850;,
 -50.47453;22.18342;-74.13127;,
 -45.22004;100.30317;-74.13958;,
 -46.13160;22.14027;-74.13235;,
 -40.87713;100.26001;-74.14064;,
 -41.78866;22.09712;-74.13343;,
 -36.53419;100.21686;-74.14173;,
 -37.44573;22.05397;-74.13452;,
 -32.19126;100.17371;-74.14281;,
 -33.10279;22.01079;-74.13560;,
 -27.84832;100.13056;-74.14389;,
 -28.75986;21.96764;-74.13668;,
 -23.50539;100.08738;-74.14497;,
 -24.41692;21.92449;-74.13774;,
 -19.16245;100.04423;-74.14602;,
 -19.25361;92.22796;-74.14530;,
 -19.34476;84.41166;-74.14457;,
 -19.43592;76.59536;-74.14385;,
 -19.52708;68.77907;-74.14314;,
 -19.61823;60.96279;-74.14241;,
 -19.70939;53.14650;-74.14169;,
 -19.80054;45.33020;-74.14098;,
 -19.89170;37.51392;-74.14025;,
 -19.98286;29.69763;-74.13953;,
 -20.07399;21.88134;-74.13882;,
 123.83661;149.58205;107.50571;,
 -5.57819;218.38723;107.50595;,
 -6.07695;190.71358;107.50573;,
 121.22750;126.08610;107.50571;,
 121.22750;126.08610;107.50571;,
 -6.07695;190.71358;107.50573;,
 -6.07696;190.51901;-74.33610;,
 121.22748;126.08610;-74.33611;,
 121.22748;126.08610;-74.33611;,
 -6.07696;190.51901;-74.33610;,
 -5.57821;218.38723;-74.33630;,
 123.83659;149.58205;-74.33611;,
 123.83659;149.58205;-74.33611;,
 -5.57821;218.38723;-74.33630;,
 -5.57819;218.38723;107.50595;,
 123.83661;149.58205;107.50571;,
 -5.57819;218.38723;107.50595;,
 -5.57821;218.38723;-74.33630;,
 -6.07696;190.51901;-74.33610;,
 -6.07695;190.71358;107.50573;,
 123.83659;149.58205;-74.33611;,
 123.83661;149.58205;107.50571;,
 121.22750;126.08610;107.50571;,
 121.22748;126.08610;-74.33611;,
 -130.14005;140.44215;107.50574;,
 -127.19191;117.14625;107.50574;,
 -6.07695;190.51901;107.50573;,
 -5.36918;218.18721;107.50595;,
 -127.19191;117.14625;107.50574;,
 -127.19193;117.14625;-74.33609;,
 -6.07696;190.51901;-74.33610;,
 -6.07695;190.51901;107.50573;,
 -127.19193;117.14625;-74.33609;,
 -130.14008;140.44215;-74.33609;,
 -5.36917;218.18723;-74.33630;,
 -6.07696;190.51901;-74.33610;,
 -130.14008;140.44215;-74.33609;,
 -130.14005;140.44215;107.50574;,
 -5.36918;218.18721;107.50595;,
 -5.36917;218.18723;-74.33630;,
 -5.36918;218.18721;107.50595;,
 -6.07695;190.51901;107.50573;,
 -5.36917;218.18723;-74.33630;,
 -130.14008;140.44215;-74.33609;,
 -127.19193;117.14625;-74.33609;,
 -127.19191;117.14625;107.50574;,
 -130.14005;140.44215;107.50574;,
 28.96829;175.59749;53.82078;,
 66.54040;175.59749;53.82078;,
 66.54040;226.96524;53.82078;,
 28.96829;226.96524;53.82078;,
 28.96829;226.96524;53.82078;,
 66.54040;226.96524;53.82078;,
 66.54039;226.96524;10.46835;,
 28.96829;226.96524;10.46835;,
 28.96829;226.96524;10.46835;,
 66.54039;226.96524;10.46835;,
 66.54039;175.59749;10.46835;,
 28.96829;175.59749;10.46835;,
 28.96829;175.59749;10.46835;,
 66.54039;175.59749;10.46835;,
 66.54040;175.59749;53.82078;,
 28.96829;175.59749;53.82078;,
 66.54040;175.59749;53.82078;,
 66.54039;175.59749;10.46835;,
 66.54039;226.96524;10.46835;,
 66.54040;226.96524;53.82078;,
 28.96829;175.59749;10.46835;,
 28.96829;175.59749;53.82078;,
 28.96829;226.96524;53.82078;,
 28.96829;226.96524;10.46835;,
 -1.70930;98.42150;-37.38927;,
 -43.73143;120.76315;-37.38920;,
 -43.89339;111.77726;-37.38926;,
 -2.55651;90.79216;-37.38927;,
 -2.55651;90.79216;-37.38927;,
 -43.89339;111.77726;-37.38926;,
 -43.89340;111.71406;-96.43487;,
 -2.55652;90.79216;-96.43488;,
 -2.55652;90.79216;-96.43488;,
 -43.89340;111.71406;-96.43487;,
 -43.73144;120.76315;-96.43496;,
 -1.70930;98.42150;-96.43488;,
 -1.70930;98.42150;-96.43488;,
 -43.73144;120.76315;-96.43496;,
 -43.73143;120.76315;-37.38920;,
 -1.70930;98.42150;-37.38927;,
 -43.73143;120.76315;-37.38920;,
 -43.73144;120.76315;-96.43496;,
 -43.89340;111.71406;-96.43487;,
 -43.89339;111.77726;-37.38926;,
 -1.70930;98.42150;-96.43488;,
 -1.70930;98.42150;-37.38927;,
 -2.55651;90.79216;-37.38927;,
 -2.55652;90.79216;-96.43488;,
 -84.17777;95.45368;-37.38926;,
 -83.22047;87.88931;-37.38926;,
 -43.89339;111.71406;-37.38926;,
 -43.66354;120.69820;-37.38920;,
 -83.22047;87.88931;-37.38926;,
 -83.22047;87.88931;-96.43487;,
 -43.89340;111.71406;-96.43487;,
 -43.89339;111.71406;-37.38926;,
 -83.22047;87.88931;-96.43487;,
 -84.17777;95.45368;-96.43487;,
 -43.66355;120.69820;-96.43496;,
 -43.89340;111.71406;-96.43487;,
 -84.17777;95.45368;-96.43487;,
 -84.17777;95.45368;-37.38926;,
 -43.66354;120.69820;-37.38920;,
 -43.66355;120.69820;-96.43496;,
 -43.66354;120.69820;-37.38920;,
 -43.89339;111.71406;-37.38926;,
 -43.66355;120.69820;-96.43496;,
 -84.17777;95.45368;-96.43487;,
 -83.22047;87.88931;-96.43487;,
 -83.22047;87.88931;-37.38926;,
 -84.17777;95.45368;-37.38926;,
 -80.93310;0.54015;-83.86895;,
 -5.91590;0.54015;-83.86895;,
 -5.91590;12.76393;-83.86895;,
 -80.93310;12.76393;-83.86895;,
 -80.93310;12.76393;-83.86895;,
 -5.91590;12.76393;-83.86895;,
 -5.91590;12.76393;-99.21354;,
 -80.93310;12.76393;-99.21353;,
 -80.93310;12.76393;-99.21353;,
 -5.91590;12.76393;-99.21354;,
 -5.91590;0.54015;-99.21354;,
 -80.93310;0.54015;-99.21353;,
 -80.93310;0.54015;-99.21353;,
 -5.91590;0.54015;-99.21354;,
 -5.91590;0.54015;-83.86895;,
 -80.93310;0.54015;-83.86895;,
 -5.91590;0.54015;-83.86895;,
 -5.91590;0.54015;-99.21354;,
 -5.91590;12.76393;-99.21354;,
 -5.91590;12.76393;-83.86895;,
 -80.93310;0.54015;-99.21353;,
 -80.93310;0.54015;-83.86895;,
 -80.93310;12.76393;-83.86895;,
 -80.93310;12.76393;-99.21353;,
 -80.93310;10.54783;-69.00404;,
 -5.91589;10.54783;-69.00405;,
 -5.91589;22.77162;-69.00405;,
 -80.93310;22.77162;-69.00404;,
 -80.93310;22.77162;-69.00404;,
 -5.91589;22.77162;-69.00405;,
 -5.91590;22.77162;-84.34865;,
 -80.93310;22.77162;-84.34865;,
 -80.93310;22.77162;-84.34865;,
 -5.91590;22.77162;-84.34865;,
 -5.91590;10.54783;-84.34865;,
 -80.93310;10.54783;-84.34865;,
 -80.93310;10.54783;-84.34865;,
 -5.91590;10.54783;-84.34865;,
 -5.91589;10.54783;-69.00405;,
 -80.93310;10.54783;-69.00404;,
 -5.91590;10.54783;-84.34865;,
 -5.91590;22.77162;-84.34865;,
 -80.93310;10.54783;-84.34865;,
 -80.93310;10.54783;-69.00404;,
 -80.93310;22.77162;-69.00404;,
 -80.93310;22.77162;-84.34865;;
 
 130;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,5;,
 4;19,20,4,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 3;46,47,48;,
 3;47,49,48;,
 3;49,50,48;,
 3;50,51,48;,
 3;51,52,48;,
 3;52,53,48;,
 3;53,54,48;,
 3;54,55,48;,
 3;55,56,48;,
 3;56,57,48;,
 3;57,58,48;,
 3;58,59,48;,
 3;48,59,60;,
 3;59,61,60;,
 3;60,61,62;,
 3;61,63,62;,
 3;62,63,64;,
 3;63,65,64;,
 3;64,65,66;,
 3;65,67,66;,
 3;66,67,68;,
 3;67,69,68;,
 3;68,69,70;,
 3;69,71,70;,
 3;70,71,72;,
 3;71,73,72;,
 3;72,73,74;,
 3;73,75,74;,
 3;74,75,76;,
 3;74,76,77;,
 3;74,77,78;,
 3;74,78,79;,
 3;74,79,80;,
 3;79,81,80;,
 3;81,82,80;,
 3;82,83,80;,
 3;83,84,80;,
 3;84,85,80;,
 3;86,87,88;,
 3;88,87,89;,
 3;89,87,90;,
 3;90,87,91;,
 3;91,87,92;,
 3;92,87,93;,
 3;93,87,94;,
 3;94,87,95;,
 3;95,87,96;,
 3;96,87,97;,
 3;97,87,98;,
 3;87,99,98;,
 3;98,99,100;,
 3;99,101,100;,
 3;100,101,102;,
 3;101,103,102;,
 3;102,103,104;,
 3;103,105,104;,
 3;104,105,106;,
 3;105,107,106;,
 3;106,107,108;,
 3;107,109,108;,
 3;108,109,110;,
 3;109,111,110;,
 3;110,111,112;,
 3;111,113,112;,
 3;112,113,114;,
 3;113,115,114;,
 3;114,115,116;,
 3;114,116,117;,
 3;114,117,118;,
 3;114,118,119;,
 3;114,119,120;,
 3;114,120,121;,
 3;114,121,122;,
 3;114,122,123;,
 3;114,123,124;,
 3;124,125,114;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;158,159,160,161;,
 4;162,163,164,165;,
 4;166,167,144,168;,
 4;169,170,171,172;,
 4;173,174,175,176;,
 4;177,178,179,180;,
 4;181,182,183,184;,
 4;185,186,187,188;,
 4;189,190,191,192;,
 4;193,194,195,196;,
 4;197,198,199,200;,
 4;201,202,203,204;,
 4;205,206,207,208;,
 4;209,210,211,212;,
 4;213,214,215,216;,
 4;217,218,219,220;,
 4;221,222,223,224;,
 4;225,226,227,228;,
 4;229,230,231,232;,
 4;233,234,235,236;,
 4;237,238,215,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;269,284,285,270;,
 4;286,287,288,289;;
 
 MeshMaterialList {
  1;
  130;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\game114\\Desktop\\2年生後期_3Dスクロールアクション\\game_project\\14 ギミック\\DATA\\TEXTURE\\OBJECT\\home02.jpg";
   }
  }
 }
 MeshNormals {
  117;
  0.000000;0.000000;1.000000;,
  -0.488371;0.872636;0.000000;,
  0.488371;0.872636;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000012;0.026971;-0.999636;,
  0.000000;0.026969;-0.999636;,
  0.000000;0.026969;-0.999636;,
  -0.000000;0.026969;-0.999636;,
  -0.000000;0.026969;-0.999636;,
  -0.000012;0.026971;-0.999636;,
  0.000004;0.026969;-0.999636;,
  -0.000004;0.026969;-0.999636;,
  -0.000002;0.026968;-0.999636;,
  0.000002;0.026968;-0.999636;,
  0.000003;0.026969;-0.999636;,
  -0.000003;0.026969;-0.999636;,
  -0.000001;0.026968;-0.999636;,
  0.000004;0.026967;-0.999636;,
  0.000000;0.026968;-0.999636;,
  -1.000000;0.000000;0.000000;,
  0.000001;0.026969;-0.999636;,
  1.000000;0.000000;0.000000;,
  0.000001;0.026968;-0.999636;,
  -1.000000;0.000000;0.000000;,
  0.000001;0.026970;-0.999636;,
  0.000003;0.026969;-0.999636;,
  0.000000;0.026963;-0.999636;,
  0.000002;0.026969;-0.999636;,
  -0.000000;0.026969;-0.999636;,
  -0.000002;0.026969;-0.999636;,
  0.000000;0.026969;-0.999636;,
  -0.000252;-0.000089;-1.000000;,
  -0.000243;-0.000090;-1.000000;,
  -0.000241;-0.000090;-1.000000;,
  -0.000258;-0.000088;-1.000000;,
  -0.000245;-0.000090;-1.000000;,
  -0.000243;-0.000090;-1.000000;,
  -0.000254;-0.000088;-1.000000;,
  -0.000248;-0.000090;-1.000000;,
  -0.000245;-0.000090;-1.000000;,
  -0.000250;-0.000088;-1.000000;,
  -0.000250;-0.000088;-1.000000;,
  -0.000247;-0.000090;-1.000000;,
  -0.000248;-0.000089;-1.000000;,
  -0.000250;-0.000090;-1.000000;,
  -0.000250;-0.000090;-1.000000;,
  -0.000250;-0.000090;-1.000000;,
  -0.000248;-0.000090;-1.000000;,
  -0.000248;-0.000090;-1.000000;,
  -0.000251;-0.000089;-1.000000;,
  -0.000249;-0.000089;-1.000000;,
  -0.000250;-0.000089;-1.000000;,
  -0.000251;-0.000089;-1.000000;,
  -0.000250;-0.000089;-1.000000;,
  -0.000250;-0.000089;-1.000000;,
  -0.000248;-0.000089;-1.000000;,
  -0.000250;-0.000089;-1.000000;,
  -0.000248;-0.000089;-1.000000;,
  -0.000245;-0.000090;-1.000000;,
  -0.000250;-0.000088;-1.000000;,
  -0.000250;-0.000088;-1.000000;,
  -0.000245;-0.000090;-1.000000;,
  -0.000248;-0.000090;-1.000000;,
  -0.000254;-0.000088;-1.000000;,
  -0.000243;-0.000090;-1.000000;,
  -0.000245;-0.000090;-1.000000;,
  -0.000258;-0.000088;-1.000000;,
  -0.000241;-0.000090;-1.000000;,
  -0.000243;-0.000090;-1.000000;,
  -0.000252;-0.000089;-1.000000;,
  -0.000001;-0.000004;1.000000;,
  -0.452128;-0.891953;0.000477;,
  0.037757;-0.999287;0.000273;,
  -0.000001;-0.000004;-1.000000;,
  0.000002;-0.000004;1.000000;,
  0.518145;-0.855292;-0.000000;,
  0.000001;-0.000004;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000001;-0.000004;1.000000;,
  -0.452127;-0.891953;0.000477;,
  0.037757;-0.999287;0.000273;,
  -0.000002;-0.000005;-1.000000;,
  0.000002;-0.000004;1.000000;,
  0.518145;-0.855293;-0.000000;,
  0.000002;-0.000005;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.852341;0.522987;-0.000000;,
  -0.852341;0.522987;0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000004;-1.000000;,
  0.469440;0.882964;-0.000000;,
  -0.999839;0.017957;-0.000009;,
  0.993891;-0.110367;-0.000000;,
  0.864900;-0.501944;-0.000000;,
  -0.528840;0.848721;0.000000;,
  0.999673;-0.025573;-0.000000;,
  -0.992087;-0.125551;0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000005;-1.000000;,
  0.469440;0.882964;-0.000000;,
  -0.999839;0.017958;-0.000010;,
  0.993891;-0.110368;-0.000000;,
  0.864899;-0.501946;-0.000000;,
  -0.528840;0.848721;0.000000;,
  0.999673;-0.025575;-0.000000;,
  -0.992087;-0.125553;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;;
  130;
  4;0,0,0,0;,
  4;1,2,2,1;,
  4;3,3,3,3;,
  4;92,92,92,92;,
  4;93,93,2,2;,
  4;94,94,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;92,92,92,92;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  3;29,28,30;,
  3;28,27,30;,
  3;27,25,30;,
  3;25,23,30;,
  3;23,21,30;,
  3;21,19,30;,
  3;19,17,30;,
  3;17,15,30;,
  3;15,13,30;,
  3;13,7,30;,
  3;7,8,30;,
  3;8,9,30;,
  3;30,9,8;,
  3;9,9,8;,
  3;8,9,9;,
  3;9,10,9;,
  3;9,10,11;,
  3;10,11,11;,
  3;11,11,31;,
  3;11,8,31;,
  3;31,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,9,8;,
  3;8,9,8;,
  3;9,8,8;,
  3;8,8,32;,
  3;8,12,32;,
  3;32,12,14;,
  3;32,14,16;,
  3;32,16,18;,
  3;32,18,20;,
  3;32,20,33;,
  3;22,22,22;,
  3;24,24,24;,
  3;26,26,22;,
  3;24,24,24;,
  3;26,26,22;,
  3;44,46,43;,
  3;43,46,42;,
  3;42,46,41;,
  3;41,46,40;,
  3;40,46,39;,
  3;39,46,38;,
  3;38,46,37;,
  3;37,46,36;,
  3;36,46,35;,
  3;35,46,34;,
  3;34,46,45;,
  3;46,48,45;,
  3;45,48,47;,
  3;48,49,47;,
  3;47,49,49;,
  3;49,51,49;,
  3;49,51,50;,
  3;51,53,50;,
  3;50,53,52;,
  3;53,55,52;,
  3;52,55,54;,
  3;55,57,54;,
  3;54,57,56;,
  3;57,59,56;,
  3;56,59,58;,
  3;59,61,58;,
  3;58,61,60;,
  3;61,72,60;,
  3;60,72,71;,
  3;60,71,70;,
  3;60,70,69;,
  3;60,69,68;,
  3;60,68,67;,
  3;60,67,66;,
  3;60,66,65;,
  3;60,65,64;,
  3;60,64,63;,
  3;63,62,60;,
  4;73,73,73,73;,
  4;74,74,75,74;,
  4;76,97,76,76;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;100,100,100,100;,
  4;77,77,77,77;,
  4;78,78,75,101;,
  4;79,79,79,97;,
  4;102,102,102,102;,
  4;103,101,103,103;,
  4;104,104,104,104;,
  4;80,80,80,80;,
  4;5,5,5,5;,
  4;81,81,81,81;,
  4;92,92,92,92;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;82,82,82,82;,
  4;83,83,84,83;,
  4;85,107,85,85;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;86,86,86,86;,
  4;87,87,84,111;,
  4;88,88,88,107;,
  4;112,112,112,112;,
  4;113,111,113,113;,
  4;114,114,114,114;,
  4;89,89,89,89;,
  4;5,5,5,5;,
  4;90,90,90,90;,
  4;92,92,92,92;,
  4;115,115,115,115;,
  4;22,22,22,22;,
  4;89,89,89,89;,
  4;5,5,5,5;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;116,116,116,116;,
  4;22,22,22,22;;
 }
 MeshTextureCoords {
  290;
  0.784205;0.759731;,
  0.782019;0.835588;,
  0.857875;0.837774;,
  0.860062;0.761918;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.714879;0.701768;,
  0.718629;0.830777;,
  0.838916;0.826755;,
  0.835166;0.697746;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.125000;0.750000;,
  0.641816;0.640427;,
  0.640432;0.979879;,
  0.968757;0.981310;,
  0.970141;0.641859;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.644824;0.640441;,
  0.643440;0.979892;,
  0.971764;0.981323;,
  0.973149;0.641872;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.641822;0.639069;,
  0.640438;0.978521;,
  0.968762;0.979952;,
  0.970146;0.640500;,
  0.641787;0.647611;,
  0.640403;0.987063;,
  0.968727;0.988494;,
  0.970112;0.649042;,
  0.065523;0.272788;,
  0.065523;0.294288;,
  0.108327;0.272788;,
  0.065523;0.315789;,
  0.065523;0.337289;,
  0.065523;0.358789;,
  0.065523;0.380289;,
  0.065523;0.401790;,
  0.065523;0.423290;,
  0.065523;0.444790;,
  0.065523;0.466290;,
  0.065523;0.487791;,
  0.108327;0.487791;,
  0.151132;0.487791;,
  0.151132;0.272788;,
  0.193936;0.487791;,
  0.193936;0.272788;,
  0.236740;0.487791;,
  0.236740;0.272788;,
  0.279544;0.487791;,
  0.279544;0.272788;,
  0.322349;0.487791;,
  0.322349;0.272788;,
  0.365153;0.487791;,
  0.365153;0.272788;,
  0.407957;0.487791;,
  0.407957;0.272788;,
  0.450761;0.487791;,
  0.450761;0.272788;,
  0.493565;0.487791;,
  0.493565;0.466290;,
  0.493565;0.444790;,
  0.493565;0.423290;,
  0.493565;0.401790;,
  0.493565;0.272788;,
  0.493565;0.380289;,
  0.493565;0.358789;,
  0.493565;0.337289;,
  0.493565;0.315789;,
  0.493565;0.294288;,
  0.955918;0.108531;,
  0.928758;0.109053;,
  0.956103;0.139751;,
  0.956288;0.170971;,
  0.956473;0.202192;,
  0.956658;0.233412;,
  0.956844;0.264632;,
  0.957029;0.295853;,
  0.957214;0.327073;,
  0.957399;0.358293;,
  0.957584;0.389514;,
  0.957769;0.420734;,
  0.930608;0.421257;,
  0.901597;0.109576;,
  0.903448;0.421779;,
  0.874436;0.110099;,
  0.876287;0.422302;,
  0.847276;0.110621;,
  0.849126;0.422825;,
  0.820115;0.111144;,
  0.821966;0.423347;,
  0.792955;0.111667;,
  0.794805;0.423870;,
  0.765794;0.112190;,
  0.767645;0.424393;,
  0.738633;0.112712;,
  0.740484;0.424915;,
  0.711473;0.113235;,
  0.713323;0.425438;,
  0.684312;0.113757;,
  0.684497;0.144978;,
  0.684682;0.176198;,
  0.684867;0.207419;,
  0.685052;0.238639;,
  0.685237;0.269859;,
  0.685422;0.301080;,
  0.685607;0.332300;,
  0.685793;0.363520;,
  0.685978;0.394740;,
  0.686163;0.425961;,
  0.502814;0.972759;,
  0.508952;0.546457;,
  0.087992;0.540395;,
  0.081854;0.966697;,
  0.328769;0.327318;,
  0.578769;0.327318;,
  0.578769;0.077318;,
  0.328769;0.077318;,
  0.506071;0.972806;,
  0.512210;0.546503;,
  0.091250;0.540442;,
  0.085111;0.966744;,
  0.483065;0.972945;,
  0.489204;0.546643;,
  0.068243;0.540581;,
  0.062105;0.966883;,
  0.706046;0.675660;,
  0.703006;0.925641;,
  0.952988;0.928681;,
  0.956028;0.678700;,
  0.502838;0.955692;,
  0.508976;0.529390;,
  0.088016;0.523328;,
  0.081877;0.949631;,
  0.502814;0.972759;,
  0.081854;0.966697;,
  0.087992;0.540395;,
  0.508952;0.546457;,
  0.330420;0.325667;,
  0.330420;0.075667;,
  0.580420;0.075667;,
  0.580420;0.325667;,
  0.517354;0.961704;,
  0.096394;0.955642;,
  0.102533;0.529340;,
  0.523493;0.535402;,
  0.497258;0.972945;,
  0.076298;0.966883;,
  0.082436;0.540581;,
  0.503396;0.546643;,
  0.706046;0.675660;,
  0.956028;0.678700;,
  0.703006;0.925641;,
  0.502838;0.959705;,
  0.081877;0.953644;,
  0.088016;0.527341;,
  0.508976;0.533403;,
  0.642951;0.982649;,
  0.991891;0.982649;,
  0.991891;0.633709;,
  0.642951;0.633709;,
  0.640647;0.986304;,
  0.989587;0.986304;,
  0.989587;0.637364;,
  0.640647;0.637364;,
  0.640647;0.978435;,
  0.989587;0.978435;,
  0.989587;0.629496;,
  0.640647;0.629496;,
  0.507903;0.923270;,
  0.514041;0.496967;,
  0.093081;0.490906;,
  0.086942;0.917208;,
  0.657387;0.979539;,
  1.004855;0.979539;,
  1.004855;0.632071;,
  0.657387;0.632071;,
  0.666960;0.984128;,
  1.014428;0.984128;,
  1.014428;0.636661;,
  0.666960;0.636661;,
  0.502814;0.937277;,
  0.508952;0.510974;,
  0.087992;0.504912;,
  0.081854;0.931215;,
  0.328769;0.327318;,
  0.578769;0.327318;,
  0.578769;0.077318;,
  0.328769;0.077318;,
  0.449889;0.973441;,
  0.456028;0.547138;,
  0.035068;0.541076;,
  0.028929;0.967379;,
  0.507903;0.967413;,
  0.514041;0.541110;,
  0.093081;0.535049;,
  0.086942;0.961351;,
  0.706046;0.675660;,
  0.703006;0.925641;,
  0.952988;0.928681;,
  0.956028;0.678700;,
  0.502838;0.935627;,
  0.508976;0.509325;,
  0.088016;0.503263;,
  0.081877;0.929566;,
  0.502814;0.937277;,
  0.081854;0.931215;,
  0.087992;0.504912;,
  0.508952;0.510974;,
  0.330420;0.325667;,
  0.330420;0.075667;,
  0.580420;0.075667;,
  0.580420;0.325667;,
  0.461172;0.962339;,
  0.040212;0.956277;,
  0.046350;0.529975;,
  0.467311;0.536036;,
  0.507903;0.967413;,
  0.086942;0.961351;,
  0.093081;0.535049;,
  0.514041;0.541110;,
  0.706046;0.675660;,
  0.956028;0.678700;,
  0.703006;0.925641;,
  0.502838;0.935627;,
  0.081877;0.929566;,
  0.088016;0.503263;,
  0.508976;0.509325;,
  0.158298;0.185034;,
  0.408298;0.185034;,
  0.408298;0.042637;,
  0.158298;0.042637;,
  0.158298;0.184354;,
  0.408298;0.184354;,
  0.408298;0.041957;,
  0.158298;0.041957;,
  0.158298;0.190532;,
  0.408298;0.190532;,
  0.408298;0.048134;,
  0.158298;0.048134;,
  0.158298;0.182995;,
  0.408298;0.182995;,
  0.408298;0.040597;,
  0.158298;0.040597;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.169143;0.185034;,
  0.419143;0.185034;,
  0.419143;0.042637;,
  0.169143;0.042637;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.158298;0.186640;,
  0.408298;0.186640;,
  0.408298;0.044242;,
  0.158298;0.044242;,
  0.158298;0.190532;,
  0.408298;0.190532;,
  0.408298;0.048134;,
  0.158298;0.048134;,
  0.158298;0.187566;,
  0.408298;0.187566;,
  0.408298;0.045169;,
  0.158298;0.045169;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.157104;0.185034;,
  0.407104;0.185034;,
  0.407104;0.042637;,
  0.157104;0.042637;;
 }
}
