#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Estructura para representar un movimiento
struct Movimiento {
    string tipo;
    string nombre;
    string actividad;
};

// Estructura para representar un plazo fijo
struct PlazoFijo {
    float monto = 0;
    int dias = 0;
    float interes = 0;
};

// Estructura para representar una cuenta bancaria
struct Cuenta {
    string nombre = "admin";
    string contrasenia = "admin";
    float saldo = 0;
    float dolares = 0;
    vector<Movimiento> movimientos;
    vector<PlazoFijo> plazos_fijos;
};

// Función para mostrar el menú principal
void menu_principal(Cuenta usuario) {
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nombre << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo << endl;
    cout << "Dólares: USD$ " << usuario.dolares << endl;
    cout << "Plazos fijos armados: " << usuario.plazos_fijos.size() << endl;
    cout << endl;
    cout << "1 - Ingresar efectivo." << endl;
    cout << "2 - Retirar efectivo." << endl;
    cout << "3 - Comprar y/o vender dólares." << endl;
    cout << "4 - Retirar dólares." << endl;
    cout << "5 - Armar plazo fijo." << endl;
    cout << "6 - Cancelar plazo fijo." << endl;
    cout << "7 - Pedir préstamo." << endl;
    cout << "8 - Ver movimientos." << endl;
    cout << "9 - Actualizar datos." << endl;
    cout << "10 - Salir del sistema." << endl;
    cout << endl;
    cout << "Elegir una opción del menú: ";
}

// Función para registrar un nuevo usuario
void registrar_usuario() {
    string nombre, contrasenia;
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese su contraseña: ";
    cin >> contrasenia;

    // Guardar los datos en un archivo
    ofstream archivo("usuarios.txt", ios::app); // Abrir el archivo en modo de adición
    if (archivo.is_open()) {
        archivo << nombre << " " << contrasenia << endl;
        archivo.close();
        cout << "Usuario registrado con éxito." << endl;
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

// Función para validar los datos de acceso
bool validar_usuario(Cuenta &usuario) {
    string nombre, contrasenia;
    cout << "Ingrese su nombre de usuar"// Función para comprar o vender dólares

// Función para ingresar efectivo en la cuenta
void ingresar_efectivo(Cuenta &usuario) {
    float monto;
    cout << "Ingrese el monto en pesos que desea depositar en su cuenta: ";
    cin >> monto;

    if (monto > 0) {
        usuario.saldo += monto;
        cout << "El monto de $" << monto << " ha sido ingresado correctamente a su cuenta." << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Deposito de efectivo: $" << monto << ", Nuevo saldo: $" << usuario.saldo << endl;
            archivo.close();
            cout << "El movimiento ha sido registrado en movimientos.txt." << endl;
        } else {
            cout << "No se pudo abrir el archivo para registrar el movimiento." << endl;
        }

        Movimiento nuevo_movimiento = {"Deposito", usuario.nombre, "Ingreso de efectivo"};
        usuario.movimientos.push_back(nuevo_movimiento);
    } else {
        cout << "El monto ingresado no es válido. Intente nuevamente con un monto positivo." << endl;
    }
}

// Función para retirar efectivo de la cuenta
void retirar_efectivo(Cuenta &usuario) {
    float monto;
    cout << "Ingrese el monto que desea retirar (múltiplo de 100): ";
    cin >> monto;

    if (static_cast<int>(monto) % 100 != 0) {
        cout << "El monto ingresado no es múltiplo de 100. Intente nuevamente." << endl;
        return;
    }

    if (monto > usuario.saldo) {
        cout << "Fondos insuficientes. Su saldo actual es de $" << usuario.saldo << "." << endl;
        return;
    }

    int billetes_1000 = monto / 1000;
    monto -= billetes_1000 * 1000;

    int billetes_500 = monto / 500;
    monto -= billetes_500 * 500;

    int billetes_200 = monto / 200;
    monto -= billetes_200 * 200;

    int billetes_100 = monto / 100;
    monto -= billetes_100 * 100;

    float total_retirado = (billetes_1000 * 1000) + (billetes_500 * 500) + (billetes_200 * 200) + (billetes_100 * 100);

    usuario.saldo -= total_retirado;

    // Mostrar el desglose de billetes
    cout << "Retiro exitoso. Se entregaron:" << endl;
    if (billetes_1000 > 0) cout << billetes_1000 << " billetes de $1000" << endl;
    if (billetes_500 > 0) cout << billetes_500 << " billetes de $500" << endl;
    if (billetes_200 > 0) cout << billetes_200 << " billetes de $200" << endl;
    if (billetes_100 > 0) cout << billetes_100 << " billetes de $100" << endl;

    // Registrar el movimiento en un archivo de texto
    ofstream archivo("movimientos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Retiro de efectivo: $" << total_retirado << ", Nuevo saldo: $" << usuario.saldo << endl;
        archivo.close();
        cout << "El movimiento ha sido registrado en movimientos.txt." << endl;
    } else {
        cout << "No se pudo abrir el archivo para registrar el movimiento." << endl;
    }

    // Agregar el movimiento al vector de movimientos
    Movimiento nuevo_movimiento = {"Retiro", usuario.nombre, "Retiro de efectivo"};
    usuario.movimientos.push_back(nuevo_movimiento);
}
// Función para comprar o vender dólares
void comprar_vender_dolares(&usuario){
    cout << "¿Desea comprar o vender dólares? (c/v): ";
    char opcion;
    cin >> opcion;

    if (opcion == 'c' || opcion == 'C') {
        // Comprar dólares
        float monto_dolares;
        cout << "Ingrese el monto de dólares que desea comprar: ";
        cin >> monto_dolares;

        float monto_pesos = monto_dolares * 1000;  // Tasa de cambio: 1 USD = 1000 ARS

        if (monto_pesos <= usuario.saldo) {
            usuario.saldo -= monto_pesos;  // Descontar el monto en pesos de la cuenta
            usuario.dolares += monto_dolares;  // Agregar los dólares a la cuenta

            // Registrar el movimiento en un archivo de texto
            ofstream archivo("movimientos.txt", ios::app);
            if (archivo.is_open()) {
                archivo << "Compra de dólares: USD$ " << monto_dolares << ", Monto en pesos: $" << monto_pesos << ", Nuevo saldo: $" << usuario.saldo << endl;
                archivo.close();
                cout << "El movimiento ha sido registrado en movimientos.txt." << endl;
            } else {
                cout << "No se pudo abrir el archivo para registrar el movimiento." << endl;
            }

            // Agregar el movimiento al vector de movimientos
            Movimiento nuevo_movimiento = {"Compra", usuario.nombre, "Compra de dólares"};
            usuario.movimientos.push_back(nuevo_movimiento);

            cout << "Compra exitosa! Ahora tiene USD$ " << usuario.dolares << endl;
        } else {
            cout << "No tiene suficiente saldo en pesos para comprar esa cantidad de dólares." << endl;
            cout << "Por favor ingrese un monto menor o igual a su saldo en pesos." << endl;
        }

    } else if (opcion == 'v' || opcion == 'V') {
        // Vender dólares
        if (usuario.dolares < 10) {
            cout << "No puede vender dólares porque tiene menos de USD$ 10." << endl;
            return;
        }

        float monto_dolares;
        cout << "Ingrese el monto de dólares que desea vender: ";
        cin >> monto_dolares;

        if (monto_dolares <= usuario.dolares) {
            float monto_pesos = monto_dolares * 1000;  // Tasa de cambio: 1 USD = 1000 ARS

            usuario.dolares -= monto_dolares;  // Descontar los dólares de la cuenta
            usuario.saldo += monto_pesos;  // Agregar el monto en pesos a la cuenta

            // Registrar el movimiento en un archivo de texto
            ofstream archivo("movimientos.txt", ios::app);
            if (archivo.is_open()) {
                archivo << "Venta de dólares: USD$ " << monto_dolares << ", Monto en pesos: $" << monto_pesos << ", Nuevo saldo: $" << usuario.saldo << endl;
                archivo.close();
                cout << "El movimiento ha sido registrado en movimientos.txt." << endl;
            } else {
                cout << "No se pudo abrir el archivo para registrar el movimiento." << endl;
            }

            // Agregar el movimiento al vector de movimientos
            Movimiento nuevo_movimiento = {"Venta", usuario.nombre, "Venta de dólares"};
            usuario.movimientos.push_back(nuevo_movimiento);

            cout << "Venta exitosa! Ahora tiene USD$ " << usuario.dolares << endl;
        } else {
            cout << "No tiene suficientes dólares en su cuenta para realizar esta venta." << endl;
            cout << "Por favor ingrese un monto menor o igual a su saldo en dólares." << endl;
        }

    } else {
        cout << "Opción no válida. Por favor, ingrese 'c' para comprar o 'v' para vender dólares." << endl;
    }
}

int main() {
    Cuenta usuario;();
            validar_usuario(usuario);
        } else {
            return 0; // Si el usuario no quiere registrarse, salir
        }
    }

    while (opcion != 10) {
        menu_principal(usuario);
        cin >> opcion;

        switch (opcion) {
        case 1:
            ingresar_efectivo(usuario);
            break;
        case 2:
            retirar_efectivo(usuario);
            break;
        case 3:
            comprar_vender_dolares(usuario); 
        break;
        case 4:
            retirar_dolares(usuario, opcion);
            break;
        case 5:
            armar_plazo_fijo(usuario, opcion);
            break;
        case 6:
            cancelar_plazo_fijo(usuario, opcion);
            break;File Handling: Consider adding error checks when opening/writing to files.

        case 7:
            pedir_prestamo(usuario, opcion);
            break;
        case 8:
            ver_movimientos(usuario);
            break;
        case 9:
            actualizar_datos(usuario, opcion);
            break;
        case 10:
            cout << "Gracias por utilizar nuestro sistema " << usuario.nombre << ", vuelva pronto." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
    }

    return 0;
}