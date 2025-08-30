/*Спринт 4/22: 2 спринт → Тема 3/7: Пары и кортежи → Урок 7/8


Задание 2. Трекер задач
Для работы над текущими задачами тимлид Матвей нанял нескольких разработчиков. Чтобы лучше следить за тем, 
как продвигаются работы, Матвею нужен трекер задач. Каждая задача привязана к определённому разработчику и проходит 
четыре статуса: NEW → IN_PROGRESS → TESTING → DONE. В его компании принято выполнять сначала новые задачи (статус NEW),
затем задачи в статусе IN_PROGRESS и т. д. Матвей хочет быстро узнавать статистику задач своих коллег: сколько задач
 находится в каждом из статусов.
Реализуйте:
Класс TeamTasks, трекер задач. Он может хранить только статистику — сколько задач какого разработчика находится 
в каком статусе. Количество разработчиков может быть любым целым положительным числом.
Метод GetPersonTasksInfo класса TeamTasks, принимающий имя разработчика и возвращающий статистику его задач.
Метод AddNewTask класса TeamTasks. Позволяет добавить одну задачу в статусе NEW указанному разработчику.
Метод PerformPersonTasks класса TeamTasks. Он принимает имя разработчика и число N и вызывается, когда разработчик
 выполнил N задач. Считается, что разработчик выполняет вначале задачи с самым низким статусом, и эти задачи
  переходят в следующий статус.
Точные сигнатуры методов описаны в заготовке кода.
Метод PerformPersonTasks принимает параметры: person — имя разработчика, task_count — количество задач, 
которые надо выполнить. Его алгоритм таков:
Рассмотреть все невыполненные задачи разработчика person.
Среди них рассмотреть первые task_count задач и перевести каждую из них в следующий статус в соответствии 
с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE. Таким образом сначала выполнятся все задачи 
в статусе NEW, затем все задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
Этот метод возвращает пару из двух элементов:
Словарь со статусами обновившихся задач: количество обновившихся задач по каждому статусу.
Информацию о невыполненных задачах — тех, статус которых не DONE и не изменился. Также в виде словаря, 
хранящего количество по статусу.
Для словаря, хранящего количество задач по статусам, предусмотрен псевдоним: using TasksInfo = map<TaskStatus, int>.
Конструкция using позволила создать псевдонимы для типа TasksInfo, использование которого
 будет эквивалентно map<TaskStatus, int>. Его проще написать, и не нужно будет вспоминать для чего он используется.
Ограничения
В методе PerformPersonTasks не обновляйте статус одной и той же задачи дважды. Если задача перешла
 из статуса NEW в статус IN_PROGRESS, то при рассмотрении задач в статусе IN_PROGRESS эта задача не должна 
 быть обновлена. Будут рассмотрены те задачи, которые находились в статусе IN_PROGRESS до вызова метода PerformPersonTasks.
Также в методе PerformPersonTasks второй элемент возвращаемого кортежа не должен содержать задач со статусом DONE.
Если разработчика с именем person нет, метод PerformPersonTasks возвращает кортеж из двух пустых TasksInfo.
Не используйте цикл для переноса задач по одной. В словаре TasksInfo хранятся числа: отнимите число из 
одного статуса и прибавьте к другому.
Метод GetPersonTasksInfo должен остаться константным.
Как будет тестироваться программа
Будет проверена корректность класса TeamTasks и его методов.
Гарантируется, что параметр task_count метода PerformPersonTasks — положительное число. Если task_count 
превышает текущее количество невыполненных задач разработчика, достаточно считать, что task_count равен
 количеству невыполненных задач. Дважды обновлять статус какой-либо задачи в этом случае не нужно.
Гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
Пример работы метода PerformPersonTasks
Допустим, у конкретного разработчика десять задач со следующими статусами:
NEW — 3 задачи,
IN_PROGRESS — 2 задачи,
TESTING — 4 задачи,
DONE — 1 задача.
Поступает команда PerformPersonTasks с параметром task_count, равным 4. Это означает, что нужно 
обновить статус c NEW до IN_PROGRESS для трёх задач и с IN_PROGRESS до TESTING для одной задачи. 
Новые статусы задач:
NEW — нет задач,
IN_PROGRESS — 4 задачи: 3 обновлённых, 1 старая,
TESTING — 5 задач: 1 обновлённая, 4 старых,
DONE — 1 старая.
В этом случае нужно вернуть кортеж из двух словарей:
Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
Необновлённые задачи, исключая задачи со статусом DONE: IN_PROGRESS — 1, TESTING — 4.
Пример ввода

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
    TasksInfo updated_tasks, untouched_tasks;
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
} 
Пример вывода
Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done 
Пример ввода

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Sasha");
    tasks.AddNewTask("Sasha");
    tasks.AddNewTask("Sasha");
  
    TasksInfo updated_tasks, untouched_tasks;
    for (int i = 0; i != 4; ++i) {
        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Sasha", 10);
        cout << "Updated Sasha's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Sasha's tasks: ";
        PrintTasksInfo(untouched_tasks);
    }
} 
Пример вывода
Performing 10 tasks...
Updated Sasha's tasks: 0 new tasks, 3 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Performing 10 tasks...
Updated Sasha's tasks: 0 new tasks, 0 tasks in progress, 3 tasks are being tested, 0 tasks are done
Untouched Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Performing 10 tasks...
Updated Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 3 tasks are done
Untouched Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Performing 10 tasks...
Updated Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Sasha's tasks: 0 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done 
Несмотря на то, что пример выполняет команду PerformPersonTasks с параметром task_count, равным 10,
 статус обновится только у трёх задач и только на следующий статус.
 Если вызвать эту команду 4 раза, задачи с статусом NEW дойдут до DONE за 3 подхода, а на четвёртом
  подходе в ответе будут только нули.

  Чтобы удалить задачи в статусе DONE из второй элемент возвращаемого кортежа, воспользуйтесь методом erase
Чтобы получить следующий статус после другого конкретного статуса, вам может пригодиться эта функция:

static TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
} 
Не меняйте словарь по которому вы итерируетесь в цикле for(... : ...) – это приводит к неопределённому поведению. Лучше используйте обычный цикл for(...;...;...), который начнёт с статуса NEW и будет двигаться до DONE не включительно. Написать красивый код вам поможет функция Next.
В цикле вам нужно вычислить количество задач для переноса в следующий статус. Это можно сделать так:
Из количество задач в текущем статусе вычесть количество задач, которые только что перенесли в этот статус.
Взять минимум с количеством задач, которые нужно обновить.
Полученное количество нужно вычесть из числа задач текущего статуса, прибавить к задачам в следующем статусе, и сохранить для ответа.
При возникновении сложностей вы можете ознакомиться с видео-разбором решения этой задачи.
*/


#include <algorithm>// Содержит функцию lexicographical_compare
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <cctype> // содержит функцию tolower.
#include <numeric>
#include <sstream>
#include <map>
#include <cmath>
#include <cstdint>
#include <limits>
#include <tuple>

using namespace std;

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const;

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person);

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count);
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"s
         << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
         << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
         << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia"s);
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan"s);
    }
    cout << "Ilia's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"s));
    cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
}