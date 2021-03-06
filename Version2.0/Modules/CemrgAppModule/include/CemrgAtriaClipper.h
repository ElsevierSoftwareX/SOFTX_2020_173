/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
/*=========================================================================
 *
 * Atrial Clipper
 *
 * Cardiac Electromechanics Research Group
 * http://www.cemrgapp.com
 * orod.razeghi@kcl.ac.uk
 *
 * This software is distributed WITHOUT ANY WARRANTY or SUPPORT!
 *
=========================================================================*/

#ifndef CemrgAtriaClipper_h
#define CemrgAtriaClipper_h

#include <mitkSurface.h>
#include <mitkImage.h>
#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkRegularPolygonSource.h>
#include <vmtk/vtkvmtkPolyDataCenterlines.h>
#include <vmtk/vtkvmtkPolyDataCenterlineSections.h>
#include <QString>

// The following header file is generated by CMake and thus it's located in
// the build directory. It provides an export macro for classes and functions
// that you want to be part of the public interface of your module.
#include <MitkCemrgAppModuleExports.h>

class MITKCEMRGAPPMODULE_EXPORT CemrgAtriaClipper {

public:

    CemrgAtriaClipper(QString directory, mitk::Surface::Pointer surface);

    void ComputeCtrLines(std::vector<int> pickedSeedLabels, vtkSmartPointer<vtkIdList> pickedSeedIds, bool flip);
    void ComputeCtrLinesClippers(std::vector<int> pickedSeedLabels);
    void ClipVeinsMesh(std::vector<int> pickedSeedLabels);
    void ClipVeinsImage(std::vector<int> pickedSeedLabels, mitk::Image::Pointer segImage, bool morphAnalysis);
    void CalcParamsOfPlane(vtkSmartPointer<vtkRegularPolygonSource> plane, int ctrLineNo, int position);
    void ResetCtrLinesClippingPlanes();

    mitk::Image::Pointer GetClippedSegImage() const;
    mitk::Surface::Pointer GetClippedSurface() const;
    std::vector<vtkSmartPointer<vtkvmtkPolyDataCenterlines>> GetCentreLines() const;
    std::vector<vtkSmartPointer<vtkRegularPolygonSource>> GetCentreLinePolyPlanes() const;
    std::vector<std::vector<double>> GetMClipperAngles();
    std::vector<int> GetManualType() const;
    void SetToAutomaticClipperMode(int clippersIndex);
    void SetMClipperAngles(double* value, int clippersIndex);
    void SetMClipperSeeds(vtkSmartPointer<vtkPolyData> pickedCutterSeeds, int clippersIndex);
    void SetRadiusAdjustment(double value);

private:

    vtkIdType CentreOfMass(mitk::Surface::Pointer surface);
    void VTKWriter(vtkSmartPointer<vtkPolyData> PD, QString path);

    QString directory;
    mitk::Surface::Pointer surface;
    mitk::Surface::Pointer clippedSurface;
    mitk::Image::Pointer clippedSegImage;
    std::vector<vtkSmartPointer<vtkPolyData>> centreLineVeinPlanes;
    std::vector<vtkSmartPointer<vtkRegularPolygonSource>> centreLinePolyPlanes;
    std::vector<vtkSmartPointer<vtkPoints>> centreLinePointPlanes;
    std::vector<vtkSmartPointer<vtkvmtkPolyDataCenterlines>> centreLines;

    //Default variables
    double maxiSlope = 200.0; //Anything above this is ostium
    double highSlope = 80.00; //Above this slope we start counting
    double criterion = 0.025; //Ostium if slope higher than highslope and above bump criterion
    double clSpacing = 2.000; //Resample the centerline with this spacing
    double radiusAdj = 2.000; //Adjustment for cutter planes radii

    //Cutters properties
    std::vector<int> manuals; //Cutter's tilt manual or automatic
    std::vector<std::vector<double>> normalPlAngles; //Cutter's tilt adjustments

    //Constant Vein Labels
    //const int LEFTSUPERIORPV  = 11;
    //const int LEFTMIDDLEPV    = 12;
    //const int LEFTINFERIORPV  = 13;
    //const int LEFTCOMMONPV    = 14;
    //const int RIGHTSUPERIORPV = 15;
    //const int RIGHTMIDDLEPV   = 16;
    //const int RIGHTINFERIORPV = 17;
    //const int RIGHTCOMMONPV   = 18;
    //const int APPENDAGECUT    = 19;
    const int APPENDAGEUNCUT  = 20;
    //const int DEFAULTVALUE    = 21;
};

#endif // CemrgAtriaClipper_h
