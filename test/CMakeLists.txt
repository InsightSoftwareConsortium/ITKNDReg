itk_module_test()

set(NDRegTests
  itkMetamorphosisImageRegistrationMethodv4Test.cxx
  itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest.cxx
  itkTimeVaryingVelocityFieldSemiLagrangianTransformTest.cxx
  itkWrapExtrapolateImageFunctionTest.cxx
  )

CreateTestDriver(NDReg "${NDReg-Test_LIBRARIES}" "${NDRegTests}")

itk_add_test(NAME itkMetamorphosisImageRegistrationMethodv4Test
      COMMAND NDRegTestDriver
    --compare ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
    DATA{Baseline/itkMyFilterTestOutput.mha}
    itkMetamorphosisImageRegistrationMethodv4Test ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )

itk_add_test(NAME itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest
      COMMAND NDRegTestDriver
    --compare ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
              DATA{Baseline/itkMyFilterTestOutput.mha}
    itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilterTest ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )

itk_add_test(NAME itkTimeVaryingVelocityFieldSemiLagrangianTransformTest
      COMMAND NDRegTestDriver --without-threads
    --compare ${ITK_TEST_OUTPUT_DIR}/itkNormalDistributionImageSourceTestOutput.mha
              DATA{Baseline/itkNormalDistributionImageSourceTestOutput.mha}
    itkTimeVaryingVelocityFieldSemiLagrangianTransformTest ${ITK_TEST_OUTPUT_DIR}/itkNormalDistributionImageSourceTestOutput.mha
  )

itk_add_test(NAME itkWrapExtrapolateImageFunctionTest
      COMMAND NDRegTestDriver
    --compare ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
              DATA{Baseline/itkMyFilterTestOutput.mha}
    itkWrapExtrapolateImageFunctionTest ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )
