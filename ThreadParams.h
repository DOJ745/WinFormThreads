#pragma once
// Структура для передачи параметров потока
public value struct ThreadParams 
{
	int data; // Данные для работы в потоке
	System::String message;
};