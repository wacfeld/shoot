#include <cmath>

#include "linalg.h"

std::ostream &operator<<(std::ostream &out, Rectangle rect)
{
  out << rect.bl() << " " << rect.tl() << " " << rect.tr() << " " << rect.br();
  // out << rect.bl << std::endl << rect.tl() << std::endl << rect.tr() << std::endl << rect.br();
  return out;
}

std::ostream &operator<<(std::ostream &out, Point p)
{
  out << "(";
  out << p.x << "," << p.y << "," << p.z;
  out << ")";
  return out;
}

std::ostream &operator<<(std::ostream &out, Line l)
{
  out << l.p << " + t" << l.dir;
  return out;
}

std::ostream &operator<<(std::ostream &out, Plane pl)
{
  // not supported by all the compilers i could install
  // out << std::format("%fx + %fy + %fz = %f", pl.a, pl.b, pl.c, pl.d);
  out << pl.a << "x + " << pl.b << "y + " << pl.c << "z = " << pl.d << std::endl;
  return out;
}

Point cross(Point v1, Point v2)
{
  return {
    v1.y*v2.z - v1.z*v2.y,
    v1.z*v2.x - v1.x*v2.z,
    v1.x*v2.y - v1.y*v2.x
  };
}

double dot(Point v1, Point v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Point operator-(Point p1, Point p2)
{
  return {p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

Point operator+(Point v1, Point v2)
{
  return {v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}

Point operator*(double c, Point v)
{
  return {c*v.x, c*v.y, c*v.z};
}

Point operator*(Point v, double c)
{
  return c * v;
}

Line points2line(Point p1, Point p2)
{
  Line l;
  l.p = p1;
  l.dir = p2-p1;
  return l;
}

Line pdir2line(Point p, Point dir)
{
  Line l;
  l.p = p;
  l.dir = dir;
  return l;
}

Plane points2plane(Point p1, Point p2, Point p3)
{
  Point d1 = p2-p1;
  Point d2 = p3-p1;
  return pdir2plane(p1, d1, d2);
}

Plane pdir2plane(Point p, Point d1, Point d2)
{
  Point N = cross(d1, d2);
  double d = dot(p, N);
  return Plane(N.x, N.y, N.z, d);
}

Plane::Plane(double _a, double _b, double _c, double _d): a{_a}, b{_b}, c{_c}, d{_d} {}

Point Plane::normal()
{
  return {a, b, c};
}

// Rectangle::Rectangle(Point _bl, Point _w, Point _h): bl_dat{_bl}, w{_w}, h{_h} {}

// Rectangle::Rectangle(Point bl, Point br, Point tl, Point tr): bl_dat{bl}, w{br-bl}, h{tl-bl} {}

Rectangle::Rectangle(Point bl, Point br, Point tl, Point tr): _bl{bl}, _br{br}, _tl{tl} {}

// Point Rectangle::tr()
// {
//   Point p = tl+w;
//   return p;
// }

// Point Rectangle::bl()
// {
//   Point p = tl+h;
//   return p;
// }

// Point Rectangle::br()
// {
//   Point p = tl+h+w;
//   return p;
// }

Plane Rectangle::plane()
{
  return pdir2plane(bl(), w(), h());
}

Point intersect(Plane pl, Line l)
{
  double numer = pl.d - (pl.a*l.p.x + pl.b*l.p.y + pl.c*l.p.z);
  double denom = pl.a*l.dir.x + pl.b*l.dir.y + pl.c*l.dir.z;
  double t = numer/denom;
  
  Point p = l.p + t*l.dir;
  return p;
}

bool parallel(Plane pl, Line l)
{
  return dot(pl.normal(), l.dir) == 0;
}

bool zero(Point p)
{
  return p.x == 0 && p.y == 0 && p.z == 0;
}

Rectangle project(Rectangle src, Rectangle dest, Point p)
{
  return project(src, dest.plane(), p);
}

Rectangle project(Rectangle src, Plane dest, Point p)
{
  Line l = points2line(src.bl(), p);
  Point bl = intersect(dest, l);
  
  l = points2line(src.br(), p);
  Point br = intersect(dest, l);

  l = points2line(src.tl(), p);
  Point tl = intersect(dest, l);

  l = points2line(src.tr(), p);
  Point tr = intersect(dest, l);
  
  Rectangle res {bl, br, tl, tr};
  return res;
}

double deg2rad(double deg)
{
  return deg*M_PI/180;
}

Vec Point::rotateX(double th)
{
  Vec v;
  v.x = x;
  v.y = y*cos(th) - z*sin(th);
  v.z = y*sin(th) + z*cos(th);
  return v;
}

Vec Point::rotateY(double th)
{
  Vec v;
  v.x = x*cos(th) + z*sin(th);
  v.y = y;
  v.z = -x*sin(th) + z*cos(th);
  return v;
}

Vec Point::rotateZ(double th)
{
  Vec v;
  v.x = x*cos(th) - y*sin(th);
  v.y = x*sin(th) + y*cos(th);
  v.z = z;
  return v;
}

Point Point::orient(Orient o)
{
  Point p {x,y,z};
  p = p.rotateX(o.roll);
  p = p.rotateZ(o.alt);
  p = p.rotateY(o.azi);
  return p;
}

Point Point::unorient(Orient o)
{
  Point p {x,y,z};
  p = p.rotateY(-o.azi);
  p = p.rotateZ(-o.alt);
  p = p.rotateX(-o.roll);
  return p;
}

Rectangle Rectangle::orient(Orient o)
{
  Point new_bl = bl().orient(o);
  Point new_br = br().orient(o);
  Point new_tl = tl().orient(o);
  Point new_tr = tr().orient(o);

  return Rectangle{new_bl, new_br, new_tl, new_tr};
}

Rectangle Rectangle::unorient(Orient o)
{
  Point new_bl = bl().unorient(o);
  Point new_br = br().unorient(o);
  Point new_tl = tl().unorient(o);
  Point new_tr = tr().unorient(o);

  return Rectangle{new_bl, new_br, new_tl, new_tr};
}
