/* --------------------------------- Header --------------------------------- */


/**
 * @file    point2d.cpp
 * @brief   2D point class
 */


/* -------------------------------- Includes -------------------------------- */


# include <algorithm>
# include <cmath>

# include "point2d.h"


/* ----------------------- Constructors / Destructors ----------------------- */


/**
 * @brief   Creates a 2D point at coordinates (0, 0)
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 *
 * @return  The created point
 */
Point2D::Point2D():
Point2D( 0, 0 )
{}


/**
 * @brief   Creates a 2D point at the specified coordinates
 *
 * @param   x   The x-coordinate
 * @param   y   The y-coordinate
 *
 * @return  The created point
 */
Point2D::Point2D( double x, double y ):
Vector3<double>( x, y, 1 )
{}


/**
 * @brief   Creates a 2D point from a 2D vector of doubles
 *
 * @param   &v  The vector to create the 2D point from
 *
 * @return  The created point
 */
Point2D::Point2D( const Vector2<double> &v ):
Point2D( v[0], v[1] )
{}


/**
 * @brief   Creates a 2D point from a 2x1 matrix of doubles
 *
 * @param   &m  The matrix to create the 2D point from
 *
 * @return  The created point
 */
Point2D::Point2D( const Matrix<double> &m ):
Point2D( m[0][0], m[1][0] )
{}


/**
 * @brief   Creates a 2D point from an existing 2D point
 *
 * @param   point   The 2D point to create from
 *
 * @return  The created point
 */
Point2D::Point2D( const Point2D &p ):
Point2D( p.getX(), p.getY() )
{}


Point2D::~Point2D() = default;


/* -------------------------- Overloaded Operators -------------------------- */


/**
 * @brief   Assigns a point to this point
 *
 * @param   &point  The point to assign
 *
 * @return  A reference to this point
 */
Point2D &Point2D::operator=( const Point2D &p )
{
    setX( p.getX() );
    setY( p.getY() );
    return *this;
}


/**
 * @brief   Adds a 2D point to this 2D point and assigns the sum to
 *          this 2D point
 *
 * @param   &point  The 2D point to add
 *
 * @return  A reference to this 2D point
 */
Point2D &Point2D::operator+=( const Point2D &p )
{
    return *this = *this + p;
}


/**
 * @brief   Subtracts a 2D point from this 2D point and assigns the
 *          difference to this 2D point
 *
 * @param   &point  The 2D point to subtract
 *
 * @return  A reference to this 2D point
 */
Point2D &Point2D::operator-=( const Point2D &p )
{
    return *this = *this - p;
}


/**
 * @brief   Adds a 2D point to this 2D point
 *
 * @param   &point  The 2D point to add
 *
 * @return  The sum of the 2D points
 */
Point2D Point2D::operator+( const Point2D &p ) const
{
    return Point2D( getX() + p.getX(), getY() + p.getY() );
}


/**
 * @brief   Subtracts a 2D point from this 2D point
 *
 * @param   &point  The 2D point to subtract
 *
 * @return  The difference of the 2D points
 */
Point2D Point2D::operator-( const Point2D &p ) const
{
    return Point2D( getX() - p.getX(), getY() - p.getY() );
}


/**
 * @brief   Determines if the magnitude of this point is less than the
 *          magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is less than the magnitude
 *          of the other point, false otherwise
 */
bool Point2D::operator<( const Point2D &p ) const
{
    return magnitude() < p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is less than or equal
 *          to the magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is less than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point2D::operator<=( const Point2D &p ) const
{
    return magnitude() <= p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is greater than the
 *          magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is greater than the magnitude
 *          of the other point, false otherwise
 */
bool Point2D::operator>( const Point2D &p ) const
{
    return magnitude() > p.magnitude();
}


/**
 * @brief   Determines if the magnitude of this point is greater than or
 *          equal to the magnitude of another point
 *
 * @param   &p  The point to compare against
 *
 * @return  True if the magnitude of this point is greater than or equal to
 *          the magnitude of the other point, false otherwise
 */
bool Point2D::operator>=( const Point2D &p ) const
{
    return magnitude() >= p.magnitude();
}


/**
 * @brief   Converts a 2D point to a string and writes it to an output stream
 *
 * @param   &os     The output stream to write to
 * @param   &point  The 2D point to convert
 *
 * @return  The output stream
 */
std::ostream &operator<<( std::ostream &os, const Point2D &p )
{
    p.out( os );
    return os;
}


/* ---------------------------- Public Functions ---------------------------- */



/**
 * @brief   Creates a dynamically allocated clone of this 2D point
 *
 * @param   void
 *
 * @return  A pointer to cloned 2D point
 */
Point2D *Point2D::clone() const
{
    return new Point2D( getX(), getY() );
}


/**
 * @brief   Gets the magnitude of the vector between the origin and this
 *          2D point
 *
 * @param   void
 *
 * @return  The magnitude of the vector between the origin and this 2D point
 */
double Point2D::magnitude() const
{
    return sqrt( pow( getX(), 2 ) + pow( getY(), 2 ) );
}


/**
 * @brief   Gets the direction of the vector between this 2D point and another
 *          2D point in radians
 *
 * @param   void
 *
 * @return  The direction of the vector between this 2D point and another 2D
 *          point in radians
 */
double Point2D::direction( const Point2D &p ) const
{
    double dot = getX() * p.getX() + getY() * p.getY();
    double det = getX() * p.getY() - getY() * p.getX();
    double angle = atan2( det, dot );

    // if ( angle < 0 )
    // {
    //     angle = 2 * M_PI + angle;
    // }

    return angle;
}


/**
 * @brief   Calculates the dot product between the vectors created by this
 *          2D point and the origin and another 2D point and the origin
 *
 * @param   &p  The 2D point to calculate the dot product with
 *
 * @return  The dot product of the vectors created by the 2D points
 *          and the origin
 */
double Point2D::dotProduct( const Point2D &p ) const
{
    return ( ( getX() * p.getX() ) + ( getY() * p.getY() ) );
}


/**
 * @brief   Converts this 2D point to a string and writes it to an output
 *          stream
 *
 * @param   &os     The output stream to write to
 *
 * @return  The output stream
 */
std::ostream &Point2D::out( std::ostream &os ) const
{
    os << "POINT2D( " << getX() << " " << getY() << " )";
    return os;
}


/**
 * @brief   Performs a deep copy of a matrix of 2D point pointers
 *
 * @param   &v      The matrix to copy
 *
 * @return  The copied matrix
 */
Matrix<Point2D*> Point2D::matrixDeepCopy( const Matrix<Point2D*> &m )
{
    Matrix<Point2D*> clone = Matrix<Point2D*>( m );

    unsigned int rows = clone.getRows();
    unsigned int cols = clone.getColumns();

    for ( unsigned int col = 0; col < cols; col++ )
    {
        for ( unsigned int row = 0; row < rows; row++ )
        {
            clone[row][col] = m[row][col]->clone();
        }
    }

    return clone;
}


/**
 * @brief   Performs a deep delete of a matrix of 2D point pointers
 *
 * @param   &v      The matrix to delete
 *
 * @return  void
 */
void Point2D::matrixDeepDelete( const Matrix<Point2D*> &m )
{
    unsigned int rows = m.getRows();
    unsigned int cols = m.getColumns();

    for ( unsigned int col = 0; col < cols; col++ )
    {
        for ( unsigned int row = 0; row < rows; row++ )
        {
            delete m[row][col];
        }
    }
}


/**
 * @brief   Performs a deep copy of a vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
std::vector<Point2D*> Point2D::vectorDeepCopy( const std::vector<Point2D*> &v )
{
    std::vector<Point2D*> clone = std::vector<Point2D*>();

    std::for_each( v.begin(), v.end(), [&clone]( Point2D *p )
                   {
                       Point2D *pClone = p->clone();
                       clone.push_back( pClone );
                   }
    );

    return clone;
}


/**
 * @brief   Performs a deep delete of a vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vectorDeepDelete( const std::vector<Point2D*> &v )
{
    std::for_each( v.begin(), v.end(), []( Point2D *p )
                   {
                       delete p;
                   }
    );
}


/**
 * @brief   Performs a deep copy a 2D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector2<Point2D*> Point2D::vector2DeepCopy( const Vector2<Point2D*> &v )
{
    return Vector2<Point2D*>( v[0]->clone(), v[1]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 2D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector2DeepDelete( const Vector2<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
}


/**
 * @brief   Performs a deep copy a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector3<Point2D*> Point2D::vector3DeepCopy( const Vector3<Point2D*> &v )
{
    return Vector3<Point2D*>( v[0]->clone(), v[1]->clone(), v[2]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector3DeepDelete( const Vector3<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
}


/**
 * @brief   Performs a deep copy a 4D vector of 2D point pointers
 *
 * @param   &v      The vector to copy
 *
 * @return  The copied vector
 */
Vector4<Point2D*> Point2D::vector4DeepCopy( const Vector4<Point2D*> &v )
{
    return Vector4<Point2D*>( v[0]->clone(), v[1]->clone(), v[2]->clone(), v[3]->clone() );
}


/**
 * @brief   Performs a deep deletion of a 3D vector of 2D point pointers
 *
 * @param   &v      The vector to delete
 *
 * @return  void
 */
void Point2D::vector4DeepDelete( const Vector4<Point2D*> &v )
{
    delete v.getX();
    delete v.getY();
    delete v.getZ();
    delete v.getW();
}


/* -------------------------------------------------------------------------- */