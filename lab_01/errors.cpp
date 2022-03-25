#include "errors.h"

int errors(const err_t &code)
{
    switch (code)
    {
        case FILE_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "При открытии файла произошла ошибка.");
            break;
        case ALLOCATION_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "При выделении памяти произошла ошибка.");
            break;
        case READ_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "При чтении файла произошла ошибка.");
            break;
        case PSIZE_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Некорретный размер количества точек.");
            break;
        case LSIZE_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Некорректный размер количества линий.");
            break;
        case MEMORY_ERROR:
            QMessageBox::critical(NULL, "Ошибка", "Ошибка при обращении к данным.");
            break;
        default:
            QMessageBox::critical(NULL, "Ошибка", "Неизвестная комманда.");
    }

    return SUCCESS;
}
