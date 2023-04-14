#include "camera.h"
#include <cmath>

Camera::getRect()
{
  // use alt and azi to calculate unit direction vector that camera is facing in
  Vec unit;
  unit.y = sin(alt);
  double hori = cos(alt);
  unit.x = hori*cos(azi);
  unit.z = hori*sin(azi);

  // get center of rectangle using unit and dist
  Vec rec_cent = cent + unit * dist;
  
}
