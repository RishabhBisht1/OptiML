#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

Vec3 vec_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float vec_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float sphere_intersect(Vec3 ro, Vec3 rd, Vec3 center, float radius) {
    Vec3 oc = vec_sub(ro, center);
    float b = 2.0 * vec_dot(oc, rd);
    float c = vec_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * c;
    if (discriminant < 0)
        return -1.0;
    else
        return (-b - sqrt(discriminant)) / 2.0;
}

int main() {
    int width = 80, height = 40;
    Vec3 camera = {0, 0, 0};
    Vec3 sphere_center = {0, 0, 5};
    float sphere_radius = 1.0;

    for (int y = -height / 2; y < height / 2; y++) {
        for (int x = -width / 2; x < width / 2; x++) {
            Vec3 dir = {x / (float)width, y / (float)height, 1};
            float t = sphere_intersect(camera, dir, sphere_center, sphere_radius);
            if (t > 0)
                printf("@");
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}
