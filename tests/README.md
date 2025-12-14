# WiseIO Tests

Набор тестов для библиотеки WiseIO с использованием Google Test.

## Структура тестов

```
tests/
├── CMakeLists.txt           # Конфигурация для CMake
├── cases/test_stream_basic.cpp    # Базовые тесты Stream (создание, перемещение, размер файла)
├── cases/test_stream_read.cpp     # Тесты на чтение (CRead, CustomRead, все перегрузки)
├── cases/test_stream_write.cpp    # Тесты на запись (CWrite, AWrite, CustomWrite)
├── cases/test_bytes_buffer.cpp    # Тесты BytesIOBuffer
├── cases/test_string_buffer.cpp   # Тесты StringIOBuffer
└── cases/test_integration.cpp     # Интеграционные тесты
```

## Покрытие тестами

### Stream (test_stream_basic.cpp)
- ✅ CreateStream для всех режимов (Read, Write, Append, ReadAndWrite)
- ✅ Обработка ошибок (несуществующие файлы)
- ✅ Move constructor и move assignment
- ✅ GetFileSize (пустые, малые, большие файлы)
- ✅ SetCursor, IsEOF
- ✅ Close (одиночный и множественные вызовы)

### Stream Reading (test_stream_read.cpp)
- ✅ CRead с vector<uint8_t> (пустые, малые, большие файлы)
- ✅ CRead с IOBuffer (BytesIOBuffer, StringIOBuffer)
- ✅ CRead с std::string
- ✅ CustomRead с offset (все перегрузки)
- ✅ Множественные чтения
- ✅ Бинарные данные
- ✅ SetCursor + чтение
- ✅ EOF handling

### Stream Writing (test_stream_write.cpp)
- ✅ CWrite с vector<uint8_t> (пустые, малые, большие данные)
- ✅ CWrite с IOBuffer
- ✅ CWrite с std::string
- ✅ AWrite (Append mode) - все перегрузки
- ✅ CustomWrite с offset
- ✅ ReadAndWrite mode
- ✅ Проверка режимов (ошибки при неправильном режиме)
- ✅ Бинарные данные
- ✅ SetCursor + запись

### BytesIOBuffer (test_bytes_buffer.cpp)
- ✅ Базовые операции (GetDataPtr, GetBufferSize)
- ✅ ResizeBuffer (увеличение, уменьшение, до нуля, большие размеры)
- ✅ SetCursor (валидные/невалидные позиции)
- ✅ AddDataToBuffer (пустые, малые, множественные, большие данные)
- ✅ IsData (различные состояния курсора)
- ✅ ReadFromBuffer (различные размеры, множественные чтения)
- ✅ Clear (сброс данных и курсора)
- ✅ Комбинированные сценарии
- ✅ Стресс-тесты

### StringIOBuffer (test_string_buffer.cpp)
- ✅ Базовые операции
- ✅ SetEncoding (UTF-8, UTF-16)
- ✅ GetLen (с разными кодировками)
- ✅ AddDataToBuffer (строки, множественные вызовы)
- ✅ IsLines
- ✅ GetLine (одиночные/множественные строки, пустые строки)
- ✅ SetIgnoreComments (фильтрация комментариев)
- ✅ Clear
- ✅ Специальные символы (табы, \r\n)
- ✅ Проверка багов в ReadLine

### Integration Tests (test_integration.cpp)
- ✅ Stream + BytesIOBuffer (чтение/запись)
- ✅ Stream + StringIOBuffer (текстовые файлы)
- ✅ Фильтрация комментариев
- ✅ Копирование файлов
- ✅ Append mode (множественные записи)
- ✅ ReadAndWrite mode (модификация файлов)
- ✅ Сложные сценарии (обработка CSV, бинарные протоколы)
- ✅ Стресс-тесты

## Сборка и запуск

### Требования
- CMake >= 3.12
- C++23 совместимый компилятор
- Google Test (загружается автоматически через FetchContent)

### Сборка

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Запуск всех тестов

```bash
cd build
ctest --output-on-failure
```

Или напрямую:

```bash
./tests/wiseio_tests
```

### Запуск конкретного теста

```bash
./tests/wiseio_tests --gtest_filter=StreamBasicTest.CreateStreamReadMode_Success
```

### Запуск группы тестов

```bash
# Все тесты Stream
./tests/wiseio_tests --gtest_filter=Stream*

# Все тесты BytesBuffer
./tests/wiseio_tests --gtest_filter=BytesBufferTest*

# Все тесты чтения
./tests/wiseio_tests --gtest_filter=StreamReadTest*
```

### Подробный вывод

```bash
./tests/wiseio_tests --gtest_print_time=1
```

### Проверка coverage (если установлен gcov/lcov)

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage" ..
cmake --build .
./tests/wiseio_tests
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --list coverage.info
```

## Целевой Coverage

Текущий набор тестов покрывает примерно **90%** функций библиотеки:

- ✅ Stream: все публичные методы + граничные случаи
- ✅ BytesIOBuffer: 100% методов
- ✅ StringIOBuffer: ~90% (SetIgnoreBlank недоступен в API)
- ✅ Интеграция: основные сценарии использования

## Добавление новых тестов

Для добавления новых тестов:

1. Создайте файл `test_<название>.cpp` в папке `tests/`
2. Добавьте его в `tests/CMakeLists.txt`:
   ```cmake
   add_executable(wiseio_tests
       ...
       test_<название>.cpp
   )
   ```
3. Используйте Google Test макросы:
   - `TEST_F(ClassName, TestName)` для тестов с fixture
   - `TEST(SuiteName, TestName)` для простых тестов
   - `EXPECT_*` для проверок, которые не останавливают тест
   - `ASSERT_*` для критичных проверок

## Примеры тестов

### Позитивный тест
```cpp
TEST_F(StreamReadTest, CRead_Vector_SmallFile) {
    std::string content = "Hello";
    auto path = CreateTestFile("small.txt", content);
    auto stream = wiseio::CreateStream(path.c_str(), wiseio::OpenMode::kRead);
    
    std::vector<uint8_t> buffer(10);
    ssize_t bytes_read = stream.CRead(buffer);
    
    EXPECT_EQ(bytes_read, content.size());
    EXPECT_EQ(buffer.size(), content.size());
}
```

### Негативный тест
```cpp
TEST_F(StreamBasicTest, CreateStreamReadMode_FileNotExists_Throws) {
    auto path = (test_dir_ / "nonexistent.txt").string();
    
    EXPECT_THROW({
        auto stream = wiseio::CreateStream(path.c_str(), wiseio::OpenMode::kRead);
    }, std::runtime_error);
}
```

### Граничный случай
```cpp
TEST_F(BytesBufferTest, SetCursor_BeyondEnd_Throws) {
    buffer_.ResizeBuffer(10);
    EXPECT_THROW(buffer_.SetCursor(11), std::out_of_range);
}
```
