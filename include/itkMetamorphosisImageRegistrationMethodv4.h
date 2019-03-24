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
#ifndef itkMetamorphosisImageRegistrationMethodv4_h
#define itkMetamorphosisImageRegistrationMethodv4_h

#include "itkTimeVaryingVelocityFieldImageRegistrationMethodv4.h"
#include "itkTimeVaryingVelocityFieldSemiLagrangianTransform.h"
#include "itkForwardFFTImageFilter.h"
#include "itkInverseFFTImageFilter.h"
#include "itkFFTPadImageFilter.h"
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkImportImageFilter.h"
#include "itkComposeImageFilter.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkVectorMagnitudeImageFilter.h"
#include "itkGradientImageFilter.h"
#include "itkDisplacementFieldJacobianDeterminantFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkAddImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkJoinSeriesImageFilter.h"
#include "itkExtractImageFilter.h"
#include "itkWrapExtrapolateImageFunction.h"
#include "itkNearestNeighborInterpolateImageFunction.h"
#include "itkImageMaskSpatialObject.h"
#include "itkSpatialObjectToImageFilter.h"

namespace itk
{
template<class TInputImage, class TOutputImage>
class ConstantImageFilter:
public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(ConstantImageFilter);

  /** Standard class type alias. */
  using Self = ConstantImageFilter;
  using Superclass = ImageToImageFilter< TInputImage, TOutputImage >;
  using Pointer = SmartPointer< Self >;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConstantImageFilter, ImageToImageFilter);

  using OutputImageType = TOutputImage;
  using OutputPixelType = typename OutputImageType::PixelType;
  using OutputImageIteratorType = ImageRegionIterator<OutputImageType>;

  itkSetMacro(Constant, OutputPixelType);
  itkGetConstMacro(Constant, OutputPixelType);


protected:
  ConstantImageFilter() = default;
  ~ConstantImageFilter() override = default;

  /** Does the real work. */
  void DynamicThreadedGenerateData(const typename OutputImageType::RegionType& outputRegionForThread) override
  {
    OutputPixelType constant = this->GetConstant();
    OutputImageIteratorType  it(this->GetOutput(),outputRegionForThread);

    while(!it.IsAtEnd())
    {
      it.Set(constant);
      ++it;
    }
  }

private:

  OutputPixelType m_Constant;
};

/** \class MetamorphosisImageRegistrationMethodv4
* \breif Perfoms metamorphosis registration between images
*
* \author Kwane Kutten
*
* \ingroup NDReg
*/

template<  typename TFixedImage,
           typename TMovingImage = TFixedImage >
class MetamorphosisImageRegistrationMethodv4:
public TimeVaryingVelocityFieldImageRegistrationMethodv4<TFixedImage, TMovingImage, TimeVaryingVelocityFieldSemiLagrangianTransform<double, TFixedImage::ImageDimension> >
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(MetamorphosisImageRegistrationMethodv4);

  /** Standard class type alias. */
  using Self = MetamorphosisImageRegistrationMethodv4;
  using Superclass = TimeVaryingVelocityFieldImageRegistrationMethodv4<TFixedImage, TMovingImage, TimeVaryingVelocityFieldSemiLagrangianTransform<double, TFixedImage::ImageDimension> >;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information */
  itkTypeMacro(MetamorphosisImageRegistrationMethodv4, TimeVaryingVelocityFieldImageRegistrationMethodv4);

  /** Concept checking */
#ifdef ITK_USE_CONCEPT_CHECKING
  itkConceptMacro(MovingSameDimensionCheck, (Concept::SameDimension<TFixedImage::ImageDimension,TMovingImage::ImageDimension>));
#endif

  /** Image type alias */
  itkStaticConstMacro(ImageDimension, unsigned int, TFixedImage::ImageDimension);

  using FixedImageType = TFixedImage;
  using FixedImagePointer = typename FixedImageType::Pointer;

  using MovingImageType = TMovingImage;
  using MovingImagePointer = typename MovingImageType::Pointer;

  using VirtualImageType = typename Superclass::VirtualImageType;
  using VirtualImagePointer = typename VirtualImageType::Pointer;
  using VirtualPixelType = typename VirtualImageType::PixelType;

  using MaskImageType = Image<unsigned char, ImageDimension>;
  using MaskImagePointer = typename MaskImageType::Pointer;
  using MaskType = ImageMaskSpatialObject<ImageDimension>;
  using MaskPointer = typename MaskType::Pointer;
  using MaskConstPointer = typename MaskType::ConstPointer;

  using BiasImageType = VirtualImageType;
  using BiasImagePointer = typename BiasImageType::Pointer;

  using OutputTransformType = typename Superclass::OutputTransformType;
  using RealType = typename OutputTransformType::ScalarType;

  using FieldType = typename OutputTransformType::DisplacementFieldType;
  using FieldPointer = typename FieldType::Pointer;
  using VectorType = typename FieldType::PixelType;

  using TimeVaryingImageType = Image<typename VirtualImageType::PixelType,ImageDimension+1>;
  using TimeVaryingImagePointer = typename TimeVaryingImageType::Pointer;

  using TimeVaryingFieldType = typename OutputTransformType::TimeVaryingVelocityFieldType;
  using TimeVaryingFieldPointer = typename TimeVaryingFieldType::Pointer;

  // Metric type alias
  using ImageMetricType = typename Superclass::ImageMetricType;
  using ImageMetricPointer = typename ImageMetricType::Pointer;
  using MetricValueType = typename ImageMetricType::MeasureType;
  using MetricDerivativeType = typename ImageMetricType::DerivativeType;
  using MetricTraits = typename ImageMetricType::MetricTraits;

  // Filter type alias
  using FixedImageGradientFilterType = typename MetricTraits::FixedImageGradientFilterType;
  using FixedImageGradientFilterPointer = typename FixedImageGradientFilterType::Pointer;
  using DefaultFixedImageGradientFilterType = GradientImageFilter<FixedImageType, double, double>;
  using FixedImageConstantGradientFilterType = ConstantImageFilter<VirtualImageType, typename ImageMetricType::FixedImageGradientImageType>;

  using MovingImageGradientFilterType = typename MetricTraits::MovingImageGradientFilterType;
  using MovingImageGradientFilterPointer = typename MovingImageGradientFilterType::Pointer;
  using DefaultMovingImageGradientFilterType = GradientImageFilter<MovingImageType, double, double>;
  using MovingImageConstantGradientFilterType = ConstantImageFilter<VirtualImageType, typename ImageMetricType::MovingImageGradientImageType>;

  /** Public member functions */
  itkSetMacro(Scale, double);
  itkGetConstMacro(Scale, double);
  itkSetMacro(RegistrationSmoothness, double);
  itkGetConstMacro(RegistrationSmoothness,double);
  itkSetMacro(BiasSmoothness, double);
  itkGetConstMacro(BiasSmoothness,double);
  itkSetMacro(Sigma, double);
  itkGetConstMacro(Sigma, double);
  itkSetMacro(Mu, double);
  itkGetConstMacro(Mu, double);
  itkSetMacro(Gamma, double);
  itkGetConstMacro(Gamma, double);
  itkSetMacro(MinLearningRate, double)
  itkGetConstMacro(MinLearningRate, double);
  itkSetMacro(MinImageEnergyFraction, double);
  itkGetConstMacro(MinImageEnergyFraction, double);
  itkSetMacro(NumberOfTimeSteps, unsigned int);
  itkGetConstMacro(NumberOfTimeSteps, unsigned int);
  itkSetMacro(NumberOfIterations, unsigned int);
  itkGetConstMacro(NumberOfIterations, unsigned int);
  itkBooleanMacro(UseJacobian);
  itkSetMacro(UseJacobian, bool);
  itkGetConstMacro(UseJacobian, bool);
  itkBooleanMacro(UseBias);
  itkSetMacro(UseBias, bool);
  itkGetConstMacro(UseBias, bool);

  double GetVelocityEnergy();
  double GetRateEnergy();
  double GetImageEnergy(VirtualImagePointer movingImage, MaskPointer movingMask=nullptr);
  double GetImageEnergy();
  double GetImageEnergyFraction();
  double GetEnergy();
  double GetLength();
  BiasImagePointer GetBias();

protected:
  MetamorphosisImageRegistrationMethodv4();
  ~MetamorphosisImageRegistrationMethodv4() override = default;
  TimeVaryingImagePointer ApplyKernel(TimeVaryingImagePointer kernel, TimeVaryingImagePointer image);
  TimeVaryingFieldPointer ApplyKernel(TimeVaryingImagePointer kernel, TimeVaryingFieldPointer image);
  double CalculateNorm(TimeVaryingImagePointer image);
  double CalculateNorm(TimeVaryingFieldPointer field);
  void InitializeKernels(TimeVaryingImagePointer kernel, TimeVaryingImagePointer inverseKernel, double alpha, double gamma);
  void Initialize();
  void IntegrateRate();
  FieldPointer GetMetricDerivative(FieldPointer field, bool useImageGradients);
  void UpdateControls();
  void StartOptimization() override;
  void GenerateData() override;
  void PrintSelf(std::ostream& os, Indent indent) const override;

private:

  double m_Scale;
  double m_RegistrationSmoothness;
  double m_BiasSmoothness;
  double m_Sigma;
  double m_Mu;
  double m_Gamma;
  double m_MinLearningRate;
  double m_MinImageEnergyFraction;
  double m_MaxImageEnergy;
  double m_MinImageEnergy;
  unsigned int m_NumberOfTimeSteps;
  unsigned int m_NumberOfIterations;
  bool m_UseJacobian;
  bool m_UseBias;
  double m_TimeStep;
  double m_VoxelVolume;
  double m_Energy;
  bool m_RecalculateEnergy;
  bool m_IsConverged;
  VirtualImagePointer m_VirtualImage;
  VirtualImagePointer m_ForwardImage;
  MaskImagePointer    m_MovingMaskImage;
  MaskImagePointer    m_ForwardMaskImage;
  typename VirtualImageType::PointType m_CenterPoint;
  TimeVaryingImagePointer m_VelocityKernel;
  TimeVaryingImagePointer m_InverseVelocityKernel;
  TimeVaryingImagePointer m_RateKernel;
  TimeVaryingImagePointer m_InverseRateKernel;
  TimeVaryingImagePointer m_Rate;
  VirtualImagePointer m_Bias;

  typename MovingImageConstantGradientFilterType::Pointer m_MovingImageConstantGradientFilter;
  typename FixedImageConstantGradientFilterType::Pointer  m_FixedImageConstantGradientFilter;

}; // End class MetamorphosisImageRegistrationMethodv4


} // End namespace itk
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMetamorphosisImageRegistrationMethodv4.hxx"
#endif

#endif
