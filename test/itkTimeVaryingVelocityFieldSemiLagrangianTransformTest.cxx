/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkTimeVaryingVelocityFieldSemiLagrangianTransform.h"
#include "itkImageFileWriter.h"
#include "itkTestingMacros.h"


int itkTimeVaryingVelocityFieldSemiLagrangianTransformTest( int argc, char * argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " outputImage";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  constexpr unsigned int Dimension = 2;

  using ParametersValueType = double;

  using TimeVaryingVelocityFieldSemiLagrangianTransformType =
    itk::TimeVaryingVelocityFieldSemiLagrangianTransform< ParametersValueType, Dimension >;
  TimeVaryingVelocityFieldSemiLagrangianTransformType::Pointer timeVaryingVelocityFieldSemiLagrangianTransform =
    TimeVaryingVelocityFieldSemiLagrangianTransformType::New();

  EXERCISE_BASIC_OBJECT_METHODS( timeVaryingVelocityFieldSemiLagrangianTransform,
    TimeVaryingVelocityFieldSemiLagrangianTransform, TimeVaryingVelocityFieldTransform );


  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
