class Section:
	def __init__( self, material, plane, shape ):
		self.material = material
		self.front_plane = plane
		self.shape = shape

	@property
	def thickness( self ):
		return self.material.thickness

	@property
	def back_plane( self ):
		pass #TODO

	@property
	def mid_plane( self ):
		pass #TODO

	
