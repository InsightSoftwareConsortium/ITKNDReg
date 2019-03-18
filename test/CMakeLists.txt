itk_module_test()

set(NDRegTests
  itkMetamorphosisImageRegistrationMethodv4Test.cxx
  #itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest.cxx
  itkTimeVaryingVelocityFieldSemiLagrangianTransformTest.cxx
  itkWrapExtrapolateImageFunctionTest.cxx
  )

CreateTestDriver(NDReg "${NDReg-Test_LIBRARIES}" "${NDRegTests}")

itk_add_test(NAME itkMetamorphosisImageRegistrationMethodv4Test
      COMMAND NDRegTestDriver
    itkMetamorphosisImageRegistrationMethodv4Test ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )

# Todo: Fix and re-enable
#itk_add_test(NAME itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest
      #COMMAND NDRegTestDriver
    #itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  #)

itk_add_test(NAME itkTimeVaryingVelocityFieldSemiLagrangianTransformTest
      COMMAND NDRegTestDriver --without-threads
    itkTimeVaryingVelocityFieldSemiLagrangianTransformTest ${ITK_TEST_OUTPUT_DIR}/itkNormalDistributionImageSourceTestOutput.mha
  )

itk_add_test(NAME itkWrapExtrapolateImageFunctionTest
      COMMAND NDRegTestDriver
    itkWrapExtrapolateImageFunctionTest ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )
