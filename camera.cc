#include "camera.h"
#include <cmath>

Camera::Camera(Point _p, Orient _o, double _width, double _height, double _dist): p{_p}, o{_o}, width{_width}, height{_height}, dist{_dist}
{
  // create 3 points on a plane perpendicular to the x axis
  Point cent = p + Point{dist,0,0};
  Point top = Point{0,1,0} + cent;
  Vec right = Point{0,0,1} + cent;

  // orient them
  cent = cent.orient(cent);
  top = cent.orient(top);
  right = cent.orient(right);

  // write into pl
  pl = points2plane(cent, top, right);
}

// Rectangle Camera::getRect()
// {
//   // create the rectangle's 3 corners with alt=0, azi=0, roll=0
//   Vec rec_cent = p + Point{1,0,0} * dist;
//   Vec bl = rec_cent + Point{0, -height/2, -width/2};
//   Vec br = rec_cent + Point{0, -height/2, width/2};
//   Vec tl = rec_cent + Point{0, height/2, -width/2};

//   // rotate according to roll
//   bl = bl.rotateX(roll);
//   br = br.rotateX(roll);
//   tl = tl.rotateX(roll);
  
//   // rotate according to altitude
//   bl = bl.rotateZ(alt);
//   br = br.rotateZ(alt);
//   tl = tl.rotateZ(alt);

//   // rotate according to azimuth
//   bl = bl.rotateY(azi);
//   br = br.rotateY(azi);
//   tl = tl.rotateY(azi);

//   // form the rectangle
//   Rectangle rect {bl, br, tl, br+(tl-bl)};
//   return rect;
  
//   // // use alt and azi to calculate unit direction vector that camera is facing in
//   // Vec unit;
//   // unit.y = sin(alt);
//   // double hori = cos(alt);
//   // unit.x = hori*cos(azi);
//   // unit.z = hori*sin(azi);

//   // // get center of rectangle using unit and dist
//   // Vec rec_cent = cent + unit * dist;
  
// }
