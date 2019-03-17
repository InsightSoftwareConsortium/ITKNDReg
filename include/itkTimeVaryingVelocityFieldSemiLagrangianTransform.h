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
#ifndef itkTimeVaryingVelocityFieldSemiLagrangianTransform_h
#define itkTimeVaryingVelocityFieldSemiLagrangianTransform_h

#include "itkTimeVaryingVelocityFieldTransform.h"

namespace itk
{

/** \class TimeVaryingVelocityFieldSemiLagrangianTransform
 * \brief Transform objects based on integration of a time-varying velocity
 * field using Semi-Lagrangian advection.
 *
 *
 * \ingroup Transforms
 * \ingroup NDReg
 */
template<typename TParametersValueType, unsigned int NDimensions>
class TimeVaryingVelocityFieldSemiLagrangianTransform :
  public TimeVaryingVelocityFieldTransform<TParametersValueType, NDimensions>
{
public:
  /** Standard class type alias. */
  using Self = TimeVaryingVelocityFieldSemiLagrangianTransform;
  using Superclass = TimeVaryingVelocityFieldTransform<TParametersValueType, NDimensions>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Run-time type information (and related methods). */
  itkTypeMacro( TimeVaryingVelocityFieldSemiLagrangianTransform, TimeVaryingVelocityFieldTransform );

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro( Self );

  /** InverseTransform type. */
  using InverseTransformBasePointer = typename Superclass::InverseTransformBasePointer;

  /** Interpolator types.*/
  using InterpolatorType = typename Superclass::InterpolatorType;

  /** Field types. */
  using DisplacementFieldType = typename Superclass::DisplacementFieldType;
  using VelocityFieldType = typename Superclass::VelocityFieldType;

  using TimeVaryingVelocityFieldType = typename Superclass::TimeVaryingVelocityFieldType;
  using TimeVaryingVelocityFieldPointer = typename Superclass::TimeVaryingVelocityFieldPointer;

  /** Scalar type. */
  using ScalarType = typename Superclass::ScalarType;

  /** Type of the input parameters. */
  using ParametersType = typename Superclass::ParametersType;
  using ParametersValueType = typename Superclass::ParametersValueType;
  using FixedParametersType = typename Superclass::FixedParametersType;
  using FixedParametersValueType = typename Superclass::FixedParametersValueType;
  using NumberOfParametersType = typename Superclass::NumberOfParametersType;

  /** Derivative type */
  using DerivativeType = typename Superclass::DerivativeType;
  using TransformPointer = typename Superclass::TransformPointer;

  /** Trigger the computation of the displacement field by integrating
   * the time-varying velocity field. */
  virtual void IntegrateVelocityField() ITK_OVERRIDE;
  itkBooleanMacro(UseInverse);
  itkSetMacro(UseInverse, bool);
  itkGetConstMacro(UseInverse, bool);

protected:
  TimeVaryingVelocityFieldSemiLagrangianTransform();
  virtual ~TimeVaryingVelocityFieldSemiLagrangianTransform(){};

private:
  TimeVaryingVelocityFieldSemiLagrangianTransform( const Self& ) ITK_DELETE_FUNCTION;
  void operator=( const Self& ) ITK_DELETE_FUNCTION;
  bool m_UseInverse;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
# include "itkTimeVaryingVelocityFieldSemiLagrangianTransform.hxx"
#endif

#endif // itkTimeVaryingVelocityFieldSemiLagrangianTransform_h
