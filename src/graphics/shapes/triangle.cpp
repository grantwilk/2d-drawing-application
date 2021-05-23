/* --------------------------------- Header --------------------------------- */


/**
 * @file    triangle.cpp
 * @brief   Triangle shape
 */


/* -------------------------------- Includes -------------------------------- */


# include <sstream>
# include "color.h"
# include "triangle.h"


/* --------------------- Constructors / Destructors --------------------- */


/**
 * @brief   Creates a black triangle from three points
 *
 * @param   &start  The starting point of the triangle
 * @param   &mid    The middle point of the triangle
 * @param   &end    The ending point of the triangle
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Point2D &start, const Point2D &mid, const Point2D &end ):
Triangle( start, mid, end, Color( 0, 0, 0 ) )
{}


/**
 * @brief   Creates a colored triangle from three points
 *
 * @param   &start  The starting point of the triangle
 * @param   &mid    The middle point of the triangle
 * @param   &end    The ending point of the triangle
 * @param   &color  The color of the triangle
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Point2D &start, const Point2D &mid, const Point2D &end, const Color &color ):
Shape( color, midpoint( start, mid, end ) ),
verts( Vector3<Point2D*>( start.clone(), mid.clone(), end.clone() ) )
{}


/**
 * @brief   Creates a triangle from an existing triangle
 *
 * @param   &triangle   The triangle to create from
 *
 * @return  The created triangle
 */
Triangle::Triangle( const Triangle &triangle ) :
Shape( triangle.color, triangle.origin ), verts( triangle.verts )
{}


/**
 * @brief   Triangle destructor
 *
 * @param   void
 *
 * @return  void
 */
Triangle::~Triangle()
{
    Point2D::vector3DeepDelete( verts );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a triangle to this triangle
 *
 * @param   &triangle   The triangle to assign to this triangle
 *
 * @return  A reference to this triangle
 */
Triangle &Triangle::operator=( const Triangle &triangle )
{
    Point2D::vector3DeepDelete( verts );

    this->verts = Point2D::vector3DeepCopy( triangle.verts );
    this->color = triangle.color;
    this->origin = triangle.origin;

    return *this;
}


/**
 * @brief   Gets an immutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  An immutable reference to the vertex at the specified index
 */
const Point2D &Triangle::operator[]( unsigned int index ) const
{
    return *verts[index];
}


/**
 * @brief   Gets a mutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  A mutable reference to the vertex at the specified index
 */
Point2D &Triangle::operator[]( unsigned int index )
{
    return *verts[index];
}


/**
 * @brief   Converts a triangle to a string and writes it to an output stream
 *
 * @param   &os         The output stream to write to
 * @param   &triangle   The triangle to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Triangle &triangle )
{
    triangle.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */


/**
 * @brief   Draws this shape to a graphics context
 *
 * @param   *gc     The graphics context to draw to
 * @param   *vc     The view context to draw with
 *
 * @return  void
 */
void Triangle::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    // convert from model to device coordinates
    Point2D start = vc->modelToDevice( *verts[0] );
    Point2D mid = vc->modelToDevice( *verts[1] );
    Point2D end = vc->modelToDevice( *verts[2] );

    // set color
    gc->setColor( color.toX11() );

    // draw lines
    gc->drawLine( ( int ) start.getX(), ( int ) start.getY(),
                  ( int ) mid.getX(),   ( int ) mid.getY() );

    gc->drawLine( ( int ) mid.getX(),   ( int ) mid.getY(),
                  ( int ) end.getX(),   ( int ) end.getY() );

    gc->drawLine( ( int ) end.getX(),   ( int ) end.getY(),
                  ( int ) start.getX(), ( int ) start.getY() );
}


/**
 * @brief   Clones this triangle
 *
 * @param   void
 *
 * @return  The cloned copy of this triangle
 */
Triangle *Triangle::clone() const
{
    return new Triangle( *verts[0], *verts[1], *verts[2], color );
}


/**
 * @brief   Converts this triangle to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Triangle::out( std::ostream &os ) const
{
    Shape::out( os );
    os << "  VERTICES( " << *verts[0] << " "
                         << *verts[1] << " "
                         << *verts[2] << " )";
    return os;
}


/**
 * @brief   Extracts a triangle from an input stream and assigns it to this
 *          triangle
 *
 * @param   &os     The input stream to extract from
 *
 * @return  A reference to the input stream
 */
std::istream &Triangle::in( std::istream &is )
{
    // process shape attributes
    Shape::in( is );

    // get description string
    std::string desc;
    std::getline( is, desc );

    // tokenize the description string
    std::vector<std::string> tokens;
    std::stringstream ss = std::stringstream( desc );

    while( ss )
    {
        std::string token;
        ss >> token;
        tokens.push_back( token );
    }

    // validate that the line describes a triangle
    if ( ( tokens.size() != 25 )      || ( tokens[10] != "VERTICES(" ) ||
         ( tokens[11] != "POINT2D(" ) || ( tokens[15] != "POINT2D(" )  ||
         ( tokens[19] != "POINT2D(" ) )
    {
        throw ShapeException("Invalid triangle description.");
    }

    // extract and set the line's vertices
    double startX = std::stod( tokens[ 12 ] );
    double startY = std::stod( tokens[ 13 ] );
    double midX = std::stod( tokens[ 16 ] );
    double midY = std::stod( tokens[ 17 ] );
    double endX = std::stod( tokens[ 20 ] );
    double endY = std::stod( tokens[ 21 ] );

    Point2D::vector3DeepDelete( verts );
    verts = Vector3<Point2D*>(
        new Point2D( startX, startY),
        new Point2D( midX, midY),
        new Point2D( endX, endY )
    );

    return is;
}

/* ---------------------------- Private Functions --------------------------- */

/**
 * @brief   Determines the midpoint between three points
 *
 * @param   &a  The first point
 * @param   &b  The second point
 * @param   &c  The third point
 *
 * @return  The midpoint between three points
 */
Point2D Triangle::midpoint( const Point2D &a, const Point2D &b, const Point2D &c )
{
    return Point2D( ( a.getX() + b.getX() + c.getX() ) / 3,
                    ( a.getY() + b.getY() + c.getY() ) / 3 );
}

/* -------------------------------------------------------------------------- */