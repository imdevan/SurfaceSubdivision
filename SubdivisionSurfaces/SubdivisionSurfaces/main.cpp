/* 

  Devan Huapaya
  CSCE 462 - Assignment 6

  Assignment Procedure:

  - Read in obj file with quadrilateral mesh.

	example: f i1 i2 i3 i4

  - When the users presses the '+' key, subdivide the surface.
  - - First, perform linear subdivision on the shape and then averaging.
  - If the users presses the 'L' key -> linearly subdivide.
  - If the users presses the 'A' key -> perform averaging on the surface.
  - '+' is the combination of 'L' followed by 'A'

  - User should be able to zoom by dragging the right mouse button up and down.
  - User should be able to rotate the shape horizontally and vertically 
    by dragging the left mouse button.
  
  - Object should be lit by at least one light.
  - - This means calculating normals of the faces (Flat shading should be used).
  
  - Use OpenGL to do all of the following:
  - - Rendering
  - - Lighting
  - - Hidden Surface Removal
  
 */