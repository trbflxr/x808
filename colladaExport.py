import bpy
import math
import os

#######################################
## Export Settings
#######################################
export_selected = False


#######################################
## File Paths
#######################################

base_filename = bpy.path.basename(bpy.context.blend_data.filepath).replace(".blend","").replace(".blend","")
base_directory = base_filename + '\\'

if not os.path.exists(base_directory):
    os.makedirs(base_directory)

dae_filename = base_filename + '.dae'
dae_path = base_directory + dae_filename

physics_filename = base_filename + '.physics'
physics_path = base_directory + physics_filename 

lights_filename = base_filename + '.lights'
lights_path = base_directory + lights_filename 


#######################################
## Export Collada File
#######################################
print("")
print("")

bpy.ops.wm.collada_export(filepath=dae_path)


#######################################
## Export Lights
#######################################
print("")
print("")
print("Lights Export: " + lights_path)


lights_file = open(lights_path, 'w')
numL = 0


for item in bpy.data.objects:
    if(item.type == 'LAMP'):
        lamp = item.data
        if(lamp.type == 'SPOT' or lamp.type == 'POINT'):
            numL = numL + 1
        # border
            border = "== == ==" + '\n'
            lights_file.write(border)
        # name
            name = "nam " + lamp.name + '\n'
            lights_file.write(name)
        # type
            shape = "typ " + str(lamp.type) + '\n'
            lights_file.write(shape)
        #intensity
            intensity = "ity " + str(lamp.energy) + '\n'
            lights_file.write(intensity)
        #color
            color = "col " + str(lamp.color.r) + " " + str(lamp.color.g) + " " + str(lamp.color.b) + '\n'
            lights_file.write(color)
        #falloff
            falloff = "fal " + str(lamp.distance) + '\n'
            lights_file.write(falloff)
        #spot_angle and spot_blur
            spot_angle = "ang 0" + '\n'
            spot_blur = "blr 0" + '\n'
            if (lamp.type == 'SPOT'):
                spot_angle = "ang " + str(lamp.spot_size) + '\n'
                spot_blur = "blr " + str(lamp.spot_blend) + '\n'
            lights_file.write(spot_angle)
            lights_file.write(spot_blur)
        #shadow
            shadow_method = str(lamp.shadow_method)
            has_shadow = 0
            if (not(shadow_method == 'NOSHADOW')):
                has_shadow = 1
            shadow = "sha " + str(has_shadow) + '\n'
            lights_file.write(shadow)
            
            lights_file.write('\n')

numL_string = "num " + str(numL)
lights_file.write(numL_string)

print("Info: Exported " + str(numL) + " Lights")
