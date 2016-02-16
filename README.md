PJE Sph
=======

I made this, with the help of Richad Meralli (not programmer) as a project
for *Arts et Métiers* engineer school.

PJE Sph is a axprimental SPH solver.
It is made to be hackable and at least reasonably performant.

Technologies used
------------------

 - c++14 with clang compiler
 - [Armadillo](http://arma.sourceforge.net/) (compiled with  [OpenBLAS](https://github.com/philsquared/Catch), not tested other backend)
 - VTK and HDF5 for storage
 - [Catch](https://github.com/philsquared/Catch) for UnitTest
 - [SdpLog](https://github.com/gabime/spdlog) for logging
 - [PyBind11](https://github.com/wjakob/pybind11) for python binary


License
--------

The whole code in `/src`, `/headers` and `/test` is given, under the MIT License.

For vendors, confere to original License.
