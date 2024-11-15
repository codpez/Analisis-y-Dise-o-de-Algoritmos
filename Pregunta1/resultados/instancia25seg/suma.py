import os

# Directorio de los archivos de salida
output_dir = "./"  # Cambia si los archivos están en otra carpeta
output_prefix = "prueba"
num_files = 10  # Número de archivos a procesar

# Lista para almacenar los tiempos extraídos
execution_times = []

# Procesar cada archivo de salida
for i in range(1, num_files + 1):
    output_file = os.path.join(output_dir, f"{output_prefix}{i}.txt")
    
    if os.path.isfile(output_file):
        try:
            with open(output_file, 'r') as file:
                lines = file.readlines()
                # Buscar el tiempo en la última línea
                last_line = lines[-1].strip()
                if "microsegundos" in last_line:
                    # Extraer el número antes de "microsegundos"
                    time_microseconds = int(last_line.split()[-2])
                    execution_times.append((output_file, time_microseconds))
                    print(f"Archivo: {output_file} -> Tiempo: {time_microseconds} microsegundos")
                else:
                    print(f"No se encontró tiempo en: {output_file}")
        except Exception as e:
            print(f"Error al procesar {output_file}: {e}")
    else:
        print(f"Archivo no encontrado: {output_file}")

# Mostrar los tiempos procesados
print("\nTiempos de ejecución procesados:")
for file, time in execution_times:
    print(f"{file}: {time} microsegundos")
