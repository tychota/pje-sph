#include "solid/Box.hpp"


Box::Box(double cr_co,
         Type type,
         vec3 center,
         vec3 rotation,
         vec3 extendAxis) : Solid(cr_co, type),
        cr_co(cr_co),
        type(type),
        center(center),
        rotation(rotation),
        extendAxis(extendAxis)
{ }
