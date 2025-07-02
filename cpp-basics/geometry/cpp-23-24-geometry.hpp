#include <stdint.h>

class Vector;
class IShape;
class Point;
class Segment;
class Ray;
class Circle;

Vector PointToVector(const Point& k_point);
int64_t MaxX(const Segment& k_segm);
int64_t MinX(const Segment& k_segm);
int64_t MaxY(const Segment& k_segm);
int64_t MinY(const Segment& k_segm);
int64_t Square(int64_t num);

class Vector {
 public:
  Vector() = default;
  Vector(const int64_t& k_vec_x, const int64_t& k_vec_y);
  Vector(const Point& k_point);
  Vector(const Vector& k_vec);
  Vector operator+=(const Vector& k_vec);
  Vector operator-=(const Vector& k_vec);
  Vector operator*=(const int64_t& k_num);
  Vector operator*(const int64_t& k_num);
  Vector operator-() const;
  int64_t GetX() const;
  int64_t GetY() const;
  int64_t Module() const;
  Vector Ort(const Vector& k_vec);

 private:
  int64_t vx_;
  int64_t vy_;
};

Vector operator*(int64_t num, const Vector& k_vec);
int64_t operator*(const Vector& k_vec1, const Vector& k_vec2);
int64_t operator^(const Vector& k_vec1, const Vector& k_vec2);
Vector operator+(const Vector& k_vec1, const Vector& k_vec2);
Vector operator-(const Vector& k_vec1, const Vector& k_vec2);

class IShape {
 public:
  virtual ~IShape() = default;
  virtual void Move(const Vector& k_vec) = 0;
  virtual bool ContainsPoint(const Point& k_point) const = 0;
  virtual bool CrossSegment(const Segment& k_seg) const = 0;
  virtual IShape* Clone() const = 0;
};

class Point : public IShape {
 public:
  Point() = default;
  Point(const int64_t& k_x, const int64_t& k_y);
  Point(const Point& k_point);
  Point& operator=(const Point& k_point);
  int64_t GetX() const;
  int64_t GetY() const;
  void Move(const Vector& k_vec) override;
  bool ContainsPoint(const Point& k_point) const override;
  bool CrossSegment(const Segment& k_seg) const override;
  IShape* Clone() const override;

 private:
  int64_t px_;
  int64_t py_;
};

class Segment : public IShape {
 public:
  Segment() = default;
  Segment(const Point& k_a, const Point& k_b);
  Segment& operator=(const Segment& k_segm);
  Point GetA() const;
  Point GetB() const;
  void Move(const Vector& k_vec) override;
  bool ContainsPoint(const Point& k_point) const override;
  bool CrossSegment(const Segment& k_seg) const override;
  IShape* Clone() const override;

 private:
  Point sa_;
  Point sb_;
};

class Line : public IShape {
 public:
  Line() = default;
  Line(const Point& k_a, const Point& k_b);
  Line& operator=(const Line& k_line);
  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;
  void Move(const Vector& k_vec) override;
  bool ContainsPoint(const Point& k_point) const override;
  bool CrossSegment(const Segment& k_seg) const override;
  IShape* Clone() const override;

 private:
  Point la_;
  Point lb_;
};

class Ray : public IShape {
 public:
  Ray() = default;
  Ray(const Point& k_a, const Point& k_b);
  Ray& operator=(const Ray& k_ray);
  Point GetA() const;
  Vector GetVector() const;
  void Move(const Vector& k_vec) override;
  bool ContainsPoint(const Point& k_point) const override;
  bool CrossSegment(const Segment& k_seg) const override;
  IShape* Clone() const override;

 private:
  Point ra_;
  Point rb_;
};

class Circle : public IShape {
 public:
  Circle() = default;
  Circle(const Point& centre, unsigned radius);
  Point GetCentre() const;
  unsigned GetRadius() const;
  void Move(const Vector& k_vec) override;
  bool ContainsPoint(const Point& k_point) const override;
  bool CrossSegment(const Segment& k_seg) const override;
  IShape* Clone() const override;
  bool Check(const Segment& k_seg) const;

 private:
  Point centre_;
  unsigned radius_;
};