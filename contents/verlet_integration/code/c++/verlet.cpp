#include <iomanip>
#include <iostream>
#include <utility>

using vpair = std::pair<double, double>;

double verlet(double pos, double acc, double dt) {

  double prev_pos = pos;
  double time = 0;

  while (pos > 0) {
    time += dt;
    double next_pos = pos * 2 - prev_pos + acc * dt * dt;
    prev_pos = pos;
    pos = next_pos;
  }

  return time;
}

vpair stormer_verlet(double pos, double acc, double dt) {

  double prev_pos = pos;
  double time = 0;
  double vel = 0;
  while (pos > 0) {
    time += dt;
    double next_pos = pos * 2 - prev_pos + acc * dt * dt;
    prev_pos = pos;
    pos = next_pos;

    // The acceleration is constant, so the velocity is
    // straightforward
    vel += acc * dt;
  }

  return std::make_pair(time, vel);
}

vpair velocity_verlet(double pos, double acc, double dt) {

  double time = 0;
  double vel = 0;
  while (pos > 0) {
    time += dt;
    pos += vel * dt + 0.5 * acc * dt * dt;
    vel += acc * dt;
  }

  return std::make_pair(time, vel);
}

int main() {
  double time, vel;

  std::cout << std::fixed << std::setprecision(8);

  // Note that depending on the simulation, you might want to have the
  // Verlet loop outside.

  // For example, if your acceleration chages as a function of time,
  // you might need to also change the acceleration to be read into
  // each of these functions.

  time = verlet(5.0, -10, 0.01);
  std::cout << "Time for Verlet integration is: " \
            << time << std::endl;

  std::tie(time, vel) = stormer_verlet(5.0, -10, 0.01);
  std::cout << "Time for Stormer Verlet integration is: " \
            << time << std::endl;
  std::cout << "Velocity for Stormer Verlet integration is: " \
            << vel << std::endl;

  std::tie(time, vel) = velocity_verlet(5.0, -10, 0.01);
  std::cout << "Time for velocity Verlet integration is: " \
            << time << std::endl;
  std::cout << "Velocity for velocity Verlet integration is: " \
            << vel << std::endl;

  return 0;

}
