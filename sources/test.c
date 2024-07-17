#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    Vec3 position;
    Vec3 orientation;
    float fov;
} Camera;

void normalize(Vec3* v) {
    float norm = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
}

Vec3 cross_product(Vec3 a, Vec3 b) {
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

Camera init_camera(float px, float py, float pz, float ox, float oy, float oz, float fov) {
    Camera cam;
    cam.position.x = px;
    cam.position.y = py;
    cam.position.z = pz;

    float norm = sqrt(ox * ox + oy * oy + oz * oz);
    cam.orientation.x = ox / norm;
    cam.orientation.y = oy / norm;
    cam.orientation.z = oz / norm;

    cam.fov = fov * M_PI / 180.0; // Conversion du FOV en radians

    return cam;
}

void print_camera_info(Camera cam) {
    printf("Camera Information:\n");
    printf("Position: (%f, %f, %f)\n", cam.position.x, cam.position.y, cam.position.z);
    printf("Orientation: (%f, %f, %f)\n", cam.orientation.x, cam.orientation.y, cam.orientation.z);
    printf("FOV: %f radians\n", cam.fov);
}

Vec3 calculate_ray_direction(int i, int j, int image_width, int image_height, Camera camera) {
    float aspect_ratio = (float)image_width / (float)image_height;
    float screen_width = 2.0f * tan(camera.fov / 2.0f);
    float screen_height = screen_width / aspect_ratio;

    Vec3 forward = camera.orientation;

    Vec3 up_global = {0.0f, 1.0f, 0.0f};
    Vec3 right = cross_product(up_global, forward);
    normalize(&right);

    Vec3 up = cross_product(forward, right);
    normalize(&up);

    float u = (i + 0.5f) / (float)image_width * screen_width - screen_width / 2.0f;
    float v = (j + 0.5f) / (float)image_height * screen_height - screen_height / 2.0f;

    Vec3 ray_dir = {
        u * right.x + v * up.x + forward.x,
        u * right.y + v * up.y + forward.y,
        u * right.z + v * up.z + forward.z
    };

    normalize(&ray_dir);

    return ray_dir;
}

int main() {
    // Initialisation de la caméra avec les valeurs fournies
    Camera cam = init_camera(-50.0, 0.0, 20.0, 0.0, 0.0, 1.0, 70.0);

    // Afficher les informations de la caméra pour vérifier
    print_camera_info(cam);

    // Exemple de calcul de direction de rayon pour un pixel spécifique
    int image_width = 800;
    int image_height = 600;
    int pixel_x = 400;
    int pixel_y = 300;

    Vec3 ray_direction = calculate_ray_direction(pixel_x, pixel_y, image_width, image_height, cam);

    printf("Ray direction for pixel (%d, %d): (%f, %f, %f)\n", pixel_x, pixel_y, ray_direction.x, ray_direction.y, ray_direction.z);

    return 0;
}
