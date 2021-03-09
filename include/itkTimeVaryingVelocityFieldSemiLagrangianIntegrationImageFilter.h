/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#ifndef itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter_h
#define itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter_h

#include "itkExtrapolateImageFunction.h"
#include "itkWrapExtrapolateImageFunction.h"
#include "itkTimeVaryingVelocityFieldIntegrationImageFilter.h"

namespace itk
{
/**
 * \class TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter
 * \brief Integrate a time-varying velocity field using a Semi-Lagrangian scheme.
 *
 *
 * \warning The output deformation field needs to have dimensionality of 1
 * less than the input time-varying velocity field.
 *
 * \ingroup NDReg
 */
template<typename TTimeVaryingVelocityField, typename TDisplacementField =
 Image<typename TTimeVaryingVelocityField::PixelType,
 TTimeVaryingVelocityField::ImageDimension - 1> >
class TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter :
  public TimeVaryingVelocityFieldIntegrationImageFilter<TTimeVaryingVelocityField, TDisplacementField>
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter);

  using Self = TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter;
  using Superclass = TimeVaryingVelocityFieldIntegrationImageFilter
    <TTimeVaryingVelocityField, TDisplacementField>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information ( and related methods ) */
  itkTypeMacro( TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter, TimeVaryingVelocityFieldIntegrationImageFilter );

  /**
   * Dimensionality of input data is assumed to be one more than the output
   * data the same. */


  itkStaticConstMacro( InputImageDimension, unsigned int,
    TTimeVaryingVelocityField::ImageDimension );

  itkStaticConstMacro( OutputImageDimension, unsigned int,
    TDisplacementField::ImageDimension );

  using TimeVaryingVelocityFieldType = TTimeVaryingVelocityField;
  using DisplacementFieldType = TDisplacementField;
  using VectorType = typename Superclass::VectorType;
  using RealType = typename Superclass::RealType;
  using ScalarType = typename Superclass::ScalarType;
  using PointType = typename Superclass::PointType;
  using OutputRegionType = typename DisplacementFieldType::RegionType;

  using VelocityFieldInterpolatorPointer = typename Superclass::VelocityFieldInterpolatorPointer;

  using VelocityFieldExtrapolatorType = ExtrapolateImageFunction<TimeVaryingVelocityFieldType, ScalarType>;
  using VelocityFieldExtrapolatorPointer = typename VelocityFieldExtrapolatorType::Pointer;

  using DisplacementFieldExtrapolatorType = ExtrapolateImageFunction<DisplacementFieldType, ScalarType>;
  using DisplacementFieldExtrapolatorPointer = typename DisplacementFieldExtrapolatorType::Pointer;

  /**
   * Get/Set the time-varying velocity field extrapolator.  Default = linear. 
   */
  itkSetObjectMacro( VelocityFieldExtrapolator, VelocityFieldExtrapolatorType );
  itkGetModifiableObjectMacro(VelocityFieldExtrapolator, VelocityFieldExtrapolatorType );

  /**
   * Get/Set the deformation field extrapolator for the initial diffeomorphism
   * (if set).
   */
  itkSetObjectMacro( DisplacementFieldExtrapolator, DisplacementFieldExtrapolatorType );
  itkGetModifiableObjectMacro(DisplacementFieldExtrapolator, DisplacementFieldExtrapolatorType );

  /**
   * Get the number of iterations used per integration steps.
   */
  itkGetConstMacro( NumberOfIterations, unsigned int );


protected:
  TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter();
  ~TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter() override = default;

  void PrintSelf( std::ostream & os, Indent indent ) const override;
  void BeforeThreadedGenerateData() override;
  void ThreadedGenerateData( const OutputRegionType &, ThreadIdType ) override;
  VectorType IntegrateVelocityAtPoint( const PointType &initialSpatialPoint, const TimeVaryingVelocityFieldType * inputField );

  DisplacementFieldExtrapolatorPointer      m_DisplacementFieldExtrapolator;
 
private:

  VelocityFieldInterpolatorPointer          m_VelocityFieldInterpolator;
  VelocityFieldExtrapolatorPointer          m_VelocityFieldExtrapolator;
  unsigned int                              m_NumberOfIterations;
  RealType                                  m_DeltaTime;
  RealType                                  m_TimeSpan;
  RealType                                  m_TimeOrigin;
};
}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter.hxx"
#endif

#endif
