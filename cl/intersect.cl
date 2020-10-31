#include "cl/ray_trace.h"

t_roots	ft_intersect_ray_obj(float3 o, float3 d, t_object obj)
{
	float3	k;
	float		disc;
	t_roots	t;
	t_ray		pr;
	float3	oc;
	float3	texture;
	int 		i;

	if (obj.type == 's')
	{
		
		oc = o - obj.center;
		k.x = dot(d, d);
		k.y = 2.0f * dot(oc, d);
		k.z = dot(oc, oc) - native_powr(obj.radius, 2);
		disc = k.y * k.y - 4 * k.x * k.z;

		if (disc < 0)
		{
			t.root1 = INF;
			t.root2 = INF;
			return (t);
		}

		t.root1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
		t.root2 = (-k.y - sqrt(disc)) / (2.0f * k.x);

		if (t.root1 < t.root2)
			disc = t.root1;
		else
			disc = t.root2;

		if (obj.textype == 'o')
		{
			pr.o = o + (d * (t.root1));
			pr.d = pr.o - (obj.center);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(obj, pr.d, pr.o);
			if (texture.x < 100)
				t.root1 = INF;

			pr.o = o + (d * (t.root2));
			pr.d = pr.o - (obj.center);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(obj, pr.d, pr.o);
			if (texture.x < 100)
				t.root2 = INF;
			
		}

		if (obj.textype == 'd')
		{
			pr.o = o + (d * (disc));
			pr.d = pr.o - (obj.center);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(obj, pr.d, pr.o) / 255;
			texture.x = (1 - texture.x) / obj.radius / 2;
			k.z = dot(oc, oc) - pow((obj.radius -  texture.x), 2);

			disc = k.y * k.y - 4 * k.x * k.z;
			i = 0;
			{
				t.root1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
				t.root2 = (-k.y - sqrt(disc)) / (2.0f * k.x);
			}
			
		}
	}
	else if (obj.type == 'p')
	{
		t.root1 = INF;
		t.root2 = INF;
		oc = o - obj.center;
		k.x = dot(d, obj.norm);

		t.root1 = - dot(oc, obj.norm) / k.x;
		t.root2 = - dot(oc, obj.norm) / k.x;
		if (k.x < 0)
			t.root1 = INF;
		else
			t.root2 = INF;
	}
	else if (obj.type == 'c')
	{
		oc = o - obj.center;
		k.x = dot((d - (obj.norm * dot(d, obj.norm))), (d - (obj.norm * dot(d, obj.norm))));
		k.y = 2.0f * dot((d - (obj.norm * dot(d, obj.norm))), (oc - (obj.norm * dot(oc, obj.norm))));
		k.z = dot((oc - (obj.norm * dot(oc, obj.norm))), (oc - (obj.norm * dot(oc, obj.norm)))) - obj.radius * obj.radius;
		disc = k.y * k.y - 4.0f * k.x * k.z;
		if (disc < 0)
		{
			t.root1 = INF;
			t.root2 = INF;
			return (t);
		}
		t.root1 = (-k.y + sqrt(disc)) / (2.0f * k.x);
		t.root2 = (-k.y - sqrt(disc)) / (2.0f * k.x);

		if (obj.textype == 'o')
		{
			pr.o = o + (d * (t.root1));
			pr.d = pr.o - (obj.center);
			pr.d = cross(pr.d, obj.norm);
			pr.d = cross(obj.norm, pr.d);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(obj, pr.d, pr.o);
			if (texture.x < 100)
				t.root1 = INF;

			pr.o = o + (d * (t.root2));
			pr.d = pr.o - (obj.center);
			pr.d = cross(pr.d, obj.norm);
			pr.d = cross(obj.norm, pr.d);
			pr.d = pr.d * (1.0f / length(pr.d));

			texture = gtexture(obj, pr.d, pr.o);
			if (texture.x < 100)
				t.root2 = INF;
		}
	}

	else if (obj.type == 't')
	{
		oc = o - obj.center;
		k.x = pow(native_cos(obj.alpha), 2) * dot((d - (obj.norm * dot(d, obj.norm))), (d - (obj.norm * dot(d, obj.norm)))) - pow(native_sin(obj.alpha) * dot(d, obj.norm), 2.0f);
		k.y = 2.0f * pow(native_cos(obj.alpha), 2.0f) * dot((d - (obj.norm * dot(d, obj.norm))), (oc - (obj.norm * dot(oc, obj.norm)))) - 2.0f * pow(native_sin(obj.alpha), 2.0f) * dot(d, obj.norm) * dot(oc, obj.norm);
		k.z = pow(native_cos(obj.alpha), 2.0f) * dot((oc - (obj.norm * dot(oc, obj.norm))), (oc -(obj.norm * dot(oc, obj.norm)))) - pow(native_sin(obj.alpha) * dot(oc, obj.norm), 2.0f);

		disc = k.y * k.y - 4.0f * k.x * k.z;
		if (disc < 0)
		{
			t.root1 = INF;
			t.root2 = INF;
			return (t);
		}
		t.root1 = (-k.y + sqrt(disc)) / (2 * k.x);
		t.root2 = (-k.y - sqrt(disc)) / (2 * k.x);
	}

	
	return(t);
}
