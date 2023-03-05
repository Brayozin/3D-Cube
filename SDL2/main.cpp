#include "screen.h"
#include <cstdlib>
// include sleep
#include <numeric>
#include <unistd.h>

struct points3 {
  float x, y, z;
};

struct lineConnection {
  float a, b;
};

void rotate(points3 &point, float x = 1, float y = 1, float z = 1) {
  float rad = 0;

  /*-- rotate around x axis --*/
  rad = x;
  point.y = point.y * cos(rad) - point.z * sin(rad);
  point.z = point.y * sin(rad) + point.z * cos(rad);

  /*-- rotate around y axis --*/
  rad = y;
  point.x = point.x * cos(rad) + point.z * sin(rad);
  point.z = -point.x * sin(rad) + point.z * cos(rad);

  /*-- rotate around z axis --*/
  rad = z;
  point.x = point.x * cos(rad) - point.y * sin(rad);
  point.y = point.x * sin(rad) + point.y * cos(rad);
};

void line(Screen &screen, float x1, float y1, float x2, float y2) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  float length = sqrt(dx * dx + dy * dy);
  float angle = atan2(dy, dx);

  for (float i = 0; i < length; i++) {
    float x = x1 + (i * cos(angle));
    float y = y1 + (i * sin(angle));
    screen.pixel(x, y);
  }
};

int main() {
  Screen screen;

  // points of the cube - vertices (8)
  vector<points3> points{
    {100,100,100},
    {200,100,100},
    {200,200,100},
    {100,200,100},

    {100,100,200},
    {200,100,200},
    {200,200,200},
    {100,200,200},
  };

  // connections between the points
  vector<lineConnection> connections{
    {0,1},
    {1,2},
    {2,3},
    {3,0},

    {4,5},
    {5,6},
    {6,7},
    {7,4},

    {0,4},
    {1,5},
    {2,6},
    {3,7},
  };

  // center of the cube
  points3 center = {0, 0, 0};
  for (auto &p : points) {
    center.x += p.x;
    center.y += p.y;
    center.z += p.z;
  }
  center.x /= points.size();
  center.y /= points.size();
  center.z /= points.size();

  while (true) {
    for (auto &p : points) {
      // move the cube to the center of the screen
      p.x -= center.x;
      p.y -= center.y;
      p.z -= center.z;
      rotate(p, 0.002, 0.001, 0.004);
      // move the cube back to the original position
      p.x += center.x;
      p.y += center.y;
      p.z += center.z;

      // draw the cube (psychadelic)
      // line(screen, p.x, p.y, points[0].x, points[0].y);
      // line(screen, p.x, p.y, points[1].x, points[1].y);
      // line(screen, p.x, p.y, points[2].x, points[2].y);
      // line(screen, p.x, p.y, points[3].x, points[3].y);
      // line(screen, p.x, p.y, points[4].x, points[4].y);
      // line(screen, p.x, p.y, points[5].x, points[5].y);
      // line(screen, p.x, p.y, points[6].x, points[6].y);
      // line(screen, p.x, p.y, points[7].x, points[7].y);
      // line(screen, p.x, p.y, points[0].x, points[0].y);
      
      // draw the cube (normal)
      for (auto &c : connections) {
        line(screen, points[c.a].x, points[c.a].y, points[c.b].x, points[c.b].y);
      }



      screen.pixel(p.x, p.y);

    };
    screen.show();
    screen.clear();

    screen.input();
    SDL_Delay(30);
  }

  return 0;
}