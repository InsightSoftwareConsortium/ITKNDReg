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
#ifndef itkWrapExtrapolateImageFunction_h
#define itkWrapExtrapolateImageFunction_h

#include "itkExtrapolateImageFunction.h"
#include "itkLinearInterpolateImageFunction.h"
namespace itk
{
/** \class WrapExtrapolateImageFunction
 * \brief Wrap extrapolation of a scalar image.
 *
 * WrapExtrapolateImageFunction wraps specified point, continuous index or index to obtain
 * the intensity of pixel within the image buffer.
 *
 * This class is templated
 * over the input image type and the coordinate representation type
 * (e.g. float or double).
 *
 * \ingroup ImageFunctions
 * \ingroup NDReg
 */
template< typename TInputImage, typename TCoordRep = float >
class WrapExtrapolateImageFunction:
  public ExtrapolateImageFunction< TInputImage, TCoordRep >
{
public:
  /** Standard class type alias. */
  using Self = WrapExtrapolateImageFunction;
  using Superclass = ExtrapolateImageFunction< TInputImage, TCoordRep >;
  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;

  /** Run-time type information (and related methods). */
  itkTypeMacro(WrapExtrapolateImageFunction,
               InterpolateImageFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** OutputType type alias support. */
  using OutputType = typename Superclass::OutputType;

  /** InputImageType type alias support. */
  using InputImageType = typename Superclass::InputImageType;

  /** Dimension underlying input image. */
  itkStaticConstMacro(ImageDimension, unsigned int, Superclass::ImageDimension);

  /** Index type alias support. */
  using IndexType = typename Superclass::IndexType;
  using IndexValueType = typename IndexType::IndexValueType;

  /** ContinuousIndex type alias support. */
  using ContinuousIndexType = typename Superclass::ContinuousIndexType;

  /** Interpolator type alias support. */
  using InterpolatorType = InterpolateImageFunction<InputImageType, TCoordRep>;
  using InterpolatorPointerType = typename InterpolatorType::Pointer;

  using LinearInterpolatorType = LinearInterpolateImageFunction<InputImageType, TCoordRep>;
  using LinearInterpolatorPointerType = typename LinearInterpolatorType::Pointer;

  itkGetModifiableObjectMacro(Interpolator, InterpolatorType);

  /** Evaluate the function at a ContinuousIndex position
   *
   * Returns the extrapolated image intensity at a
   * specified position
   */
  OutputType EvaluateAtContinuousIndex(
    const ContinuousIndexType & index) const override
  {

    ContinuousIndexType nindex;

    for ( unsigned int j = 0; j < ImageDimension; j++ )
    {
      nindex[j] = index[j];
      typename ContinuousIndexType::ValueType size = this->GetEndContinuousIndex()[j] - this->GetStartContinuousIndex()[j];

      while(nindex[j] > this->GetEndIndex()[j])
      {
        nindex[j] -= size;
      }
      while(nindex[j] < this->GetStartIndex()[j])
      {
        nindex[j] += size;
      }
    }


    return static_cast< OutputType >( m_Interpolator->EvaluateAtContinuousIndex(nindex) );
  }


  void SetInputImage(const InputImageType*ptr) override
  {
    Superclass::SetInputImage(ptr);
    m_Interpolator->SetInputImage(this->GetInputImage());
  }

  void SetInterpolator(InterpolatorType* ptr)
  {
    m_Interpolator = dynamic_cast<InterpolatorType*>(ptr);
    if(ptr != nullptr)
    {
      m_Interpolator->SetInputImage(this->GetInputImage());
    }
  }

  /** Evaluate the function at a ContinuousIndex position
   *
   * Returns the extrapolated image intensity at a
   * specified position.
   */
  OutputType EvaluateAtIndex(
    const IndexType & index) const override
  {
    IndexType nindex;

    for ( unsigned int j = 0; j < ImageDimension; j++ )
    {
      nindex[j] = index[j];

      typename IndexType::IndexValueType size = this->GetEndIndex()[j] - this->GetStartIndex()[j] + 1;

      while(nindex[j] > this->GetEndIndex()[j])
      {
        nindex[j] -= size;
      }
      while(nindex[j] < this->GetStartIndex()[j])
      {
        nindex[j] += size;
      }
    }
    return static_cast< OutputType >( this->GetInputImage()->GetPixel(nindex) );
  }

protected:
  WrapExtrapolateImageFunction()
  { m_Interpolator = dynamic_cast<InterpolatorType*>(LinearInterpolatorType::New().GetPointer()); }
  ~WrapExtrapolateImageFunction(){}
  void PrintSelf(std::ostream & os, Indent indent) const override
  {
    Superclass::PrintSelf(os, indent);
    os << indent << "Interpolator: " << this->m_Interpolator << std::endl;
  }

private:
  WrapExtrapolateImageFunction(const Self &) ITK_DELETE_FUNCTION;
  void operator=(const Self &) ITK_DELETE_FUNCTION;

  InterpolatorPointerType m_Interpolator;
};
} // end namespace itk

#endif
