itk_module_test()

set(NDRegTests
  itkMinimalStandardRandomVariateGeneratorTest.cxx
  itkNormalDistributionImageSourceTest.cxx
  itkMyFilterTest.cxx
  )

CreateTestDriver(NDReg "${NDReg-Test_LIBRARIES}" "${NDRegTests}")

itk_add_test(NAME itkMinimalStandardRandomVariateGeneratorTest
  COMMAND NDRegTestDriver itkMinimalStandardRandomVariateGeneratorTest
  )

itk_add_test(NAME itkMyFilterTest
  COMMAND NDRegTestDriver
    --compare
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
    DATA{Baseline/itkMyFilterTestOutput.mha}
  itkMyFilterTest
    ${ITK_TEST_OUTPUT_DIR}/itkMyFilterTestOutput.mha
  )

itk_add_test(NAME itkNormalDistributionImageSourceTest
  COMMAND NDRegTestDriver --without-threads
  --compare
    ${ITK_TEST_OUTPUT_DIR}/itkNormalDistributionImageSourceTestOutput.mha
    DATA{Baseline/itkNormalDistributionImageSourceTestOutput.mha}
  itkNormalDistributionImageSourceTest
    ${ITK_TEST_OUTPUT_DIR}/itkNormalDistributionImageSourceTestOutput.mha
  )
