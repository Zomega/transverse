#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef int Shape; // TODO: Composed of a closed path. Should complain if that path crosses itself (other weird topologies are fine)
                   // Should import / export SVG / DXF

typedef double Distance; // TODO: Units, and possible infty value

typedef int Vector3D; // Has Units
typedef int Point3D; // Has Units, transforms differently.

typedef int RigidTransform3D;

typedef int UnitVector3D; // Unitless, provides a direction only.

struct Plane3D {
    UnitVector3D normal;
    Distance offset;

    Plane3D( UnitVector3D normal, Distance offset )
    : normal( normal ), offset( offset )
    {}
};

typedef int Line3D; // Tangent / pint form

typedef int BBox;

struct Slab {
  Plane3D center;
  Distance thickness;
  
  Slab(Plane3D center, Distance thickness)
  : center( center ), thickness( thickness )
  {}

  Plane3D topPlane3D() const {
    return Plane3D( center.normal, center.offset + ( this->thickness / 2 ) );
  }

  Plane3D bottomPlane3D() const {
    return Plane3D( center.normal, center.offset - ( this->thickness / 2 ) );
  }
  // TODO bottom_Plane3D
};

class Component {
    public:
    virtual Shape crossSection( Plane3D Plane3D ) const = 0;
    virtual Shape crossSlab( Slab slab ) const = 0;
    virtual BBox  boundingBox() const = 0; // TODO: Axis for reference
};

class SlabComponent : public Component {
    public:
    
    SlabComponent ( Slab slab, Shape shape  )
    : m_slab ( slab ), m_shape ( shape )
    {}

    Shape crossSection( Plane3D Plane3D ) const {
        return 0;
    }

    Shape crossSlab( Slab slab ) const {
        return 0;
    }

    Shape boundingBox() const {
        return 0;
    }
    
    private:
    Slab m_slab;
    Shape m_shape;
};

main()
{
    Plane3D testPlane3D = Plane3D( 0, 0 );
    Slab testSlab = Slab( testPlane3D, 1.0 );
    Component* x = new SlabComponent( testSlab, 0 );

    cout << x->crossSlab( testSlab ) << endl;

    string SS;     // C++ STL string
    string SS2;    // C++ STL string
    
    SS = "This is a string";
    SS2 = SS;
    
    cout << SS << endl;
    cout << SS2 << endl;
    
    printf("Hello AskUbuntu!\n");
    
    // constructors used in the same order as described above:
    vector<int> first;                                // empty vector of ints
    vector<int> second (4,100);                       // four ints with value 100
    vector<int> third (second.begin(),second.end());  // iterating through second
    vector<int> fourth (third);                       // a copy of third
    
    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
    
    cout << "The contents of fifth are:";
    for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    cout << ' ' << *it;
    cout << '\n';
    
    return 0;
}
