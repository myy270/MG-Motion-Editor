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
 154;
 -3.50489;0.00201;-0.99020;,
 -3.50489;-0.99799;-0.99020;,
 -3.50489;-0.99799;1.00980;,
 -3.50489;0.00201;1.00980;,
 -3.50489;1.00201;-0.99020;,
 -3.50489;0.00201;-0.99020;,
 -3.50489;0.00201;1.00980;,
 -3.50489;1.00201;1.00980;,
 -2.50489;-7.99799;-0.99020;,
 -2.50489;-8.99799;-1.99020;,
 -2.50489;-8.99799;2.00980;,
 -2.50489;-7.99799;1.00980;,
 -2.50489;-5.99799;-0.99020;,
 -2.50489;-5.99799;-0.99020;,
 -2.50489;-7.99799;-0.99020;,
 -2.50489;-7.99799;1.00980;,
 -2.50489;-5.99799;1.00980;,
 -2.50489;-5.99799;1.00980;,
 -2.50489;-4.99799;-1.99020;,
 -2.50489;-4.99799;2.00980;,
 -2.50489;0.00201;-0.99020;,
 -2.50489;-0.99799;-1.99020;,
 -2.50489;-0.99799;-0.99020;,
 -2.50489;0.00201;1.00980;,
 -2.50489;-0.99799;1.00980;,
 -2.50489;-0.99799;2.00980;,
 -2.50489;1.00201;-1.99020;,
 -2.50489;1.00201;-0.99020;,
 -2.50489;1.00201;1.00980;,
 -2.50489;1.00201;2.00980;,
 -2.50489;2.00201;-0.99020;,
 -2.50489;1.00201;-0.99020;,
 -2.50489;1.00201;1.00980;,
 -2.50489;2.00201;1.00980;,
 -1.50489;-2.99799;-0.99020;,
 -1.50489;-4.99799;-0.99020;,
 -1.50489;-4.99799;1.00980;,
 -1.50489;-2.99799;1.00980;,
 -1.50489;1.00201;-2.99020;,
 -1.50489;-0.99799;-2.99020;,
 -1.50489;-0.99799;-1.99020;,
 -1.50489;1.00201;-1.99020;,
 -1.50489;1.00201;2.00980;,
 -1.50489;-0.99799;2.00980;,
 -1.50489;-0.99799;3.00980;,
 -1.50489;1.00201;3.00980;,
 -1.50489;2.00201;-1.99020;,
 -1.50489;1.00201;-1.99020;,
 -1.50489;1.00201;-0.99020;,
 -1.50489;2.00201;-0.99020;,
 -1.50489;2.00201;1.00980;,
 -1.50489;1.00201;1.00980;,
 -1.50489;1.00201;2.00980;,
 -1.50489;2.00201;2.00980;,
 -1.50489;3.00201;-0.99020;,
 -1.50489;2.00201;-0.99020;,
 -1.50489;2.00201;1.00980;,
 -1.50489;3.00201;1.00980;,
 -0.50489;-1.99799;-0.99020;,
 -0.50489;-2.99799;-0.99020;,
 -0.50489;-2.99799;1.00980;,
 -0.50489;-1.99799;1.00980;,
 -2.50489;0.00201;-0.99020;,
 -2.50489;0.00201;1.00980;,
 -1.50489;-8.99799;-0.99020;,
 -1.50489;-7.99799;-0.99020;,
 -1.50489;-8.99799;1.00980;,
 -1.50489;-7.99799;1.00980;,
 -1.50489;-7.99799;-0.99020;,
 -1.50489;-6.99799;-0.99020;,
 -1.50489;-7.99799;1.00980;,
 -1.50489;-6.99799;1.00980;,
 -1.50489;-0.99799;-0.99020;,
 -1.50489;1.00201;-0.99020;,
 -1.50489;-0.99799;1.00980;,
 -1.50489;1.00201;1.00980;,
 -0.50489;-8.99799;-1.99020;,
 -0.50489;-7.99799;-1.99020;,
 -0.50489;-8.99799;-0.99020;,
 -0.50489;-7.99799;-0.99020;,
 -0.50489;-8.99799;1.00980;,
 -0.50489;-7.99799;1.00980;,
 -0.50489;-8.99799;2.00980;,
 -0.50489;-7.99799;2.00980;,
 -0.50489;-7.99799;-1.99020;,
 -0.50489;-6.99799;-1.99020;,
 -0.50489;-7.99799;-0.99020;,
 -0.50489;-6.99799;-0.99020;,
 -0.50489;-7.99799;1.00980;,
 -0.50489;-6.99799;1.00980;,
 -0.50489;-7.99799;2.00980;,
 -0.50489;-6.99799;2.00980;,
 -0.50489;-4.99799;-0.99020;,
 -0.50489;-4.99799;1.00980;,
 -0.50489;-0.99799;-2.99020;,
 -0.50489;1.00201;-2.99020;,
 -0.50489;-0.99799;-1.99020;,
 -0.50489;1.00201;-1.99020;,
 -0.50489;-0.99799;2.00980;,
 -0.50489;1.00201;2.00980;,
 -0.50489;-0.99799;3.00980;,
 -0.50489;1.00201;3.00980;,
 -0.50489;2.00201;-0.99020;,
 -0.50489;3.00201;-0.99020;,
 -0.50489;2.00201;1.00980;,
 -0.50489;3.00201;1.00980;,
 0.49511;-6.99799;-1.99020;,
 0.49511;-4.99799;-1.99020;,
 0.49511;-6.99799;-0.99020;,
 0.49511;-4.99799;-0.99020;,
 0.49511;-6.99799;1.00980;,
 0.49511;-4.99799;1.00980;,
 0.49511;-6.99799;2.00980;,
 0.49511;-4.99799;2.00980;,
 0.49511;-3.99799;-0.99020;,
 0.49511;-3.99799;1.00980;,
 0.49511;-3.99799;-0.99020;,
 0.49511;-1.99799;-0.99020;,
 0.49511;-3.99799;1.00980;,
 0.49511;-1.99799;1.00980;,
 0.49511;1.00201;-1.99020;,
 0.49511;2.00201;-1.99020;,
 0.49511;1.00201;-0.99020;,
 0.49511;2.00201;-0.99020;,
 0.49511;1.00201;1.00980;,
 0.49511;2.00201;1.00980;,
 0.49511;1.00201;2.00980;,
 0.49511;2.00201;2.00980;,
 -1.50489;-7.99799;-1.99020;,
 -1.50489;-5.99799;-1.99020;,
 -1.50489;-7.99799;-1.99020;,
 -1.50489;-5.99799;-1.99020;,
 -0.50489;-5.99799;-1.99020;,
 -0.50489;-5.99799;-1.99020;,
 -0.50489;-4.99799;-1.99020;,
 -0.50489;1.00201;-1.99020;,
 -0.50489;-4.99799;-1.99020;,
 -0.50489;-4.99799;-0.99020;,
 -0.50489;-3.99799;-0.99020;,
 -0.50489;-3.99799;-0.99020;,
 -0.50489;2.00201;1.00980;,
 -0.50489;2.00201;-0.99020;,
 -0.50489;-4.99799;1.00980;,
 -0.50489;-3.99799;1.00980;,
 -0.50489;-3.99799;1.00980;,
 -1.50489;-7.99799;2.00980;,
 -1.50489;-5.99799;2.00980;,
 -1.50489;-7.99799;2.00980;,
 -1.50489;-5.99799;2.00980;,
 -0.50489;-5.99799;2.00980;,
 -0.50489;-5.99799;2.00980;,
 -0.50489;-4.99799;2.00980;,
 -0.50489;1.00201;2.00980;,
 -0.50489;-4.99799;2.00980;;
 
 244;
 3;0,1,2;,
 3;3,0,2;,
 3;4,5,6;,
 3;7,4,6;,
 3;8,9,10;,
 3;11,8,10;,
 3;12,9,8;,
 3;13,14,15;,
 3;16,11,10;,
 3;17,13,15;,
 3;18,9,12;,
 3;18,12,16;,
 3;19,16,10;,
 3;19,18,16;,
 3;20,21,22;,
 3;23,24,25;,
 3;26,21,20;,
 3;27,26,20;,
 3;28,23,25;,
 3;29,28,25;,
 3;30,31,32;,
 3;33,30,32;,
 3;34,35,36;,
 3;37,34,36;,
 3;38,39,40;,
 3;41,38,40;,
 3;42,43,44;,
 3;45,42,44;,
 3;46,47,48;,
 3;49,46,48;,
 3;50,51,52;,
 3;53,50,52;,
 3;54,55,56;,
 3;57,54,56;,
 3;58,59,60;,
 3;61,58,60;,
 3;22,20,24;,
 3;20,23,24;,
 3;62,31,63;,
 3;31,32,63;,
 3;64,65,66;,
 3;65,67,66;,
 3;68,69,70;,
 3;69,71,70;,
 3;40,41,72;,
 3;41,73,72;,
 3;74,75,43;,
 3;75,42,43;,
 3;48,49,51;,
 3;49,50,51;,
 3;76,77,78;,
 3;77,79,78;,
 3;80,81,82;,
 3;81,83,82;,
 3;84,85,86;,
 3;85,87,86;,
 3;88,89,90;,
 3;89,91,90;,
 3;87,92,89;,
 3;92,93,89;,
 3;94,95,96;,
 3;95,97,96;,
 3;98,99,100;,
 3;99,101,100;,
 3;102,103,104;,
 3;103,105,104;,
 3;106,107,108;,
 3;107,109,108;,
 3;110,111,112;,
 3;111,113,112;,
 3;109,114,111;,
 3;114,115,111;,
 3;116,117,118;,
 3;117,119,118;,
 3;120,121,122;,
 3;121,123,122;,
 3;124,125,126;,
 3;125,127,126;,
 3;94,39,38;,
 3;95,94,38;,
 3;128,9,18;,
 3;129,128,18;,
 3;40,21,26;,
 3;41,40,26;,
 3;76,9,128;,
 3;84,130,131;,
 3;77,76,128;,
 3;85,84,131;,
 3;132,129,18;,
 3;133,85,131;,
 3;134,132,18;,
 3;135,47,46;,
 3;106,133,136;,
 3;106,85,133;,
 3;107,106,136;,
 3;120,135,46;,
 3;121,120,46;,
 3;22,1,0;,
 3;62,5,4;,
 3;20,22,0;,
 3;31,62,4;,
 3;48,31,30;,
 3;49,48,30;,
 3;137,35,34;,
 3;138,137,34;,
 3;59,138,34;,
 3;102,55,54;,
 3;103,102,54;,
 3;109,92,139;,
 3;116,59,58;,
 3;114,109,139;,
 3;116,138,59;,
 3;117,116,58;,
 3;74,24,23;,
 3;74,23,28;,
 3;75,74,28;,
 3;80,66,67;,
 3;88,70,71;,
 3;81,80,67;,
 3;89,88,71;,
 3;140,51,50;,
 3;110,89,93;,
 3;111,110,93;,
 3;124,51,140;,
 3;125,124,140;,
 3;98,43,42;,
 3;99,98,42;,
 3;40,96,41;,
 3;96,97,41;,
 3;22,72,20;,
 3;20,72,27;,
 3;72,73,27;,
 3;64,78,65;,
 3;68,86,69;,
 3;78,79,65;,
 3;86,87,69;,
 3;48,141,49;,
 3;87,108,92;,
 3;108,109,92;,
 3;48,122,141;,
 3;122,123,141;,
 3;2,24,3;,
 3;6,63,7;,
 3;24,23,3;,
 3;63,32,7;,
 3;32,51,33;,
 3;51,50,33;,
 3;36,142,37;,
 3;142,143,37;,
 3;143,60,37;,
 3;56,104,57;,
 3;104,105,57;,
 3;93,111,144;,
 3;60,118,61;,
 3;111,115,144;,
 3;143,118,60;,
 3;118,119,61;,
 3;10,145,19;,
 3;145,146,19;,
 3;25,43,29;,
 3;43,42,29;,
 3;10,82,145;,
 3;147,90,148;,
 3;82,83,145;,
 3;90,91,148;,
 3;146,149,19;,
 3;91,150,148;,
 3;149,151,19;,
 3;52,152,53;,
 3;150,112,153;,
 3;91,112,150;,
 3;112,113,153;,
 3;152,126,53;,
 3;126,127,53;,
 3;44,100,45;,
 3;100,101,45;,
 3;64,9,76;,
 3;78,64,76;,
 3;66,9,64;,
 3;10,9,66;,
 3;10,66,80;,
 3;82,10,80;,
 3;87,85,106;,
 3;108,87,106;,
 3;71,69,87;,
 3;89,71,87;,
 3;91,89,110;,
 3;112,91,110;,
 3;93,92,109;,
 3;111,93,109;,
 3;40,39,94;,
 3;96,40,94;,
 3;22,21,40;,
 3;72,22,40;,
 3;2,1,22;,
 3;24,2,22;,
 3;25,24,74;,
 3;43,25,74;,
 3;44,43,98;,
 3;100,44,98;,
 3;48,47,135;,
 3;48,135,120;,
 3;122,48,120;,
 3;32,31,48;,
 3;51,32,48;,
 3;52,51,124;,
 3;152,52,124;,
 3;126,152,124;,
 3;56,55,102;,
 3;104,56,102;,
 3;18,35,134;,
 3;136,92,107;,
 3;35,137,134;,
 3;92,109,107;,
 3;18,36,35;,
 3;18,19,36;,
 3;36,19,142;,
 3;93,153,111;,
 3;19,151,142;,
 3;153,113,111;,
 3;34,37,59;,
 3;37,60,59;,
 3;58,61,117;,
 3;61,119,117;,
 3;38,41,95;,
 3;41,97,95;,
 3;26,27,41;,
 3;27,73,41;,
 3;4,7,31;,
 3;7,32,31;,
 3;28,29,75;,
 3;29,42,75;,
 3;42,45,99;,
 3;45,101,99;,
 3;46,49,121;,
 3;49,141,121;,
 3;141,123,121;,
 3;30,33,49;,
 3;33,50,49;,
 3;140,53,125;,
 3;50,53,140;,
 3;53,127,125;,
 3;54,57,103;,
 3;57,105,103;;
 
 MeshMaterialList {
  1;
  244;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "obj\\knight.png";
   }
  }
 }
 MeshNormals {
  6;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  244;
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
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;;
 }
 MeshTextureCoords {
  154;
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.908200;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.876950;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.904300;0.500000;,
  0.904300;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.099610;0.500000;,
  0.095700;0.500000;,
  0.904300;0.500000;,
  0.099610;0.500000;;
 }
}