// Shape

trait Shape {
  fn area(&self) -> f64;
  fn perimeter(&self) -> f64;
  fn area_per_perimeter(&self) -> f64 {
      // dbg!(std::any::type_name::<Self>());
      // dbg!(std::mem::size_of::<&Self>());
      // dbg!(std::mem::size_of_val(self));
      self.area() / self.perimeter()
  }
}

// fn area_per_perimeter<ShapeImpl>(shape: &ShapeImpl) -> f64
// where
//     ShapeImpl: Shape + ?Sized,
// {
//     // dbg!(std::any::type_name::<ShapeImpl>());
//     // dbg!(std::mem::size_of::<&ShapeImpl>());
//     // dbg!(std::mem::size_of_val(shape));
//     shape.area() / shape.perimeter()
// }

// Circle

#[derive(Copy, Clone, Debug)]
struct Circle {
  radius: f64,
}

impl Shape for Circle {
  fn area(&self) -> f64 {
      std::f64::consts::PI * self.radius.powi(2)
  }
  fn perimeter(&self) -> f64 {
      std::f64::consts::PI * self.radius * 2.0
  }
}

// Rectangle

#[derive(Copy, Clone, Debug)]
struct Rectangle {
  width: f64,
  height: f64,
}

impl Shape for Rectangle {
  fn area(&self) -> f64 {
      self.width * self.height
  }
  fn perimeter(&self) -> f64 {
      2.0 * (self.width + self.height)
  }
}

// Main

fn main() {
  let c1 = Circle { radius: 1.0 };
  let c2 = Circle { radius: 2.5 };
  let r1 = Rectangle { width: 3.0, height: 3.0 };
  let r2 = Rectangle { width: 4.0, height: 6.0 };
  println!("{:?}: {}, {}", c1, c1.area(), c1.perimeter());
  println!("{}", c1.area_per_perimeter());
  println!("{}", r1.area_per_perimeter());
  println!("-- vec --");
  let _circles = vec![c1, c2];
  let shapes: Vec<&dyn Shape> = vec![&c1, &c2, &r1, &r2];
  for shape in shapes {
      println!("{}", shape.area_per_perimeter());
  }
}
