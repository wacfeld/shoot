#include "camera.h"
#include <cmath>

Rectangle Camera::getRect()
{
  // create the rectangle's 3 corners with alt=0, azi=0, roll=0
  Vec rec_cent = cent + Point{0,0,0} * dist;
  Vec bl = rec_cent + Point{0, -height/2, -width/2};
  Vec br = rec_cent + Point{0, -height/2, width/2};
  Vec tl = rec_cent + Point{0, height/2, -width/2};
  
  // rotate according to altitude
  bl = bl.rotateZ(alt);
  br = br.rotateZ(alt);
  tl = tl.rotateZ(alt);

  // rotate according to azimuth
  bl = bl.rotateY(azi);
  br = br.rotateY(azi);
  tl = tl.rotateY(azi);

  // form the rectangle
  Rectangle rect {bl, br-bl, tl-bl};
  return rect;
  
  // // use alt and azi to calculate unit direction vector that camera is facing in
  // Vec unit;
  // unit.y = sin(alt);
  // double hori = cos(alt);
  // unit.x = hori*cos(azi);
  // unit.z = hori*sin(azi);

  // // get center of rectangle using unit and dist
  // Vec rec_cent = cent + unit * dist;
  
}
