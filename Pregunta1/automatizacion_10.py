import os
import subprocess

# Obtener la ruta base del script actual
base_dir = os.path.dirname(os.path.abspath(__file__))

# Directorio de los archivos de prueba y prefijo de salida
input_dir = os.path.join(base_dir, "archivosDePrueba", "inciso_c","25seg")
output_prefix = "prueba"
program = os.path.join(base_dir, "progm1.exe")

# Ejecutar el programa 10 veces
for i in range(1, 11):
    # Generar los nombres de archivo con el número sin ceros a la izquierda
    input_file = os.path.join(input_dir, f"25seg{i}.txt")
    output_file = os.path.join(base_dir,"resultados","instancia25seg", f"{output_prefix}{i}.txt")
    
    # Verificar que el archivo de entrada existe
    if os.path.isfile(input_file):
        # Ejecutar el programa con redirección de entrada y salida
        with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
            subprocess.run([program], stdin=infile, stdout=outfile)
        print(f"Ejecucion {i} completada: {input_file} -> {output_file}")
    else:
        print(f"Archivo de entrada {input_file} no encontrado, omitiendo.")
