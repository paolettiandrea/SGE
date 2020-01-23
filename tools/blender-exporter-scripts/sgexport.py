import bpy

# This is a script for blender that exports every mesh in a .blend file as a format readable for the SGE game engine

TRIANGLE_MESH_EXTENSION = "smesh"
SIMPLE_PATH_EXTENSION = "spath"


def look_for_vert_occurrence(target_vert_index, edges, exclude_edge_index=-1):
    index = 0
    for edge in edges:
        if ((edge[0]==target_vert_index or edge[1]==target_vert_index) and index!=exclude_edge_index):
            return index
        index += 1
    return -1


def make_ordered_path(edges,vertices):
    ordered_path = []
    already_inverted_flag = False
    loop_detected = False
    target_vertex_index = edges[0][0]
    target_edge_index = 0

    while (len(ordered_path)<len(vertices)):
        ordered_path.append(vertices[target_vertex_index])
        # Find the other edge this vertex is part of
        next_edge_index = look_for_vert_occurrence(target_vertex_index, edges, target_edge_index)
        if (next_edge_index==-1):
            # We are on a terminal vertex
            if (already_inverted_flag):
                # If this was an open path it should be exausted
                break
            else:
                # We need to walk the path from where we started in the other direction
                target_edge_index = 0
                target_vertex_index = edges[0][1]
                ordered_path.reverse()
                already_inverted_flag = True
                continue
        else:
            # There is a next edge, we need to check that we're not going to loop
            target_edge_index = next_edge_index
            if target_edge_index == 0:
                # We're back considering the initial edge, so
                ordered_path.append(ordered_path[0])
                loop_detected = True
                #print("Detected looping")
                break
            else:
                # This is legit, so we just need to set the vertex target to the correct value of the tuple
                target_edge = edges[target_edge_index]
                if (target_edge[0] == target_vertex_index):
                    target_vertex_index = target_edge[1]
                else:
                    target_vertex_index = target_edge[0]

    if ((len(ordered_path) == len(vertices)) and (loop_detected==False)) or ((len(ordered_path) == len(vertices)+1) and (loop_detected== True)):
        #print("The path seems to be correctly formed: Verts:{} | Looping:{}".format(len(ordered_path),loop_detected))
        return ordered_path
    else:
        print("The path doesn't seem to be correctly formed: Verts:{} | Looping:{}".format(len(ordered_path),loop_detected))
        return -1

def export_simple_path(object, export_file_path):
    edges = []
    for edge in object.edges:
        edges.append( (edge.vertices[0], edge.vertices[1]) )

    vertices = []
    for vert in object.vertices:
        vertices.append( (vert.co.x,vert.co.y) )

    #print("EXPORTING SIMPLE PATH FROM ACTIVE OBJECT: {} | Verts:{} | Edges:{} |".format(object.name,len(vertices),len(edges)))

    ordered_path = make_ordered_path(edges, vertices)

    if ordered_path==-1:
        print("Error: the path wasn't simple")
    else:
        file = open(export_file_path, 'w')
        for vert in ordered_path:
            file.write("{0} {1}\n".format(vert[0],vert[1]))
        file.close()
        #print("Ordered path successfully exported to: {} \n".format(export_file_path))






# Get the dir path of the opened blend file
dir_path = bpy.path.abspath("//")
file_name = bpy.path.basename(bpy.context.blend_data.filepath)[:-6]     # without extension

# For every mesh in the blend file, export it in a separate file in the same dir of the original
for object in bpy.data.meshes:
    if len(object.polygons)>0:
        # The object has faces, it must be exported as a triangle mesh
        print("Exporting object [" + object.name + "] as a triangle mesh")
        export_file = open(dir_path + file_name + "__" + object.name + "." + TRIANGLE_MESH_EXTENSION, "w")
        # Write in the export file a line for every vertex of this mesh
        for vertex in object.vertices:
            export_file.write(str(vertex.co.x) + " " + str(vertex.co.y) + "\n")
        export_file.write("\n")
        # For every face in the mesh write in the export file a line with the indices to the right vertices
        for face in object.polygons:
            vert_counter = 0
            for vert_index in face.vertices:
                export_file.write(str(vert_index))
                vert_counter += 1
                if (vert_counter<3):
                    export_file.write(" ")
                else:
                    if vert_counter>3:
                        print("WARNING: found a face with more than 3 vertices, only triangle meshes are supported")
                        exit(1)

            export_file.write("\n")
        export_file.close()
    else:
        # The object has no faces, it must be exported as a simple path
        print("Exporting object [" + object.name + "] as a simple path")
        export_simple_path(object, dir_path + file_name + "__" + object.name + "." + SIMPLE_PATH_EXTENSION)



