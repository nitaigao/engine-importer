#define _BOOL bool
#include <iostream>
#include <fstream>
#include <sstream>

#include <maya/MArgList.h>
#include <maya/MFileObject.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>

#include <maya/MSimple.h>
#include <maya/MStatus.h>
#include <maya/MObject.h>
#include <maya/MFnPlugin.h>
#include <maya/MLibrary.h>
#include <maya/MFileIO.h>
#include <maya/MGlobal.h>
#include <maya/MItDag.h>
#include <maya/MDagPath.h>
#include <maya/MFnDagNode.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFnLambertShader.h>


#include <writer.h>

#include <windows.h>

#include "BinaryFileWriter.h"
#include "JSONFileWriter.h"
#include "ModelFile.h"
#include "VertexDefinition.h"
#include "SubMesh.h"
#include "Material.h"

#include "Vector3MaterialParameter.h"
#include "FloatMaterialParameter.h"

MIntArray GetLocalIndex( MIntArray & getVertices, MIntArray & getTriangle )
{
  MIntArray   localIndex;
  unsigned    gv, gt;

  assert ( getTriangle.length() == 3 );    // Should always deal with a triangle

  for ( gt = 0; gt < getTriangle.length(); gt++ )
  {
    for ( gv = 0; gv < getVertices.length(); gv++ )
    {
      if ( getTriangle[gt] == getVertices[gv] )
      {
        localIndex.append( gv );
        break;
      }
    }

    // if nothing was added, add default "no match"
    if ( localIndex.length() == gt )
      localIndex.append( -1 );
  }

  return localIndex;
}

inline float clamp(float x, float a, float b)
{
  return x < a ? a : (x > b ? b : x);
}

void extractPolygons(ModelFile& modelFile) {
  MStatus stat;
  MItDag dagIter(MItDag::kBreadthFirst, MFn::kInvalid, &stat);

 for (; !dagIter.isDone(); dagIter.next()) {
    MDagPath dagPath;
    stat = dagIter.getPath(dagPath);
    if (!stat) { continue; };

    MFnDagNode dagNode(dagPath, &stat);

    if (dagNode.isIntermediateObject()) continue;
    if (!dagPath.hasFn( MFn::kMesh )) continue;
    if (dagPath.hasFn( MFn::kTransform)) continue;

    MFnMesh fnMesh(dagPath);
    
    MStringArray  UVSets;
    stat = fnMesh.getUVSetNames( UVSets );

    // Get all UVs for the first UV set.
    MFloatArray   u, v;
    fnMesh.getUVs(u, v, &UVSets[0]);


    MPointArray vertexList;
    fnMesh.getPoints(vertexList, MSpace::kObject);

    MFloatVectorArray  meshNormals;
    fnMesh.getNormals(meshNormals);


    unsigned instanceNumber = dagPath.instanceNumber();
    MObjectArray sets;
    MObjectArray comps;
    fnMesh.getConnectedSetsAndMembers( instanceNumber, sets, comps, true );

    unsigned int comlength = comps.length();

    for (unsigned int compi = 0; compi < comlength; compi++) {

      SubMesh submesh;

      MItMeshPolygon itPolygon(dagPath, comps[compi]);

      unsigned int polyCount = 0;
      for (; !itPolygon.isDone(); itPolygon.next()) {
        polyCount++;
        MIntArray                           polygonVertices;
        itPolygon.getVertices(polygonVertices);

        int count;
        itPolygon.numTriangles(count);

        for (; count > -1; count--) {
          MPointArray                     nonTweaked;
          MIntArray                       triangleVertices;
          MIntArray                       localIndex;

          MStatus  status;
          status = itPolygon.getTriangle(count, nonTweaked, triangleVertices, MSpace::kObject);

          if (status == MS::kSuccess) {

            VertexDefinition vertex1;
            VertexDefinition vertex2;
            VertexDefinition vertex3;

            { // vertices

              MInt64 vertexCount = vertexList.length();
              
              {
                MInt64 vertexIndex0 = triangleVertices[0];
                MPoint point0 = vertexList[vertexIndex0];

                vertex1.vertex.x = point0.x;
                vertex1.vertex.y = point0.y;
                vertex1.vertex.z = point0.z;
              }

              {
                MInt64 vertexIndex0 = triangleVertices[1];
                MPoint point0 = vertexList[vertexIndex0];

                vertex2.vertex.x = point0.x;
                vertex2.vertex.y = point0.y;
                vertex2.vertex.z = point0.z;
              }

              {
                MInt64 vertexIndex0 = triangleVertices[2];
                MPoint point0 = vertexList[vertexIndex0];

                vertex3.vertex.x = point0.x;
                vertex3.vertex.y = point0.y;
                vertex3.vertex.z = point0.z;
              }

            }

            { // normals

              // Get face-relative vertex indices for this triangle
              localIndex = GetLocalIndex(polygonVertices, triangleVertices);

              {
                MInt64 index0 = itPolygon.normalIndex(localIndex[0]);
                MPoint point0 = meshNormals[index0];

                vertex1.normal.x = point0.x;
                vertex1.normal.y = point0.y;
                vertex1.normal.z = point0.z;
              }

              {
                MInt64 index0 = itPolygon.normalIndex(localIndex[1]);
                MPoint point0 = meshNormals[index0];

                vertex2.normal.x = point0.x;
                vertex2.normal.y = point0.y;
                vertex2.normal.z = point0.z;
              }

              {
                MInt64 index0 = itPolygon.normalIndex(localIndex[2]);
                MPoint point0 = meshNormals[index0];

                vertex3.normal.x = point0.x;
                vertex3.normal.y = point0.y;
                vertex3.normal.z = point0.z;
              }
            }

            { // uvs

              int uvID[3];

              for (unsigned int vtxInPolygon = 0; vtxInPolygon < 3; vtxInPolygon++) {
                itPolygon.getUVIndex(localIndex[vtxInPolygon], uvID[vtxInPolygon]);
              }


              {
                MInt64 index0 = uvID[0];
                float uvu = u[index0];
                float uvv = v[index0];

                vertex1.uv.x = uvu;
                vertex1.uv.y = 1.0f - uvv;
              }

              {
                MInt64 index0 = uvID[1];
                float uvu = u[index0];
                float uvv = v[index0];

                vertex2.uv.x = uvu;
                vertex2.uv.y = 1.0f - uvv;
              }
              
              {
                MInt64 index0 = uvID[2];
                float uvu = u[index0];
                float uvv = v[index0];

                vertex3.uv.x = uvu;
                vertex3.uv.y = 1.0f - uvv; // directx
              }
            }

            submesh.addVertex(vertex1);
            submesh.addVertex(vertex2);
            submesh.addVertex(vertex3);
          }
        }
      }

      {
        Material material;

        material.setEffect("cgfx/deferred_render_color_normal_depth.hlsl");

        {
          MObjectArray shaders;
          MIntArray indices;
          fnMesh.getConnectedShaders(0, shaders, indices);
          for(unsigned int i = 0; i < shaders.length(); i++)
          {
            MPlugArray connections;
            MFnDependencyNode shaderGroup(shaders[i]);
            MPlug shaderPlug = shaderGroup.findPlug("surfaceShader");
            shaderPlug.connectedTo(connections, true, false);
            for(unsigned int u = 0; u < connections.length(); u++)
            {
              if(connections[u].node().hasFn(MFn::kLambert))
              {
                MPlugArray plugs;
                MFnLambertShader lambertShader(connections[u].node());
                lambertShader.findPlug("color").connectedTo(plugs, true, false);

                MColor color = lambertShader.color();

                Vector3MaterialParameter* diffuseColorParameter = new Vector3MaterialParameter("DiffuseColor");
                diffuseColorParameter->value.x = color.r;
                diffuseColorParameter->value.y = color.g;
                diffuseColorParameter->value.z = color.b;

                material.addParameter(diffuseColorParameter);
              }
            }
          }
        }

        {
          FloatMaterialParameter* specularPowerParameter = new FloatMaterialParameter("SpecularPower");
          specularPowerParameter->value = 1.0;
          material.addParameter(specularPowerParameter);
        }

        {
          FloatMaterialParameter* specularIntensityParameter = new FloatMaterialParameter("SpecularIntensity");
          specularIntensityParameter->value = 1.0f;
          material.addParameter(specularIntensityParameter);
        }

        {
          FloatMaterialParameter* diffusePowerParameter = new FloatMaterialParameter("DiffusePower");
          diffusePowerParameter->value = 1.0f;
          material.addParameter(diffusePowerParameter);
        }

        submesh.setMaterial(material);
      }

      modelFile.addSubMesh(submesh);
    }
  }
}

int main(int argc, char **argv)  {
  MStatus stat = MLibrary::initialize(argv[0]);
  if (!stat) {
    std::cerr << "Failed to initialize Maya" << std::endl;
    return 1;
  }
    
  char* inputFilename = argv[1];
  char* outputFilename = argv[2];
  std::clog << "Compiling " << inputFilename << " to " << outputFilename << "." << std::endl;

  // prepare Maya to read a new scene file
  MFileIO::newFile(true);

  stat = MFileIO::open(inputFilename);
  if ( !stat ) {
    std::cerr << "Failed to open maya source file: " << stat.errorString().asUTF8() << std::endl;
    return 1;
  }

  stat = MGlobal::executeCommand( "delete -ch" );
  if (!stat) {
    std::cerr << "Failed to cleanup maya source objects" << std::endl;
    return 1;
  }
  
  ModelFile modelFile;
  extractPolygons(modelFile);

  IFileWriter* writer = new BinaryFileWriter();
  writer->openFile(outputFilename);

  modelFile.write(writer);

  writer->close();

  std::clog << "Compilation finished" << std::endl;

  MLibrary::cleanup();

  return 0;
}