typedef struct
{
	float	u, v;
	float	nx, ny, nz;
	float	x, y, z;
	
} VertexTNV;

typedef struct
{
	float			u, v;
	unsigned int	color;
	float			nx, ny, nz;
	float			x, y, z;
	
} VertexTCNV;

typedef struct
{
	float	u, v;
	float	x, y, z;
	
} VertexTV;

typedef struct
{
	float			u, v;
	unsigned int	color;
	float			x, y, z;
	
} VertexTCV;

typedef struct
{
	float	x, y, z;
	
} VertexV;

typedef struct
{
	float	nx, ny, nz;
	float	x, y, z;
	
} VertexNV;

typedef struct
{
	unsigned int	color;
	float			x, y, z;
	
} VertexCV;

typedef struct
{
	unsigned int	color;
	float			nx, ny, nz;
	float			x, y, z;
	
} VertexCNV;
