/* --------------------------------- Header --------------------------------- */


/**
 * @file    polygon.cpp
 * @brief   Polygon shape
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <sstream>

# include "color.h"
# include "polygon.h"


/* --------------------- Constructors / Destructors --------------------- */


/**
 * @brief   Creates a black polygon from a vector of points
 *
 * @param   &verts  The points of the polygon
 *
 * @return  The created polygon
 */
Polygon::Polygon( const std::vector<Point2D*> &verts ):
Polygon( verts, Color( 0, 0, 0 ) )
{}


/**
 * @brief   Creates a colored polygon from a vector of points
 *
 * @param   &verts  The points of the polygon
 * @param   &color  The color of the polygon
 *
 * @return  The created polygon
 */
Polygon::Polygon( const std::vector<Point2D*> &verts, const Color &color ):
Shape( color, midpoint( verts ) ),
verts( Point2D::vectorDeepCopy( verts ) )
{}


/**
 * @brief   Creates a polygon from an existing polygon
 *
 * @param   &polygon    The polygon to create from
 *
 * @return  The created polygon
 */
Polygon::Polygon( const Polygon &polygon ) :
Shape( polygon.color, polygon.origin ), verts( polygon.verts )
{}


/**
 * @brief   Polygon destructor
 *
 * @param   void
 *
 * @return  void
 */
Polygon::~Polygon()
{
    Point2D::vectorDeepDelete( verts );
}


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a polygon to this polygon
 *
 * @param   &polygon    The polygon to assign to this polygon
 *
 * @return  A reference to this polygon
 */
Polygon &Polygon::operator=( const Polygon &polygon )
{
    Point2D::vectorDeepDelete( verts );

    this->verts = Point2D::vectorDeepCopy( polygon.verts );
    this->color = polygon.color;
    this->origin = polygon.origin;

    return *this;
}


/**
 * @brief   Gets an immutable reference to the vertex at the specified index
 *
 * @param   index   The index of the vertex
 *
 * @return  An immutable reference to the vertex at the specified index
 */
const Point2D &Polygon::operator[]( unsigned int index ) const
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
Point2D &Polygon::operator[]( unsigned int index )
{
    return *verts[index];
}


/**
 * @brief   Converts a polygon to a string and writes it to an output stream
 *
 * @param   &os         The output stream to write to
 * @param   &polygon    The polygon to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Polygon &polygon )
{
    polygon.out( os );
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
void Polygon::draw( GraphicsContext *gc, ViewContext *vc ) const
{
    // set color
    gc->setColor( color.toX11() );

    // draw polygon
    for ( unsigned int i = 0; i < verts.size() - 1; i++ )
    {
        // convert from model to device coordinates
        Point2D current = vc->modelToDevice( *verts[i] ) ;
        Point2D next = vc->modelToDevice( *verts[i+1] ) ;

        // draw line
        gc->drawLine(
            ( int ) current.getX(), ( int ) current.getY(),
            ( int ) next.getX(),    ( int ) next.getY()
        );
    }

    // draw closing edge if applicable
    if ( verts.size() > 2 )
    {
        // convert from model to device coordinates
        Point2D first = vc->modelToDevice( *verts[0] );
        Point2D last = vc->modelToDevice( *verts[verts.size() - 1] );

        // draw line
        gc->drawLine(
            ( int ) first.getX(), ( int ) first.getY(),
            ( int ) last.getX(),  ( int ) last.getY()
        );
    }
}


/**
 * @brief   Clones this polygon
 *
 * @param   void
 *
 * @return  The cloned copy of this polygon
 */
Polygon *Polygon::clone() const
{
    return new Polygon( verts, color );
}


/**
 * @brief   Converts this polygon to a string and flushes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  A reference to the output stream
 */
std::ostream &Polygon::out( std::ostream &os ) const
{
    Shape::out( os );
    os << "  VERTICES( ";
    std::for_each( verts.begin(), verts.end(), [&os]( Point2D *vert )
        {
            os << *vert << " ";
        }
    );
    os << ")";

    return os;
}


/**
 * @brief   Extracts a polygon from an input stream and assigns it to this
 *          polygon
 *
 * @param   &os     The input stream to extract from
 *
 * @return  A reference to the input stream
 */
std::istream &Polygon::in( std::istream &is )
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

    // validate that the line describes a polygon
    if ( ( tokens.size() < 25 )       || ( tokens[10] != "VERTICES(" ) ||
         ( tokens[11] != "POINT2D(" ) || ( tokens[15] != "POINT2D(" )  ||
         ( tokens[19] != "POINT2D(" ) )
    {
        throw ShapeException("Invalid polygon description.");
    }

    // extract points and store in a vector
    std::vector<Point2D*> newVerts = std::vector<Point2D*>();

    for ( unsigned int i = 12; i < tokens.size() - 1; i += 4 )
    {
        double x = std::stod( tokens[i] );
        double y = std::stod( tokens[i+1] );
        newVerts.push_back( new Point2D( x, y ) );
    }

    // deep delete existing verts
    Point2D::vectorDeepDelete( verts );

    // reassign new verts
    verts = newVerts;

    return is;
}

/* ---------------------------- Private Functions --------------------------- */

/**
 * @brief   Determines the midpoint between three points
 *
 * @param   &verts  The vertices to find the midpoint of
 *
 * @return  The midpoint between three points
 */
Point2D Polygon::midpoint( const std::vector<Point2D*> &verts )
{
    double sumX = 0;
    double sumY = 0;

    std::for_each( verts.begin(), verts.end(), [ &sumX, &sumY ]( Point2D *vert )
       {
           sumX += vert->getX();
           sumY += vert->getY();
       }
    );

    return Point2D( ( sumX / verts.size() ), ( sumY / verts.size() ) );
}

/* -------------------------------------------------------------------------- */