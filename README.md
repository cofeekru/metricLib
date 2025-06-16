# metricLib


<p align="center">
    <img src="https://img.shields.io/github/languages/top/cofeekru/metricLib?style=for-the-badge">
    <img src="https://img.shields.io/github/languages/count/cofeekru/metricLib?style=for-the-badge">
    <img src="https://img.shields.io/github/license/cofeekru/metricLib?style=for-the-badge">
    <img src="https://img.shields.io/github/stars/cofeekru/metricLib?style=for-the-badge">
    <img src="https://img.shields.io/github/issues/cofeekru/metricLib?style=for-the-badge">
    <img src="https://img.shields.io/github/last-commit/cofeekru/metricLib?style=for-the-badge">
</p>

## Описание.
metricLib это библиотека разработанная на C++ для сбора и сохранения метрик в файл в текстовом виде.


## Установка и сборка.
Далее подразумевается, что CMake и компилятор уже установлен в систему.
Для сборки проекта необходимо выполнить следующие команды. 

1) Скачать репозиторий.
```
    git clone 
```

2) Создать директорию.
```
    mkdir build 
```

3) Сгенерировать файлы сборки.
```
    cmake build
```

4) Собрать проект.
```
    cmake --build build
```

## Обзор репозитория.
0) __.github/workflows__ - настройки пайплайнов

1) __build__ - дирекория с файлами сборки проекта (в поддиректории __bin__ находятся все исполняемые файлы)

2) __examples__ - директория с кодом для демонстрации работы библиотеки

3) __docs__ - настройки документации

4) __include__ - директория с заголовочными файлами _.hpp_ 

5) __src__ - директория с файлами _.cpp_ 

6) __tests__ - директория с тестами

## Документация.

Документация доступна по [ссылке](https://cofeekru.github.io/metricLib).