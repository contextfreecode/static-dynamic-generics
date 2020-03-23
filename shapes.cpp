#include <concepts>
#include <iostream>
#include <numbers>
#include <vector>

// Shape

template<typename ShapeImpl>
concept Shape =
  requires(const ShapeImpl shape) {
    { shape.area() } -> std::same_as<double>;
    { shape.perimeter() } -> std::same_as<double>;
  };

struct DynShape {
  virtual auto area() const -> double {return 0;}  // = 0;
  virtual auto perimeter() const -> double {return 0;}  // = 0;
};

// template<Shape ShapeImpl>
// auto area_per_perimeter(const ShapeImpl& shape) -> double {
// auto area_per_perimeter(const DynShape& shape) -> double {
auto area_per_perimeter(const Shape auto& shape) -> double {
  // std::cout << "type: " << typeid(decltype(shape)).name() << "\n";
  // std::cout << "size: " << sizeof(decltype(shape)) << "\n";
  return shape.area() / shape.perimeter();
}

// Circle

struct CircleData {
  double radius;
};

struct Circle: CircleData, virtual DynShape {
  Circle(CircleData data): CircleData(data) {}
  auto area() const -> double override {
    return std::numbers::pi * radius * radius;
  }
  auto perimeter() const -> double override {
    return std::numbers::pi * radius * 2;
  }
};

// Rectangle

struct RectangleData {
  double width;
  double height;
};

struct Rectangle: RectangleData, virtual DynShape {
  Rectangle(RectangleData data): RectangleData(data) {}
  auto area() const -> double override {
    return width * height;
  }
  auto perimeter() const -> double override {
    return 2 * (width + height);
  }
};

// Main

auto main() -> int {
  auto c1 = Circle({.radius = 1.0});
  auto c2 = Circle({.radius = 2.5});
  auto r1 = Rectangle({.width = 3.0, .height = 3.0});
  auto r2 = Rectangle({.width = 4.0, .height = 6.0});
  std::cout << "c1: " << c1.area() << ", " << c1.perimeter() << "\n";
  std::cout << area_per_perimeter(c1) << "\n";
  std::cout << area_per_perimeter(r1) << "\n";
  std::cout << "-- vec --" << "\n";
  auto circles = std::vector<Circle>{c1, c2};
  auto shapes = std::vector<DynShape*>{&c1, &c2, &r1, &r2};
  for (auto shape: shapes) {
    std::cout << area_per_perimeter(*shape) << "\n";
  }
}
