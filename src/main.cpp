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



#include <writer.h>

#include <windows.h>

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

void extractPolygons(json::Object& jsonObject) {
  MStatus stat;
  MItDag dagIter(MItDag::kBreadthFirst, MFn::kInvalid, &stat);

  json::Array meshesJSONArray;

  for (; !dagIter.isDone(); dagIter.next()) {
    MDagPath dagPath;
    stat = dagIter.getPath(dagPath);
    if (!stat) { continue; };

    json::Object meshJSONObject;
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

    json::Array verticesJSONArray;
    json::Array normalsJSONArray;
    json::Array uvsJSONArray;

    MItMeshPolygon itPolygon(dagPath, comps[0]);
    //itPolygon.next();

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
          {
            MInt64 vertexCount = vertexList.length();
            
            {
              MInt64 vertexIndex0 = triangleVertices[0];
              MPoint point0 = vertexList[vertexIndex0];

              json::Number xJSONNumber = point0.x;
              verticesJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point0.y;
              verticesJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point0.z;
              verticesJSONArray.Insert(zJSONNumber);
            }


            {
              MInt64 vertexIndex1 = triangleVertices[1];
              MPoint point1 = vertexList[vertexIndex1];

              json::Number xJSONNumber = point1.x;
              verticesJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point1.y;
              verticesJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point1.z;
              verticesJSONArray.Insert(zJSONNumber);
            }

            {
              MInt64 vertexIndex2 = triangleVertices[2];
              MPoint point2= vertexList[vertexIndex2];

              json::Number xJSONNumber = point2.x;
              verticesJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point2.y;
              verticesJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point2.z;
              verticesJSONArray.Insert(zJSONNumber);
            }

          }

          { // normals

            // Get face-relative vertex indices for this triangle
            localIndex = GetLocalIndex(polygonVertices, triangleVertices);

            {
              MInt64 index0 = itPolygon.normalIndex(localIndex[0]);
              MPoint point0 = meshNormals[index0];

              json::Number xJSONNumber = point0.x;
              normalsJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point0.y;
              normalsJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point0.z;
              normalsJSONArray.Insert(zJSONNumber);
            }


            {
              MInt64 index1 = itPolygon.normalIndex(localIndex[1]);
              MPoint point1 = meshNormals[index1];

              json::Number xJSONNumber = point1.x;
              normalsJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point1.y;
              normalsJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point1.z;
              normalsJSONArray.Insert(zJSONNumber);
            }

            {
              MInt64 index2 = itPolygon.normalIndex(localIndex[2]);
              MPoint point2 = meshNormals[index2];

              json::Number xJSONNumber = point2.x;
              normalsJSONArray.Insert(xJSONNumber);

              json::Number yJSONNumber = point2.y;
              normalsJSONArray.Insert(yJSONNumber);

              json::Number zJSONNumber = point2.z;
              normalsJSONArray.Insert(zJSONNumber);
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

              json::Number uJSONNumber = uvu;
              uvsJSONArray.Insert(uJSONNumber);

              json::Number vJSONNumber = uvv;
              uvsJSONArray.Insert(vJSONNumber);
            }


            {
              MInt64 index0 = uvID[1];

              float uvu = u[index0];
              float uvv = v[index0];

              json::Number uJSONNumber = uvu;
              uvsJSONArray.Insert(uJSONNumber);

              json::Number vJSONNumber = uvv;
              uvsJSONArray.Insert(vJSONNumber);
            }


            {
              MInt64 index0 = uvID[2];

              float uvu = u[index0];
              float uvv = v[index0];

              json::Number uJSONNumber = uvu;
              uvsJSONArray.Insert(uJSONNumber);

              json::Number vJSONNumber = uvv;
              uvsJSONArray.Insert(vJSONNumber);
            }
          }
        }
        
      }

      {
        json::Object materialJSONObject;

        materialJSONObject["effect"] = json::String("cgfx/deferred_render_color_normal_depth.hlsl");

        json::Object parametersJSONObject;

        {
          json::Object specularPowerJSONObject;
          specularPowerJSONObject["value"] = json::Number(80);
          specularPowerJSONObject["type"] = json::String("float");

          parametersJSONObject["SpecularPower"] = specularPowerJSONObject;
        }

        {
          json::Object specularIntensityJSONObject;
          specularIntensityJSONObject["value"] = json::Number(0.5f);
          specularIntensityJSONObject["type"] = json::String("float");

          parametersJSONObject["SpecularIntensity"] = specularIntensityJSONObject;
        }

        {
          json::Object diffusePowerJSONObject;
          diffusePowerJSONObject["value"] = json::Number(0.01f);
          diffusePowerJSONObject["type"] = json::String("float");

          parametersJSONObject["DiffusePower"] = diffusePowerJSONObject;
        }

        materialJSONObject["parameters"] = parametersJSONObject;
        materialJSONObject["textures"] = json::Object();

        meshJSONObject["material"] = materialJSONObject; 

      }
    }

    std::clog << "Processed " << polyCount << " polygons" << std::endl;

    meshJSONObject["vertices"] = verticesJSONArray;
    meshJSONObject["normals"] = normalsJSONArray;
    meshJSONObject["uvs"] = uvsJSONArray;

    meshesJSONArray.Insert(meshJSONObject);
  }

  jsonObject["submeshes"] = meshesJSONArray;
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

  json::Object jsonObject;
  extractPolygons(jsonObject);

  std::ofstream outputFile(outputFilename);
  json::Writer::Write(jsonObject, outputFile);

  std::clog << "Compilation finished" << std::endl;

  MLibrary::cleanup();

  return 0;
}