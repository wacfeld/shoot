#include "camera.h"
#include <cmath>

Camera::Camera(Point _p, Orient _o, double _width, double _height, double _dist): p{_p}, o{_o}, width{_width}, height{_height}, dist{_dist}
{
  // create 3 points on a plane perpendicular to the x axis
  Point cent = p + Point{dist,0,0};
  Point top = Point{0,1,0} + cent;
  Vec right = Point{0,0,1} + cent;

  // orient them
  cent = cent.orient(o);
  top = top.orient(o);
  right = right.orient(o);

  // write into pl
  plane = points2plane(cent, top, right);
}

Point2D Camera::cent2tl(Point2D P)
{
  Point2D tl {-width/2, -height/2};
  return P - tl;
}

Point2D Camera::scale(Point2D P)
{
  P.x = SCREEN_WIDTH * P.x / width;
  P.y = SCREEN_HEIGHT * P.y / height;
  return P;
}

void Camera::screenQuad(Rectangle proj)
{
  // unorient proj so it's parallel to the YZ plane
  Rectangle rect = proj.unorient(o);

  // calculate relation to screen
  Point2D tl = rect.tl();
  Point2D bl = rect.bl();
  Point2D tr = rect.tr();
  Point2D br = rect.br();

  tl.x = tl.z;
  tr.x = tr.z;
  bl.x = bl.z;
  br.x = br.z;
  
  std::cout << bl << " " << br << " " << tl << " " << tr << std::endl;
  tl = scale(cent2tl(tl));
  bl = scale(cent2tl(bl));
  br = scale(cent2tl(br));
  tr = scale(cent2tl(tr));

  std::cout << bl << " " << br << " " << tl << " " << tr << std::endl;
  
  SDL_SetRenderDrawColor(grend, 0x33, 0xCC, 0xFF, 0xFF);
  SDL_RenderDrawPoint(grend, (int)tl.x, (int)tl.y);
  SDL_RenderDrawPoint(grend, (int)tr.x, (int)tr.y);
  SDL_RenderDrawPoint(grend, (int)br.x, (int)br.y);
  SDL_RenderDrawPoint(grend, (int)bl.x, (int)bl.y);
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
