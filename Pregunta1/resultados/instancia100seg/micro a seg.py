import os

# Directorio de los archivos de salida
output_dir = "./"  # Cambia si los archivos están en otra carpeta
output_prefix = "prueba"
num_files = 10  # Número de archivos a procesar

# Procesar cada archivo de salida
for i in range(1, num_files + 1):
    output_file = os.path.join(output_dir, f"{output_prefix}{i}.txt")
    
    if os.path.isfile(output_file):
        try:
            with open(output_file, 'r') as file_reader:
                lines = file_reader.readlines()
                
            # Buscar el tiempo en microsegundos en la última línea y convertirlo a segundos
            last_line = lines[-1].strip()
            if "microsegundos" in last_line:
                # Extraer el número antes de "microsegundos"
                time_microseconds = int(last_line.split()[-2])
                # Convertir a segundos
                time_seconds = time_microseconds / 1_000_000
                # Reemplazar la línea con el valor en segundos
                lines[-1] = f"{time_seconds:.6f} segundos\n"  # 6 decimales para precisión

                # Escribir el cambio en el archivo
                with open(output_file, 'w') as file_writer:
                    file_writer.writelines(lines)
                
                print(f"{output_file}: Tiempo convertido a {time_seconds:.6f} segundos")
            else:
                print(f"No se encontró tiempo en: {output_file}")
                
        except Exception as e:
            print(f"Error al procesar {output_file}: {e}")
    else:
        print(f"Archivo no encontrado: {output_file}")

print("\nProceso completado.")
