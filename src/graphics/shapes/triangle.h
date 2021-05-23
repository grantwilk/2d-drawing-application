/* --------------------------------- Header --------------------------------- */


/**
 * @file    triangle.h
 * @brief   2D triangle shape class
 */


/* ------------------------------ Header Guard ------------------------------ */


# ifndef SHAPE_TRIANGLE_H
# define SHAPE_TRIANGLE_H


/* -------------------------------- Includes -------------------------------- */


# include "point2d.h"
# include "shape.h"


/* --------------------------------- Class ---------------------------------- */


class Triangle : public Shape
{
    /* =============================== PUBLIC =============================== */

public:

    /* --------------------- Constructors / Destructors --------------------- */


    Triangle( const Point2D &start, const Point2D &mid, const Point2D &end );
    Triangle( const Point2D &start, const Point2D &mid, const Point2D &end, const Color &color );
    Triangle( const Triangle &tri );

    ~Triangle() override;


    /* ------------------------ Overloaded Operators ------------------------ */


    Triangle &operator=( const Triangle &triangle );

    const Point2D &operator[]( unsigned int index ) const override;
    Point2D &operator[]( unsigned int index ) override;


    /* ------------------------------ Functions ----------------------------- */


    void draw( GraphicsContext *gc, ViewContext *vc ) const override;
    Triangle *clone() const override;

    std::ostream &out( std::ostream &os ) const override;
    std::istream &in( std::istream &is ) override;


    /* =============================== PRIVATE ============================== */

private:

    /* ----------------------------- Attributes ----------------------------- */


    Vector3<Point2D*> verts;


    /* ------------------------------ Functions ----------------------------- */


    static Point2D midpoint( const Point2D &a, const Point2D &b, const Point2D &c );


    /* ====================================================================== */
};


/* ----------------------- Global Overloaded Operators ---------------------- */


std::ostream &operator<<( std::ostream &os, const Triangle &triangle );


/* --------------------------------- Footer --------------------------------- */


# endif // SHAPE_TRIANGLE_H


/* -------------------------------------------------------------------------- */