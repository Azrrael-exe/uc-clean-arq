# Test Structure - Clean Architecture

Este proyecto sigue Clean Architecture y organiza los tests por capas para mantener la separación de responsabilidades.

## 📁 Estructura de Tests

```
test/
├── test_domain/           # Domain Layer Tests (env:native)
│   └── test_voltage.cpp   
├── test_app/              # Application Layer Tests (env:native) 
│   └── test_example_use_case.cpp  
├── test_infrastructure/   # Infrastructure Layer Tests (env:target + native)
│   └── test_example_driver.cpp    
└── README.md
```

## 🎯 Tipos de Tests por Capa

### Domain Layer (`test_domain/`)
- **Qué testear**: Value Objects, Entities, Domain Services
- **Entorno**: `env:native` (rápido, puro C++)
- **Dependencias**: Solo STL, sin Arduino/HAL
- **Ejemplo**: Tests de Voltage value object

### Application Layer (`test_app/`)
- **Qué testear**: Use Cases, Application Services
- **Entorno**: `env:native` (con mocks para ports)
- **Dependencias**: Domain + Ports (interfaces), sin implementaciones concretas
- **Ejemplo**: Tests de casos de uso que orquestan lógica de dominio

### Infrastructure Layer (`test_infrastructure/`)
- **Qué testear**: Drivers, HAL implementations, Adapters
- **Entorno**: `env:native` (con mocks) + `env:target` (integración)
- **Dependencias**: Puede incluir Arduino.h, HAL, RTOS
- **Ejemplo**: Tests de sensores, actuadores, storage

## 🚀 Comandos de Ejecución

### Ejecutar todos los tests
```bash
platformio test -e native
```

### Ejecutar tests por capa
```bash
# Solo domain layer
platformio test -e native --filter test_domain

# Solo app layer  
platformio test -e native --filter test_app

# Solo infrastructure layer
platformio test -e native --filter test_infrastructure
```

### Ejecutar test específico
```bash
# Test específico de voltage (dentro de domain)
platformio test -e native --filter test_domain

# Para ejecutar múltiples capas, ejecuta comandos separados:
platformio test -e native --filter test_domain
platformio test -e native --filter test_app
```

## 📋 Convenciones de Naming

### Archivos de Test
- **Domain**: `test_<value_object>.cpp`, `test_<entity>.cpp`
- **App**: `test_<use_case>.cpp`, `test_<service>.cpp`  
- **Infrastructure**: `test_<driver>.cpp`, `test_<adapter>.cpp`

### Funciones de Test
- Usar prefijo `test_` seguido de descripción clara
- Ejemplo: `test_voltage_construction_valid()`

## 🏗️ Estructura de Archivo de Test

```cpp
#include <unity.h>
#include <domain/voltage.h>  // Include what you're testing

void setUp(void) {
    // Setup before each test
}

void tearDown(void) {
    // Cleanup after each test  
}

void test_specific_functionality() {
    // Arrange
    // Act
    // Assert
    TEST_ASSERT_EQUAL_FLOAT(expected, actual);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_specific_functionality);
    return UNITY_END();
}
```

## 🎨 Principios de Testing en Clean Architecture

1. **Domain tests**: Rápidos, puros, sin I/O
2. **App tests**: Usan mocks para ports, sin implementaciones concretas
3. **Infrastructure tests**: Pueden usar hardware real o simulado
4. **Dependency Direction**: Tests siguen la misma regla de dependencias que el código
5. **Isolation**: Cada capa se testea independientemente

## 📊 Estrategia de Testing

- **Unit Tests**: Domain + App (env:native) - Rápidos y puros
- **Integration Tests**: Infrastructure (env:target) - Con hardware real
- **End-to-End Tests**: Flujos completos usando todos los layers

## 🔄 Workflow de Desarrollo

1. **Red**: Escribir test que falle
2. **Green**: Implementar código mínimo para pasar
3. **Refactor**: Mejorar código manteniendo tests verdes
4. **Repeat**: Por cada nueva funcionalidad

### Orden recomendado:
1. Tests de Domain (value objects, entities)
2. Tests de App (use cases con mocks)
3. Tests de Infrastructure (drivers, adapters)
4. Tests de integración end-to-end
