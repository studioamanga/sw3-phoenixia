


/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns a perpendicular vector from 2 given vectors by taking the cross product.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

swVertex Cross(swVertex vVector1, swVertex vVector2)
{
    swVertex vNormal;                                   // The vector to hold the cross product

    // The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)                                                    // Get the X value
    vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

    // The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
    vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

    // The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
    vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

    return vNormal;                                     // Return the cross product (Direction the polygon is facing - Normal)
}


/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the magnitude of a normal (or any other vector)
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Magnitude(swVertex vNormal)
{
    // This will give us the magnitude or "Norm" as some say, of our normal.
    // Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector

    return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}


/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns a normalize vector (A vector exactly of length 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

swVertex Normalize(swVertex vNormal)
{
    float magnitude = Magnitude(vNormal);               // Get the magnitude of our normal

    // Now that we have the magnitude, we can divide our normal by that magnitude.
    // That will make our normal a total length of 1.  This makes it easier to work with too.

    vNormal.x /= magnitude;                             // Divide the X value of our normal by it's magnitude
    vNormal.y /= magnitude;                             // Divide the Y value of our normal by it's magnitude
    vNormal.z /= magnitude;                             // Divide the Z value of our normal by it's magnitude

    // Finally, return our normalized normal.

    return vNormal;                                     // Return the new normal of length 1.
}


/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the normal of a polygon (The direction the polygon is facing)
/////
/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

swVertex Normal(swVertex vPolygon[])
{                                                       // Get 2 vectors from the polygon (2 sides), Remember the order!
    swVertex vVector1 = vPolygon[2] - vPolygon[0];
    swVertex vVector2 = vPolygon[1] - vPolygon[0];

    swVertex vNormal = Cross(vVector1, vVector2);       // Take the cross product of our 2 vectors to get a perpendicular vector

    // Now we have a normal, but it's at a strange length, so let's make it length 1.

    vNormal = Normalize(vNormal);                       // Use our function we created to normalize the normal (Makes it a length of one)

    return vNormal;                                     // Return our normal at our desired length
}


/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the distance between a plane and the origin
/////
/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float PlaneDistance(swVertex Normal, swVertex Point)
{
    float distance = 0;                                 // This variable holds the distance from the plane tot he origin

    // Use the plane equation to find the distance (Ax + By + Cz + D = 0)  We want to find D.
    // So, we come up with D = -(Ax + By + Cz)
                                                        // Basically, the negated dot product of the normal of the plane and the point. (More about the dot product in another tutorial)
    distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

    return distance;                                    // Return the distance
}


/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This checks to see if a line intersects a plane
/////
/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool IntersectedPlane(swVertex vPoly[], swVertex vLine[], swVertex &vNormal, float &originDistance)
{
    float distance1=0, distance2=0;                     // The distances from the 2 points of the line from the plane

    vNormal = Normal(vPoly);                            // We need to get the normal of our plane to go any further

    // Let's find the distance our plane is from the origin.  We can find this value
    // from the normal to the plane (polygon) and any point that lies on that plane (Any swVertex)
    originDistance = PlaneDistance(vNormal, vPoly[0]);

    // Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

    distance1 = ((vNormal.x * vLine[0].x)  +                    // Ax +
                 (vNormal.y * vLine[0].y)  +                    // Bx +
                 (vNormal.z * vLine[0].z)) + originDistance;    // Cz + D

    // Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)
    
    distance2 = ((vNormal.x * vLine[1].x)  +                    // Ax +
                 (vNormal.y * vLine[1].y)  +                    // Bx +
                 (vNormal.z * vLine[1].z)) + originDistance;    // Cz + D

    // Now that we have 2 distances from the plane, if we times them together we either
    // get a positive or negative number.  If it's a negative number, that means we collided!
    // This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

    if(distance1 * distance2 >= 0)          // Check to see if both point's distances are both negative or both positive
       return false;                        // Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...

    return true;                            // The line intersected the plane, Return TRUE
}


/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This computers the dot product of 2 vectors
/////
/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Dot(swVertex vVector1, swVertex vVector2)
{
    // The dot product is this equation: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
    // In math terms, it looks like this:  V1.V2 = ||V1|| ||V2|| cos(theta)

             //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
    return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}


/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

double AngleBetweenVectors(swVertex Vector1, swVertex Vector2)
{
    // Get the dot product of the vectors
    double dotProduct = Dot(Vector1, Vector2);

    // Get the product of both of the vectors magnitudes
    double vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

    // Get the angle in radians between the 2 vectors
    double angle = acos( dotProduct / vectorsMagnitude );

    // Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate
    if(isnan(angle))
        return 0;

    // Return the angle in radians
    return( angle );
}


/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the intersection point of the line that intersects the plane
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

swVertex IntersectionPoint(swVertex vNormal, swVertex vLine[], double distance)
{
    swVertex vPoint, vLineDir;                  // Variables to hold the point and the line's direction
    double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

    // 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
    vLineDir = vLine[1] - vLine[0];     // Get the Vector of the line
    vLineDir = Normalize(vLineDir);             // Normalize the lines vector


    // 2) Use the plane equation (distance = Ax + By + Cz + D) to find the 
    // distance from one of our points to the plane.
    Numerator = - (vNormal.x * vLine[0].x +     // Use the plane equation with the normal and the line
                   vNormal.y * vLine[0].y +
                   vNormal.z * vLine[0].z + distance);

    // 3) If we take the dot product between our line vector and the normal of the polygon,
    Denominator = Dot(vNormal, vLineDir);       // Get the dot product of the line's vector and the normal of the plane

    // Since we are using division, we need to make sure we don't get a divide by zero error
    // If we do get a 0, that means that there are INFINATE points because the the line is
    // on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).
    // In this case, we should just return any point on the line.

    if( Denominator == 0.0)                     // Check so we don't divide by zero
        return vLine[0];                        // Return an arbitrary point on the line

    dist = Numerator / Denominator;             // Divide to get the multiplying (percentage) factor

    // Now, like we said above, we times the dist by the vector, then add our arbitrary point.
    vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
    vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
    vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

    return vPoint;                              // Return the intersection point
}


/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool InsidePolygon(swVertex vIntersection, swVertex Poly[], long verticeCount)
{
    const double MATCH_FACTOR = 0.99;       // Used to cover up the error in floating point
    double Angle = 0.0;                     // Initialize the angle
    swVertex vA, vB;                        // Create temp vectors

    for (int i = 0; i < verticeCount; i++)      // Go in a circle to each swVertex and get the angle between
    {
        vA = Poly[i] - vIntersection;           // Subtract the intersection point from the current swVertex
                                                // Subtract the point from the next swVertex
        vB = Poly[(i + 1) % verticeCount] - vIntersection;

        Angle += AngleBetweenVectors(vA, vB);   // Find the angle between the 2 vectors and add them all up as we go along
    }

    if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )   // If the angle is greater than 2 PI, (360 degrees)
        return true;                            // The point is inside of the polygon
        
    return false;                               // If you get here, it obviously wasn't inside the polygon, so Return FALSE
}


/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This checks if a line is intersecting a polygon
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool IntersectedPolygon(swVertex vPoly[], swVertex vLine[], int verticeCount)
{
    swVertex vNormal;
    float originDistance = 0;

    // First, make sure our line intersects the plane
                                     // Reference   // Reference
    if(!IntersectedPlane(vPoly, vLine,   vNormal,   originDistance))
        return false;

    // Now that we have our normal and distance passed back from IntersectedPlane(),
    // we can use it to calculate the intersection point.
    swVertex vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

    // Now that we have the intersection point, we need to test if it's inside the polygon.
    if(InsidePolygon(vIntersection, vPoly, verticeCount))
        return true;                            // We collided!   Return success

    return false;                               // There was no collision, so return false
}

/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This checks if a line is intersecting a polygon and return the distance
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float IntersectedPolygonDist(swVertex vPoly[], swVertex vLine[], int verticeCount)
{
    swVertex vNormal;
    float originDistance = 0;

    // First, make sure our line intersects the plane
                                     // Reference   // Reference
    if(!IntersectedPlane(vPoly, vLine,   vNormal,   originDistance))
        return INF_THEO;

    // Now that we have our normal and distance passed back from IntersectedPlane(),
    // we can use it to calculate the intersection point.
    swVertex vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

    // Now that we have the intersection point, we need to test if it's inside the polygon.
    if(InsidePolygon(vIntersection, vPoly, verticeCount))
      {
	//printf(">>  %f %f %f\n", vIntersection.x, vIntersection.y, vIntersection.z);
	float xD=vIntersection.x-vLine[0].x;
	float yD=vIntersection.y-vLine[0].y;
	float zD=vIntersection.z-vLine[0].z;
        return sqrt(xD*xD + yD*yD + zD*zD);                            // We collided!   Return success
      }

    return INF_THEO;                               // There was no collision, so return false
}


/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the distance between 2 3D points
/////
/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Distance(swVertex vPoint1, swVertex vPoint2)
{
    // This is the classic formula used in beginning algebra to return the
    // distance between 2 points.  Since it's 3D, we just add the z dimension:
    //
    // Distance = sqrt(  (P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2 )
    //
    double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
                            (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
                            (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

    // Return the distance between the 2 points
    return (float)distance;
}


////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns the point on the line vA_vB that is closest to the point vPoint
/////
////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

swVertex ClosestPointOnLine(swVertex vA, swVertex vB, swVertex vPoint)
{
    // Create the vector from end point vA to our point vPoint.
    swVertex vVector1 = vPoint - vA;

    // Create a normalized direction vector from end point vA to end point vB
    swVertex vVector2 = Normalize(vB - vA);

    // Use the distance formula to find the distance of the line segment (or magnitude)
    float d = Distance(vA, vB);

    // Using the dot product, we project the vVector1 onto the vector vVector2.
    // This essentially gives us the distance from our projected vector from vA.
    float t = Dot(vVector2, vVector1);

    // If our projected distance from vA, "t", is less than or equal to 0, it must
    // be closest to the end point vA.  We want to return this end point.
    if (t <= 0) 
        return vA;

    // If our projected distance from vA, "t", is greater than or equal to the magnitude
    // or distance of the line segment, it must be closest to the end point vB.  So, return vB.
    if (t >= d) 
        return vB;
 
    // Here we create a vector that is of length t and in the direction of vVector2
    swVertex vVector3 = vVector2 * t;

    // To find the closest point on the line segment, we just add vVector3 to the original
    // end point vA.
    swVertex vClosestPoint = vA + vVector3;

    // Return the closest point on the line segment
    return vClosestPoint;
}


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns true if our sphere collides with the polygon passed in
/////
////////////////////////////// SPHERE POLYGON COLLISION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool SpherePolygonCollision(swVertex vPolygon[],
                            swVertex &vCenter, int vertexCount, float radius)
{
    // This function is the only function we need to call for testing if a sphere
    // collides with a polygon.  The rest are just helper functions called within here.
    // The theory is actually quite difficult to understand, especially if you are
    // a beginner to collision detection and are following the tutorials in order, but
    // I will try to be as gentle and descriptive as possible.  Let go!
    // Basically, here is the overview:  
    //
    // 1) First you want to check if the sphere collides with the polygon's plane.
    //    Remember, that planes are infinite and you could be 500 units from the
    //    polygon and it's still going to trigger this first test.  We want to
    //    write a function that classifies the sphere.  Either it's completely
    //    in front of the plane (the side the normal is on), intersecting the
    //    plane or completely behind the plane.  Got it so far?  We created a
    //    function called ClassifySphere() that returns BEHIND, FRONT or INTERSECTS.
    //    If ClassifySphere() returns INTERSECTS, then we move on to step 2, otherwise
    //    we did not collide with the polygon.
    //
    // 2) The second step is to get an intersection point right in front of the sphere.
    //    This one of the tricky parts.  We know that once we have an intersection point
    //    on the plane of the polygon, we just need to use the InsidePolygon() function
    //    to see if that point is inside the dimensions of the polygon, just like we
    //    did with the Ray to Polygon Collision tutorial.  So, how do we get the point
    //    of intersection?  It's not as simple as it might sound.  Since a sphere infinite
    //    points, there would be a million points that it collided at.  You can't just
    //    draw a ray in the direction the sphere was moving because it could have just
    //    nicked the bottom of the polygon and your ray would find an intersection
    //    point that is outside of the polygon.  Well, it turns out that we need to
    //    first try and give it a shot.  We will try the first attempt a different way though.
    //    We know that we can find the normal vector of the polygon, which in essence
    //    tells us the direction that the polygon is facing.  From ClassifyPoly(),
    //    it also returns the distance the center our sphere is from the plane.  That
    //    means we have a distance our sphere center is from the plane, and the normal
    //    tells us the direction the plane is in.  If we multiply the normal by the
    //    distance from the plane we get an offset.  This offset can then be subtracted
    //    from the center of the sphere.  Believe it or not, but we now have a position
    //    on the plane in the direction of the plane.  Usually, this intersection points
    //    works fine, but if we get around the edges of the polygon, this does not work.
    //    What we just did is also called "projecting the center of the sphere onto the plane".
    //    Another way to do this is to shoot out a ray from the center of the sphere in
    //    the opposite direction of the normal, then we find the intersection of that line
    //    and the plane.  My way just takes 3 multiplies and a subtraction.  You choose.
    //
    // 3) Once we have our psuedo intersection point, we just pass it into InsidePolygon(),
    //    along with the polygon vertices and the swVertex count.  This will then return
    //    true if the intersection point was inside of the polygon, otherwise false.
    //    Remember, just because this returns false doesn't mean we stop there!  If
    //    we didn't collide yet, we need to skip to step 4.
    //
    // 4) If we get here, it's assumed that we tried our intersection point and it
    //    wasn't in the polygon's perimeter.  No fear!  There is hope!  If we get to step
    //    4, that's means that our center point is outside of the polygon's perimeter. Since
    //    we are dealing with a sphere, we could still be colliding because of the sphere's radius.
    //    This last check requires us to find the point on each of the polygon's edges that
    //    is closest to the sphere's center.  We have a tutorial on finding this, so make sure
    //    you have read it or are comfortable with the concept.  If we are dealing with a
    //    triangle, we go through every side and get an edge vector, and calculate the closest
    //    point on those lines to our sphere's center.  After getting each closest point, we
    //    calculate the distance that point is from our sphere center.  If the distance is
    //    less than the radius of the sphere, there was a collision.  This way is pretty fast.
    //    You don't need to calculate all three sides evey time, since the first closest point's
    //    distance could be less than the radius and you return "true".
    //
    // That's the overview, *phew!*.  I bet you are reading this just wanting to cry because
    // that seems like so much math and theory to digest, so the code must be atrocious!
    // Well, you are partially right :)  It's not that bad actually, quite straight forward.
    // I will label the steps in the code so you can go back and forth to the overview and code.
    // I might mention that by having our CVector3 class operator overloaded it cuts down the
    // code tremendously.  If you are confused with this concept of C++, just create functions
    // to add, subtract and multiply vectors or scalars together.
    //

    // 1) STEP ONE - Finding the sphere's classification

    // Let's use our Normal() function to return us the normal to this polygon
    swVertex vNormal = Normal(vPolygon);

    // This will store the distance our sphere is from the plane
    float distance = 0.0f;

    // This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the plane
    // of the polygon.  We pass is our sphere center, the polygon's normal, a point on
    // the plane (swVertex), the sphere's radius and an empty float to fill the distance with.
    int classification = ClassifySphere(vCenter, vNormal, vPolygon[0], radius, distance);

    // If the sphere intersects the polygon's plane, then we need to check further,
    // otherwise the sphere did NOT intersect the polygon.  Pretty fast so far huh?
    if(classification == INTERSECTS)
    {
        // 2) STEP TWO - Finding the psuedo intersection point on the plane

        // Now we want to project the sphere's center onto the polygon's plane,
        // in the direction of the normal.  This is done by multiplying the "normal"
        // by the "distance" the sphere center is from the plane.  We got the distance
        // from the ClassifySphere() function call up above.  2 return values were given
        // through the "distance" variable being passed in as a reference.  If projecting
        // is confusing to you, just think of it as this: "I am starting at the center
        // of the sphere and I am going to just run into the plane.  I will move in the
        // direction that is reverse from the normal.  When do I know when to stop?  Well,
        // I just go in that direction until my distance from the center is the same as
        // the distance the center of the sphere is from the plane."  By doing this
        // we get an offset to subtract from the center of the sphere.
        swVertex vOffset = vNormal * distance;

        // Once we have the offset to the plane, we just subtract it from the center
        // of the sphere.  "vPosition" now a point that lies on the plane of the polygon.
        // Whether it is inside the polygon's perimeter is another story.  Usually it
        // is though, unless we get near the edges of the polygon.
        swVertex vPosition = vCenter - vOffset;

        // 3) STEP THREE - Check if the intersection point is inside the polygons perimeter

        // This is the same function used in our previous tutorial on Ray to Polygon Collision.
        // If the intersection point is inside the perimeter of the polygon, it returns true.
        // We pass in the intersection point, the list of vertices and swVertex count of the poly.
        if(InsidePolygon(vPosition, vPolygon, vertexCount))
            return true;    // We collided!
        else
        {
            // 4) STEP FOUR - Check the sphere to see if it intersects the polygon edges

            // If we get here, we didn't find an intersection point in the perimeter.
            // There is still one more chance to redeem our sphere that it can hit the mark.
            // If any part of the sphere intersects the edges of the polygon, we collided.
            // This is only checked if the sphere's center point is outside the edges of the
            // polygon. We pass in the center of the sphere, the list of verts, the polygon
            // swVertex count and the sphere's radius.  If this returns true we have a collision.
            if(EdgeSphereCollision(vCenter, vPolygon, vertexCount, radius))
            {
                return true;    // We collided! "And you doubted me..." - Sphere
            }
        }
    }

    // If we get here, there is obviously no collision happening up in this crib
    return false;
}


///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This tells if a sphere is BEHIND, in FRONT, or INTERSECTS a plane, also it's distance
/////
///////////////////////////////// CLASSIFY SPHERE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

int ClassifySphere(swVertex &vCenter,
                   swVertex &vNormal, swVertex &vPoint, float radius, float &distance)
{
    // First we need to find the distance our polygon plane is from the origin.
    // We need this for the distance formula below.
    float d = (float)PlaneDistance(vNormal, vPoint);

    // Here we use the famous distance formula to find the distance the center point
    // of the sphere is from the polygon's plane.
    // Remember that the formula is Ax + By + Cz + d = 0 with ABC = Normal, XYZ = Point
    distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

    // Now we query the information just gathered.  Here is how Sphere Plane Collision works:
    // If the distance the center is from the plane is less than the radius of the sphere,
    // we know that it must be intersecting the plane.  We take the absolute value of the
    // distance when we do this check because once the center of the sphere goes behind
    // the polygon, the distance turns into negative numbers (with 0 being that the center
    // is exactly on the plane).  What do I mean when I say "behind" the polygon?  How do
    // we know which side is the front or back side?  Well, the side with the normal pointing
    // out from it is the front side, the other side is the back side.  This is all dependant
    // on the direction the vertices stored.  I recommend drawing them counter-clockwise.
    // if you go clockwise the normal with then point the opposite way and will screw up
    // everything.
    // So, if we want to find if the sphere is in front of the plane, we just make sure
    // the distance is greater than or equal to the radius.  let's say we have a radius
    // of 5, and the distance the center is from the plane is 6; it's obvious that the
    // sphere is 1 unit away from the plane.
    // If the sphere isn't intersecting or in front of the plane, it HAS to be BEHIND it.

    // If the absolute value of the distance we just found is less than the radius,
    // the sphere intersected the plane.
    if(valAbs(distance) < radius)
        return INTERSECTS;
    // Else, if the distance is greater than or equal to the radius, the sphere is
    // completely in FRONT of the plane.
    else if(distance >= radius)
        return FRONT;

    // If the sphere isn't intersecting or in FRONT of the plane, it must be BEHIND
    return BEHIND;
}


///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////   This returns true if the sphere is intersecting any of the edges of the polygon
/////
///////////////////////////////// EDGE SPHERE COLLSIION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool EdgeSphereCollision(swVertex &vCenter,
                         swVertex vPolygon[], int vertexCount, float radius)
{
    swVertex vPoint;

    // This function takes in the sphere's center, the polygon's vertices, the swVertex count
    // and the radius of the sphere.  We will return true from this function if the sphere
    // is intersecting any of the edges of the polygon.  How it works is, every edge line
    // segment finds the closest point on that line to the center of the sphere.  If the
    // distance from that closest point is less than the radius of the sphere, there was
    // a collision.  Otherwise, we are definately out of reach of the polygon.  This works
    // for triangles, quads, and any other convex polygons.

    // Go through all of the vertices in the polygon
    for(int i = 0; i < vertexCount; i++)
    {
        // This returns the closest point on the current edge to the center of the sphere.
        // Notice that we mod the second point of the edge by our swVertex count.  This is
        // so that when we get to the last edge of the polygon, the second swVertex of the
        // edge is the first swVertex that we starting with.
        vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);

        // Now, we want to calculate the distance between the closest point and the center
        float distance = Distance(vPoint, vCenter);

        // If the distance is less than the radius, there must be a collision so return true
        if(distance < radius)
            return true;
    }

    // The was no intersection of the sphere and the edges of the polygon
    return false;
}

swVertex Vector(swVertex vPoint1, swVertex vPoint2)
{
    swVertex vVector(0,0,0);                             // Initialize our variable to zero

    // In order to get a vector from 2 points (a direction) we need to
    // subtract the second point from the first point.

    vVector.x = vPoint1.x - vPoint2.x;                  // Get the X value of our new vector
    vVector.y = vPoint1.y - vPoint2.y;                  // Get the Y value of our new vector
    vVector.z = vPoint1.z - vPoint2.z;                  // Get the Z value of our new vector

    return vVector;                                     // Return our new vector
}


swVertex GetCollisionOffset(swVertex &vNormal, float radius, float distance)
{
  swVertex vOffset=swVertex(0,0,0);
  if(distance>0)
    {
      float distanceOver=radius-distance;
      vOffset=vNormal*distanceOver;
    }
  else
    {
     float distanceOver=radius+distance;
     vOffset=vNormal* -distanceOver;
    }
  return vOffset;
}
