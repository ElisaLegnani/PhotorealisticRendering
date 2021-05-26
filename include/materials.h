#include <memory>
#include "hitrecord.h"
#include "hdrimage.h"

#ifndef _materials_h_
#define _materials_h_

struct Pigment {
    virtual Color get_color(Vec2d uv) = 0;
};

struct UniformPigment : public Pigment {

    Color color;

    UniformPigment(Color c) : color{c} {}

    Color get_color(Vec2d uv){
        return color;
    }
};

struct ImagePigment : public Pigment {

    HdrImage image;

    ImagePigment(HdrImage i) : image{i} {}

    Color get_color(Vec2d uv){

        int col = int(uv.u * image.width);
        int row = int(uv.v * image.height);

        if (col >= image.width) col = image.width - 1;
        if (row >= image.height) row = image.height - 1;

        return image.get_pixel(col, row);
    }
};

struct CheckeredPigment : public Pigment {
    
    Color color1;
    Color color2;
    int n_steps;

    CheckeredPigment(Color c1, Color c2, int ns=10) : color1{c1}, color2{c2}, n_steps{ns} {} 

    Color get_color(Vec2d uv){

        int u = int(floor(uv.u * n_steps));
        int v = int(floor(uv.v * n_steps));

        if((u % 2) == (v % 2)) return color1;
        else return color2;
    }
};

struct BRDF{

    shared_ptr<Pigment> pigment;

    BRDF(shared_ptr<Pigment> p = make_shared<UniformPigment>(Color(1.0, 1.0, 1.0))) : pigment{p} {} //white

    Color eval(Normal n, Vec dir_in, Vec dir_out, Vec2d uv){
        return Color(0.0, 0.0, 0.0); //black
    }

    //virtual Ray scatter_ray(PCG pcg, Vec dir_in, Vec interaction_point, Normal n, int depth) = 0;
};

struct Material{
    //BRDF brdf;
    shared_ptr<Pigment> emitted_radiance;

    Material(shared_ptr<Pigment> p = make_shared<UniformPigment>(Color(0.0, 0.0, 0.0))) : emitted_radiance{p} {}
    //Material(shared_ptr<BRDF> _brdf = make_shared<DiffuseBRDF>(), shared_ptr<Pigment> p = make_shared<UniformPigment>(Color(0.0, 0.0, 0.0))) : brdf{_brdf}, emitted_radiance{p} {}
};

#endif