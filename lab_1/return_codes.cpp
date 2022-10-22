#include "return_codes.h"

void error_print(rc_t error)
{
    switch(error)
    {
        case FILE_ERROR:
            QMessageBox :: warning(NULL, "Ошибка", "Невозможно открыть файл");
        case INPUT_ERROR:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка ввода");
            break;
        case MEMORY_ERROR:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка выделения памяти");
            break;
        case UNKNOWN_COMMAND:
            QMessageBox :: warning(NULL, "Ошибка", "Неизвестная команда");
            break;
        case NO_FIGURE:
            QMessageBox :: warning(NULL, "Ошибка", "Фигура не задана");
            break;
        default:
            QMessageBox :: warning(NULL, "Ошибка", "Непредвиденная ситуация");
            break;
    }
}
