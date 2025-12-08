
typedef struct s_obj t_obj;

typedef struct s_ray
{
    double o[3];
    double d[3];
} t_ray;

typedef struct s_hit
{
    double  t;
    double  p[3]; // hit position in world
    double  n[3]; // normal in world, unit, oriented
    const t_obj   *obj; // pointer to object for albedo info
}   t_hit;

typedef int (*t_intersect_fn)(const t_obj *self, const t_ray *ray, t_hit *hit);

// object type
typedef enum s_obj_type
{
    OBJ_SPHERE,
    OBJ_PLANE,
    OBJ_CYLINDER,
    OBJ_CONE,        // optional future
    OBJ_ELLIPSOID,   // optional future
    OBJ_INVALID      // optional sentinel
}	t_obj_type;

// object position/orientation in global frame
// for sphere the origin, for plane normal etc
typedef struct s_obj_pos
{
    double  pos[3];   // position in the world space
    double  dir[3];   // orientation axis / normal (unit ector)
}   t_obj_pos;

// plane needs nothing
// sphere -> needs radius info
typedef struct s_sphere
{
	double	radius;
}	t_sphere;

// cylinder -> needs axis
typedef struct s_cylinder
{
	double	radius;
	double	height;
}	t_cylinder;

// generic shape data: tagged by t_obj_type
typedef union u_shape_data
{
    t_sphere    sphere;
    t_cylinder  cylinder;
    // add cone, ellipsoid, ... later
}   t_shape_data;

// whole object info
typedef struct s_obj
{
    t_obj_type		type;
    t_obj_pos		pos;
    t_shape_data	shape;
    t_intersect_fn  intersect;
    double          albedo[3]; // vec3 in [0,1] (RGB/255).

}   t_obj;
