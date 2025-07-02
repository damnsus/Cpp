#include "cpp-23-24-geometry.hpp"

#include <cmath>

Vector PointToVector(const Point& k_point) {
  Vector temp(k_point.GetX(), k_point.GetY());
  return temp;
}

int64_t MaxX(const Segment& k_segm) {
  if (k_segm.GetA().GetX() > k_segm.GetB().GetX()) {
    return k_segm.GetA().GetX();
  }
  return k_segm.GetB().GetX();
}

int64_t MinX(const Segment& k_segm) {
  if (k_segm.GetA().GetX() > k_segm.GetB().GetX()) {
    return k_segm.GetB().GetX();
  }
  return k_segm.GetA().GetX();
}

int64_t MaxY(const Segment& k_segm) {
  if (k_segm.GetA().GetY() > k_segm.GetB().GetY()) {
    return k_segm.GetA().GetY();
  }
  return k_segm.GetB().GetY();
}

int64_t MinY(const Segment& k_segm) {
  if (k_segm.GetA().GetY() > k_segm.GetB().GetY()) {
    return k_segm.GetB().GetY();
  }
  return k_segm.GetA().GetY();
}

int64_t Square(int64_t num) { return num * num; }

//////////////////////////////////////////////////////////

Vector::Vector(const int64_t& k_vec_x, const int64_t& k_vec_y)
    : vx_(k_vec_x), vy_(k_vec_y){};

Vector::Vector(const Point& k_point)
    : vx_(k_point.GetX()), vy_(k_point.GetY()) {}

Vector::Vector(const Vector& k_vec) : vx_(k_vec.vx_), vy_(k_vec.vy_) {}

Vector Vector::operator+=(const Vector& k_vec) {
  vx_ += k_vec.vx_;
  vy_ += k_vec.vy_;
  return *this;
}

Vector Vector::operator-=(const Vector& k_vec) {
  vx_ -= k_vec.vx_;
  vy_ -= k_vec.vy_;
  return *this;
}

Vector Vector::operator*=(const int64_t& k_num) {
  vx_ *= k_num;
  vy_ *= k_num;
  return *this;
}

Vector Vector::operator*(const int64_t& k_num) { return *this *= k_num; }

Vector Vector::operator-() const {
  Vector temp(vx_, vy_);
  temp *= -1;
  return temp;
}

int64_t Vector::GetX() const { return vx_; }

int64_t Vector::GetY() const { return vy_; }

int64_t Vector::Module() const { return vx_ * vx_ + vy_ * vy_; }

Vector Ort(const Vector& k_vec) {
  Vector temp(-k_vec.GetY(), k_vec.GetX());
  return temp;
}

Vector operator*(int64_t num, const Vector& k_vec) {
  Vector temp(k_vec.GetX() * num, k_vec.GetY() * num);
  return temp;
}

int64_t operator*(const Vector& k_vec1, const Vector& k_vec2) {
  return k_vec1.GetX() * k_vec2.GetX() + k_vec1.GetY() * k_vec2.GetY();
}

int64_t operator^(const Vector& k_vec1, const Vector& k_vec2) {
  return (k_vec1.GetX() * k_vec2.GetY() - k_vec1.GetY() * k_vec2.GetX());
}

Vector operator+(const Vector& k_vec1, const Vector& k_vec2) {
  Vector temp(k_vec1);
  temp += k_vec2;
  return temp;
}

Vector operator-(const Vector& k_vec1, const Vector& k_vec2) {
  Vector temp(k_vec1);
  temp -= k_vec2;
  return temp;
}

//////////////////////////////////////////////////////////

Point::Point(const int64_t& k_x, const int64_t& k_y) : px_(k_x), py_(k_y) {}

Point::Point(const Point& k_point) : px_(k_point.px_), py_(k_point.py_) {}

Point& Point::operator=(const Point& k_point) {
  px_ = k_point.px_;
  py_ = k_point.py_;
  return *this;
}

int64_t Point::GetX() const { return px_; }

int64_t Point::GetY() const { return py_; }

void Point::Move(const Vector& k_vec) {
  px_ += k_vec.GetX();
  py_ += k_vec.GetY();
}

bool Point::ContainsPoint(const Point& k_point) const {
  return px_ == k_point.px_ && py_ == k_point.py_;
}

bool Point::CrossSegment(const Segment& k_seg) const {
  return k_seg.ContainsPoint(*this);
}

IShape* Point::Clone() const { return new Point(px_, py_); }

//////////////////////////////////////////////////////////

Segment::Segment(const Point& k_a, const Point& k_b) : sa_(k_a), sb_(k_b) {}

Segment& Segment::operator=(const Segment& k_segm) {
  sa_ = k_segm.sa_;
  sb_ = k_segm.sb_;
  return *this;
}

Point Segment::GetA() const { return sa_; }

Point Segment::GetB() const { return sb_; }

void Segment::Move(const Vector& k_vec) {
  sa_.Move(k_vec);
  sb_.Move(k_vec);
}

bool Segment::ContainsPoint(const Point& k_point) const {
  Vector vec_oa = PointToVector(sa_);
  Vector vec_ob = PointToVector(sb_);
  Vector vec_ab = vec_ob - vec_oa;
  Vector vec_oc = PointToVector(k_point);
  Vector vec_ac = vec_oc - vec_oa;
  return (vec_ab ^ vec_ac) == 0 && (vec_ab * vec_ac) >= 0 &&
         vec_ab.Module() >= vec_ac.Module();
}

bool Segment::CrossSegment(const Segment& k_seg) const {
  Vector vec_oa1 = PointToVector(sa_);
  Vector vec_ob1 = PointToVector(sb_);
  Vector vec_oa2 = PointToVector(k_seg.GetA());
  Vector vec_ob2 = PointToVector(k_seg.GetB());
  Vector vec_ab1 = vec_ob1 - vec_oa1;
  Vector vec_ab2 = vec_ob2 - vec_oa2;
  Vector vec_a1a2 = vec_oa2 - vec_oa1;
  Vector vec_a1b2 = vec_ob2 - vec_oa1;
  Vector vec_a2a1 = -vec_a1a2;
  Vector vec_a2b1 = vec_ob1 - vec_oa2;
  bool cond1 = (vec_ab1 ^ vec_a1a2) * (vec_ab1 ^ vec_a1b2) <= 0;
  bool cond2 = (vec_ab2 ^ vec_a2a1) * (vec_ab2 ^ vec_a2b1) <= 0;
  bool cond3 = true;
  if ((vec_ab1 ^ vec_ab2) == 0) {
    bool subcond1 = (MaxX(*this) < MinX(k_seg)) || (MinX(*this) > MaxX(k_seg));
    bool subcond2 = (MaxY(*this) < MinY(k_seg)) || (MinY(*this) > MaxY(k_seg));
    cond3 = !(subcond1 || subcond2);
  }
  return cond1 && cond2 && cond3;
}

IShape* Segment::Clone() const { return new Segment(sa_, sb_); }

//////////////////////////////////////////////////////////

Line::Line(const Point& k_a, const Point& k_b) : la_(k_a), lb_(k_b) {}

Line& Line::operator=(const Line& k_line) {
  la_ = k_line.la_;
  lb_ = k_line.lb_;
  return *this;
}

int64_t Line::GetA() const { return lb_.GetY() - la_.GetY(); }

int64_t Line::GetB() const { return la_.GetX() - lb_.GetX(); }

int64_t Line::GetC() const {
  return (lb_.GetX() - la_.GetX()) * la_.GetY() -
         (lb_.GetY() - la_.GetY()) * la_.GetX();
}

void Line::Move(const Vector& k_vec) {
  Point point1(la_.GetX() + k_vec.GetX(), la_.GetY() + k_vec.GetY());
  Point point2(lb_.GetX() + k_vec.GetX(), lb_.GetY() + k_vec.GetY());
  Line temp(point1, point2);
  *this = temp;
}

bool Line::ContainsPoint(const Point& k_point) const {
  Vector vec_oa = PointToVector(la_);
  Vector vec_ob = PointToVector(lb_);
  Vector vec_oc = PointToVector(k_point);
  Vector vec_ab = vec_ob - vec_oa;
  Vector vec_ac = vec_oc - vec_oa;
  return (vec_ab ^ vec_ac) == 0;
}

bool Line::CrossSegment(const Segment& k_seg) const {
  Vector vec_oa1 = PointToVector(la_);
  Vector vec_ob1 = PointToVector(lb_);
  Vector vec_oa2 = PointToVector(k_seg.GetA());
  Vector vec_ob2 = PointToVector(k_seg.GetB());
  Vector vec_ab1 = vec_ob1 - vec_oa1;
  Vector vec_a1a2 = vec_oa2 - vec_oa1;
  Vector vec_a1b2 = vec_ob2 - vec_oa1;
  return (vec_ab1 ^ vec_a1a2) * (vec_ab1 ^ vec_a1b2) <= 0;
}

IShape* Line::Clone() const { return new Line(la_, lb_); }

//////////////////////////////////////////////////////////

Ray::Ray(const Point& k_a, const Point& k_b) : ra_(k_a), rb_(k_b) {}

Ray& Ray::operator=(const Ray& k_ray) {
  ra_ = k_ray.ra_;
  rb_ = k_ray.rb_;
  return *this;
}

Point Ray::GetA() const { return ra_; }

Vector Ray::GetVector() const {
  Vector vec1(ra_.GetX(), ra_.GetY());
  Vector vec2(rb_.GetX(), rb_.GetY());
  Vector temp = vec2 - vec1;
  return temp;
}

void Ray::Move(const Vector& k_vec) {
  ra_.Move(k_vec);
  rb_.Move(k_vec);
}

bool Ray::ContainsPoint(const Point& k_point) const {
  Line line(ra_, rb_);
  Vector vec_oa(ra_);
  Vector vec_oc(k_point);
  Vector vec_ac = vec_oc - vec_oa;
  if ((GetVector() * vec_ac) >= 0) {
    return line.ContainsPoint(k_point);
  }
  return false;
}

bool Ray::CrossSegment(const Segment& k_seg) const {
  Segment segm(ra_, rb_);
  Line line(ra_, rb_);
  bool cond1 = segm.CrossSegment(k_seg);
  bool cond2 = false;
  Vector vec(1, 0);
  if ((vec * GetVector()) >= 0) {
    return segm.CrossSegment(k_seg) ||
           ((MinX(k_seg) >= ra_.GetX()) && line.CrossSegment(k_seg));
  }
  if ((vec * GetVector()) <= 0) {
    if (MaxX(k_seg) <= ra_.GetX()) {
      cond2 = line.CrossSegment(k_seg);
    }
  }
  return segm.CrossSegment(k_seg) ||
         ((MaxX(k_seg) <= ra_.GetX()) && line.CrossSegment(k_seg));
}

IShape* Ray::Clone() const { return new Ray(ra_, rb_); }

//////////////////////////////////////////////////////////

Circle::Circle(const Point& centre, unsigned radius)
    : centre_(centre), radius_(radius) {}

Point Circle::GetCentre() const { return centre_; }

unsigned Circle::GetRadius() const { return radius_; }

void Circle::Move(const Vector& k_vec) {
  Point centre(centre_.GetX() + k_vec.GetX(), centre_.GetY() + k_vec.GetY());
  centre_ = centre;
}

bool Circle::ContainsPoint(const Point& k_point) const {
  int64_t value = Square(radius_);
  int64_t first = Square(k_point.GetX() - centre_.GetX());
  int64_t second = Square(k_point.GetY() - centre_.GetY());
  return first + second <= value;
}

bool Circle::Check(const Segment& k_seg) const {
  Vector vec_oa(k_seg.GetA());
  Vector vec_ob(k_seg.GetB());
  Vector vec_oc(centre_);
  Vector vec_ca = vec_oa - vec_oc;
  Vector vec_cb = vec_ob - vec_oc;
  bool cond1 = vec_ca.Module() == Square(radius_);
  bool cond2 = vec_cb.Module() == Square(radius_);
  bool cond3 = vec_ca.Module() > Square(radius_);
  bool cond4 = vec_cb.Module() < Square(radius_);
  bool cond5 = vec_ca.Module() < Square(radius_);
  bool cond6 = vec_cb.Module() > Square(radius_);

  return cond1 || cond2 || (cond3 && cond4) || (cond5 && cond6);
}

bool Circle::CrossSegment(const Segment& k_seg) const {
  Vector vec_oa(k_seg.GetA());
  Vector vec_ob(k_seg.GetB());
  Vector vec_oc(centre_);
  Vector vec_ca = vec_oa - vec_oc;
  Vector vec_cb = vec_ob - vec_oc;
  Vector vec_ab = vec_ob - vec_oa;
  Vector vec_ort = Ort(vec_ab);
  bool cond1 = k_seg.GetA().GetX() >= centre_.GetX() - radius_;
  bool cond2 = k_seg.GetA().GetX() <= centre_.GetX() + radius_;
  bool cond3 = k_seg.GetA().GetY() >= centre_.GetY() - radius_;
  bool cond4 = k_seg.GetA().GetY() <= centre_.GetY() + radius_;
  if (vec_ab.GetX() == 0) {
    return Check(k_seg) || (cond1 && cond2);
  }
  if (vec_ab.GetY() == 0) {
    return Check(k_seg) || (cond3 && cond4);
  }
  double dist = Square(vec_ab ^ (-vec_ca)) / vec_ab.Module();
  if (dist > Square(radius_)) {
    return false;
  }
  if (dist < Square(radius_)) {
    bool temp_cond1 = Check(k_seg);
    bool temp_cond2 = ((vec_ca * vec_cb) < 0);
    bool temp_cond3 = ContainsPoint(k_seg.GetA());
    bool temp_cond4 = ContainsPoint(k_seg.GetB());
    return temp_cond1 || temp_cond2 || !(temp_cond3 || temp_cond4);
  }
  return ((vec_ort ^ vec_ca) * (vec_ort ^ vec_cb) <= 0);
}

IShape* Circle::Clone() const { return new Circle(centre_, radius_); }
