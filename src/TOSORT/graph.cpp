// Contains tha magic sauce to pull a diagram together.

struct AugEdge {
	Edge edge;
	Vertex* start;
	Vertex* end;
	Region* left;
	Region* right;
}

class Vertex {
	Point point;
	SkipRing<AugEdge> edges; // Pair?? include if ingoing or outgoing?
}

class Region {
	RLabel label;
	LinkedRing<AugEdge> border;
}

class RGraph {
	Set<AugEdge> edges
	Set<Vertex> vertecies
	Set<Region> regions
}

bool verify( RGraph graph ) {
	// Ensure no NULL pointers anwhere
		// Edges
		// Vertexes
		// Regions
	// Ensure no edges intersect (except at points).
	// Ensure each Edge ends where it says it does

	// Ensure each edge seperates two different labels.
	
	// At each vertex, verify that each consecutive pair has the same region between them.

	// Verify that each region has a valid surrounding ring.
}

RGraph convertShape( Shape shape );

Shape exportRGraph( RGraph regions, Predicate blah );
