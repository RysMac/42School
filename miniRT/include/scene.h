// this contains
// camera, Lights, Objects[] + count, Ambient

typedef struct s_obj t_obj;

typedef struct s_camera
{
    int w;
    int h;
    double fovx;
    double fovy;
    double c[3]; // camera center
    double f[3]; // forward direction
    double r[3]; // right
    double u[3]; // up
} t_camera;

typedef struct s_light
{
    double pos[3];
    double brightness;

}   t_light;

typedef struct s_ambient
{
    double ambient_ratio;
    double ambient_color[3]; // input 0-255 -> rescale for 0-1
}   t_ambient;

typedef struct s_scene
{
    t_camera    camera;
    t_light     light;
    t_ambient   ambient;
    t_obj       *objects; // pointer to whole list of objects
    size_t      count;    // number of all objects
} t_scene;