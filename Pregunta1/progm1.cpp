#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <ctime>
#include <chrono>
using punto = std::pair<int, int>;
using segmento = std::tuple<punto, punto>;

std::vector<segmento> extraerDatos(int n) {
    std::vector<segmento> segmentos;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        if (!(std::cin >> x1 >> y1 >> x2 >> y2)) {
            std::cerr << "Error al leer los puntos del segmento " << i + 1 << std::endl;
            exit(1);
        }
        segmentos.push_back(std::make_tuple(punto(x1, y1), punto(x2, y2)));
    }
    return segmentos;
}

int orientacion(punto p, punto q, punto r) {
    return (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
}

bool esColinear(punto a1, punto b1, punto a2, punto b2) {
    return orientacion(a1, b1, a2) == 0 && 
           a2.first <= std::max(a1.first, b1.first) && a2.first >= std::min(a1.first, b1.first) &&
           a2.second <= std::max(a1.second, b1.second) && a2.second >= std::min(a1.second, b1.second);
}

bool seIntersecta(punto a1, punto b1, punto a2, punto b2) {
    int d1 = orientacion(a1, b1, a2);
    int d2 = orientacion(a1, b1, b2);
    int d3 = orientacion(a2, b2, a1);
    int d4 = orientacion(a2, b2, b1);

    return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) ||
           esColinear(a1, b1, a2, b2) || esColinear(a2, b2, a1, b1);
}

punto calcularPuntoInterseccion(punto a1, punto b1, punto a2, punto b2) {
    int A1 = b1.second - a1.second;
    int B1 = a1.first - b1.first;
    int C1 = A1 * a1.first + B1 * a1.second;

    int A2 = b2.second - a2.second;
    int B2 = a2.first - b2.first;
    int C2 = A2 * a2.first + B2 * a2.second;

    int det = A1 * B2 - A2 * B1;
    if (det == 0) return {-1, -1}; // En caso de que no haya intersección

    int x = (B2 * C1 - B1 * C2) / det;
    int y = (A1 * C2 - A2 * C1) / det;
    return punto(x, y);
}

std::vector<punto> manejoDatosEinterseccion(const std::vector<segmento>& segmentos) {
    std::vector<punto> resultado;
    std::set<punto> interseccionesUnicas;

    for (size_t i = 0; i < segmentos.size(); i++) {
        for (size_t j = i + 1; j < segmentos.size(); j++) {
            const auto& a1 = std::get<0>(segmentos[i]);
            const auto& b1 = std::get<1>(segmentos[i]);
            const auto& a2 = std::get<0>(segmentos[j]);
            const auto& b2 = std::get<1>(segmentos[j]);

            if (seIntersecta(a1, b1, a2, b2)) {
                punto interseccion = calcularPuntoInterseccion(a1, b1, a2, b2);
                if (interseccion.first != -1 && interseccion.second != -1) {
                    if (interseccionesUnicas.insert(interseccion).second) {
                        resultado.push_back(interseccion);
                    }
                }
            }
        }
    }
    return resultado;
}

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Numero de segmentos invalido o error de entrada." << std::endl;
        return 1;
    }
    auto inicio = std::chrono::high_resolution_clock::now();
    std::vector<segmento> segmentos = extraerDatos(n);
    std::vector<punto> resultado = manejoDatosEinterseccion(segmentos);

    std::cout << "Numero de intersecciones encontradas: " << resultado.size() << std::endl;
    for (const auto& interseccion : resultado) {
        std::cout << "Interseccion en: " << interseccion.first << " " << interseccion.second << std::endl;
    }
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count();
    std::cout << "Tiempo de ejecucion: " << duracion << " microsegundos" << std::endl;
    return 0;
}
