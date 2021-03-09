ITKNDReg
========

.. image:: https://github.com/InsightSoftwareConsortium/ITKNDReg/actions/workflows/build-test-package.yml/badge.svg
    :target: https://github.com/InsightSoftwareConsortium/ITKNDReg/actions/workflows/build-test-package.yml
    :alt: Build, test, package

.. image:: https://img.shields.io/pypi/v/itk-ndreg.svg
    :target: https://pypi.python.org/pypi/itk-ndreg
    :alt: PyPI

.. image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg
    :target: https://github.com/InsightSoftwareConsortium/ITKNDReg/blob/master/LICENSE)
    :alt: License

Overview
--------

This is Neurodata's open-source Python package that performs affine and
deformable (LDDMM) image registration.

Installation
------------

To install the Python package::

  python -m pip install itk-ndreg

Or, build the module as a separate project against an ITK build tree::

  git clone https://github.com/InsightSoftwareConsortium/ITKNDReg
  mkdir ITKNDReg-bulid
  cd ITKNDReg-build
  cmake -DITK_DIR=/path/to/ITK-build ../ITKNDReg
  cmake --build .

License
-------

This software is distributed under the Apache 2.0 license. Please see the
*LICENSE* file for details.
