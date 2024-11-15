import os

# Directorio de los archivos de salida
output_dir = "./"  # Cambia si los archivos están en otra carpeta
output_prefix = "prueba"
num_files = 10  # Número de archivos a procesar

# Lista para almacenar los tiempos extraídos
execution_times = []
non_zero_times = []

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
                    if time_microseconds > 0:
                        non_zero_times.append(time_microseconds)
                    print(f"Archivo: {output_file} -> Tiempo: {time_microseconds} microsegundos")
                else:
                    print(f"No se encontró tiempo en: {output_file}")
        except Exception as e:
            print(f"Error al procesar {output_file}: {e}")
    else:
        print(f"Archivo no encontrado: {output_file}")

# Calcular el promedio de tiempos no nulos y redondearlo
if non_zero_times:
    average_time = round(sum(non_zero_times) / len(non_zero_times))
else:
    average_time = 0

# Reemplazar tiempos 0 con el promedio calculado directamente en los archivos
print("\nRellenando archivos con tiempos 0...")
for file, time in execution_times:
    if time == 0:
        try:
            with open(file, 'r') as file_reader:
                lines = file_reader.readlines()
            
            # Modificar la última línea con el promedio calculado
            if "microsegundos" in lines[-1]:
                lines[-1] = f"{average_time} microsegundos\n"
            
            with open(file, 'w') as file_writer:
                file_writer.writelines(lines)
            
            print(f"{file}: Rellenado con {average_time} microsegundos")
        except Exception as e:
            print(f"Error al modificar {file}: {e}")
    else:
        print(f"{file}: Sin cambios")

print("\nProceso completado.")
