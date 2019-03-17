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
#ifndef itkNormalDistributionImageSource_h
#define itkNormalDistributionImageSource_h

#include "itkGenerateImageSource.h"

namespace itk
{

/** \class NormalDistributionImageSource
 *
 * \brief Generate a image of pixels sampled from a normal distribution.
 *
 * Real-valued pixels are sampled from a normal distribution.
 *
 * The pixels, \f$x > 0\f$ follow
 *
 * \f[
 *   f(x) = \frac{1}{sx\sqrt{2 \pi}} e^{\left( \frac{-(ln x - m)^2}{2s^2} \right)}
 * \f]
 *
 * where \f$s\f$ is the StandardDeviation and \f$m\f$ is the Mean of the
 * underlying normal distribution.
 *
 * \ingroup NDReg
 *
 */
template< typename TImage >
class NormalDistributionImageSource: public GenerateImageSource< TImage >
{
public:
  using ImageType = TImage;
  using PixelType = typename ImageType::PixelType;

  /** Standard class type alias. */
  using Self = NormalDistributionImageSource;
  using Superclass = GenerateImageSource< ImageType >;
  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;

  itkStaticConstMacro( ImageDimension, unsigned int, ImageType::ImageDimension );

  /** Run-time type information. */
  itkTypeMacro( NormalDistributionImageSource, GenerateImageSource );

  /** Standard New macro. */
  itkNewMacro( Self );

protected:
  NormalDistributionImageSource();
  virtual ~NormalDistributionImageSource() {}

  void PrintSelf( std::ostream& os, Indent indent ) const ITK_OVERRIDE;

  using OutputRegionType = typename ImageType::RegionType;

  virtual void GenerateData() ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(NormalDistributionImageSource);

#ifdef ITK_USE_CONCEPT_CHECKING
  itkConceptMacro( FloatingPointPixel, ( itk::Concept::IsFloatingPoint< typename ImageType::PixelType > ) );
#endif
};
}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkNormalDistributionImageSource.hxx"
#endif

#endif // itkNormalDistributionImageSource_h
