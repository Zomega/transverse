class Edge {
	
	Point getStart()
	UnitVector2D getStartTangent

	Point getEnd()
	UnitVector2D getEndTangent // Note: Reversed from actual tangent.

	Point getPosition( float t )

	BBox2D getBBox()

	Edge applyTransform( RTransform2D transform )

	Edge subEdge( float t_s, float t_e )

}

class LinearEdge ...

class CubicEdge ...

