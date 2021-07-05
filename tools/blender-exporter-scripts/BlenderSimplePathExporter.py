import bpy;

# SCRIPT FOR BLENDER ONLY: allows for the registration in Blender of an operator that exports the data of a "Simple Path" into a file
# Simple Path means a list of points representing a path where one point is connected only to the next and to the previous point in the list.
# The path can be closed, that is represented in the output with an "*" in the last line of the file

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
                print("Detected looping")
                break
            else:
                # This is legit, so we just need to set the vertex target to the correct value of the tuple
                target_edge = edges[target_edge_index]
                if (target_edge[0] == target_vertex_index):
                    target_vertex_index = target_edge[1]
                else:
                    target_vertex_index = target_edge[0]
                    
    if ((len(ordered_path) == len(vertices)) and (loop_detected==False)) or ((len(ordered_path) == len(vertices)+1) and (loop_detected== True)):
        print("The path seems to be correctly formed: Verts:{} | Looping:{}".format(len(ordered_path),loop_detected))
        return ordered_path
    else:
        print("Returning -1")
        return -1
    
def export_ordered_path_from_active_object(filepath):
    m=bpy.context.mode
    if bpy.context.mode!='OBJECT':
        bpy.ops.object.mode_set(mode='OBJECT')
    obj = bpy.context.active_object

    edges = []
    for edge in obj.data.edges:
        edges.append( (edge.vertices[0], edge.vertices[1]) )
        
    vertices = []
    for vert in obj.data.vertices:
        vertices.append( (vert.co.x,vert.co.y) )
        
    print("EXPORTING SIMPLE PATH FROM ACTIVE OBJECT: {} | Verts:{} | Edges:{} |".format(obj.name,len(vertices),len(edges)))
             
    ordered_path = make_ordered_path(edges, vertices)
    
    if (ordered_path==-1):
        print("Error: the path wasn't simple")
    else:
        file = open(filepath, 'w')
        for vert in ordered_path:
            file.write("{0}\n{1}\n\n".format(vert[0],vert[1]))
        file.close()
        print("Ordered path successfully exported to: {} \n".format(filepath))




class ExportSomeData(bpy.types.Operator):
    bl_idname = "export.simple_path"
    bl_label = "Export Simple Path"

    filepath = bpy.props.StringProperty(subtype="FILE_PATH")

    @classmethod
    def poll(cls, context):
        return context.object is not None

    def execute(self, context):
        export_ordered_path_from_active_object(self.filepath)
        return {'FINISHED'}

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}


# Only needed if you want to add into a dynamic menu
def menu_func(self, context):
    self.layout.operator_context = 'INVOKE_DEFAULT'
    self.layout.operator(ExportSomeData.bl_idname, text="Text Export Operator")

# Register and add to the file selector
bpy.utils.register_class(ExportSomeData)
bpy.types.INFO_MT_file_export.append(menu_func)
