#define _BOOL bool
#include <iostream>
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

#include <windows.h>

void extractPolygons()
{
  MStatus stat;
  MItDag dagIter( MItDag::kBreadthFirst, MFn::kInvalid, &stat );

  for ( ; !dagIter.isDone(); dagIter.next())
  {
    MDagPath dagPath;
    stat = dagIter.getPath( dagPath );


    if ( stat )
    {
      MFnDagNode dagNode( dagPath, &stat );

      if ( dagNode.isIntermediateObject()) continue;
      if ( !dagPath.hasFn( MFn::kMesh )) continue;
      if ( dagPath.hasFn( MFn::kTransform )) continue;

      // get the mesh and all its vertices
      MFnMesh fnMesh( dagPath );

     // MPointArray meshPoints;
     // fnMesh.getPoints( meshPoints, MSpace::kObject );

      MPointArray vertexList;
      fnMesh.getPoints( vertexList, MSpace::kWorld );

      unsigned instanceNumber = dagPath.instanceNumber();
      MObjectArray sets;
      MObjectArray comps;
      fnMesh.getConnectedSetsAndMembers( instanceNumber, sets, comps, true );

      MItMeshPolygon  itPolygon( dagPath, MObject::kNullObj );
      for ( /* nothing */; !itPolygon.isDone(); itPolygon.next() )
      {
        // Get object-relative indices for the vertices in this face.
        MIntArray                           polygonVertices;
        itPolygon.getVertices( polygonVertices );

        int count;
        // Get triangulation of this poly.
        itPolygon.numTriangles(count);
        while ( count-- )
        {
          MPointArray                     nonTweaked;
          // object-relative vertex indices for each triangle
          MIntArray                       triangleVertices;
          // face-relative vertex indices for each triangle
          MIntArray                       localIndex;

          MStatus  status;
          status = itPolygon.getTriangle( count, nonTweaked, triangleVertices, MSpace::kObject );

          if ( status == MS::kSuccess )
          {

            // --------  Get Positions  --------

            // While it may be tempting to use the points array returned
            // by MItMeshPolygon::getTriangle(), don't. It does not represent
            // poly tweaks in its coordinates!

            // Positions are:
            //  { vertexList[triangleVertices[0]],
            //    vertexList[triangleVertices[1]],
            //    vertexList[triangleVertices[2]] }

            MInt64 vertexCount = vertexList.length();

            MInt64 vertexIndex0 = triangleVertices[0];
            MPoint point0 = vertexList[vertexIndex0];

            MInt64 vertexIndex1 = triangleVertices[1];
            MPoint point1 = vertexList[vertexIndex1];

            MInt64 vertexIndex2 = triangleVertices[2];
            MPoint point2 = vertexList[vertexIndex2];



            std::stringstream output;
            output << point0.x << " " << point0.y << " " << point0.z << std::endl;
            output << point1.x << " " << point1.y << " " << point1.z << std::endl;
            output << point2.x << " " << point2.y << " " << point2.z << std::endl;

            OutputDebugStringA(output.str().c_str());
          }
        }
      }
    }
  }
}

void extractVertices()
{
  // we assume here that Maya has been initialized and the file in
  // question has already been loaded.

  MStatus stat;
  MItDag dagIter( MItDag::kBreadthFirst, MFn::kInvalid, &stat );

  for ( ; !dagIter.isDone(); dagIter.next())
  {
    MDagPath dagPath;
    stat = dagIter.getPath( dagPath );

    if ( stat )
    {
      MFnDagNode dagNode( dagPath, &stat );

      std::stringstream output;
      output << "Found DAG Node: "
        << dagPath.fullPathName().asChar()
        << std::endl;

      OutputDebugStringA(output.str().c_str());

      // this object cannot be intermediate, and it must be a mesh
      // and it can't be a transform.
      // Intermediate objects are special meshes
      // that are not drawn used for mesh morphs or something.
      if ( dagNode.isIntermediateObject()) continue;
      if ( !dagPath.hasFn( MFn::kMesh )) continue;
      if ( dagPath.hasFn( MFn::kTransform )) continue;

      MFnMesh fnMesh( dagPath );

      // get the vertices that are part of the current mesh
      MPointArray vertexlist;
      fnMesh.getPoints( vertexlist, MSpace::kWorld );

      // iterate through all the vertices
      for ( unsigned int i = 0; i < vertexlist.length(); i++ )
      {
        vertexlist[i].cartesianize();
        MPoint point = vertexlist[i];

        // here is your data... now go do whatever you want with
        // it. if you need a unique identifier for this vertex,
        // use it's index in the mesh, and some kind of mesh id.
        // these stay constant while exporting ( so long as the file is
        // not edited )
        //processvertex( point.x, point.y, point.z );

        std::stringstream output;
        output << "Found DAG Node: "
          << point.x << " " << point.y << " " << point.z << std::endl;

        OutputDebugStringA(output.str().c_str());
      }
    }
  }
}

// initialize Maya, before any Maya operations are performed.
// You might do this in main for example:
int main(int argc, char **argv) 
{
  MStatus stat = MLibrary::initialize(argv[0]);
  if ( !stat )
    return 1;

  // figure out the file name to open
  char* fileName = argv[1];

  // prepare Maya to read a new scene file
  MFileIO::newFile( true );

  // read the scene file
  stat = MFileIO::open( fileName );
  if ( !stat )
    return 1;

  // remove any temporary data created by Maya while loading
  // things like the undo list which we won't be using
  stat = MGlobal::executeCommand( "delete -ch" );
  if ( !stat )
    return 1;

  extractPolygons();

  // now shut down Maya, or if you want to process another file,
  // just make another call to MFileIO::newFile(), and MFileIO::open()
  MLibrary::cleanup();

  return 0;
}