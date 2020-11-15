# CMake skripta
cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

# Promenljive i porke
message(STATUS One Two Three)
message(STATUS "One Two Three")

set(MY_VAR "[1, 2, 3, 4]")
message(STATUS "This is my variable \"${MY_VAR}\" and this is my project name \"${PROJECT_NAME}\"")

# Kontrole i toka
if("TRUE")
    message("Example A - Case 1")
else()
    message("Example A - Case 2")
endif()

if("FALSE")
    message("Example B - Case 1")
else()
    message("Example B - Case 2")
endif()

# Regularni izrazi
If("This is an array [1, 2, 3, 4, 5]" MATCHES ".*[\[]([0-9]|,|[ ])+[\]].*")
    message("Example C - String contains an array!")
else()
    message("Example C - String doesn't contain an array!")
endif()

# Petlje
set(cnt 0)
while(cnt LESS 10)
    message(STATUS "Counter value is ${cnt}!")
    math(EXPR cnt "${cnt} + 1")
endwhile()

# Foreach petlja
foreach(item IN ITEMS apple orange peach banana)
    message(STATUS "Look at this ${item}!")
endforeach()

# Foreach iz opsega
foreach(idx RANGE 100) # Moze i: foreach(idx RANGE 50 100)
    message(STATUS "idx = ${idx}")
endforeach()

# Funkcija
function(show_name my_name)
    message(STATUS "My name is ${my_name}!")
endfunction()

show_name("Robotmurlock")
show_name("Banana" "Ignore This")

# Funkcija sa proizvoljnim brojem argumenata
function(show_words)
    foreach(arg IN LISTS ARGV)
        message(STATUS ${arg})
    endforeach()
endfunction()

show_words(1 Two 3 Three 5)

# Funkcija sa "povratnom vrednošću"
function(increment var)
    math(EXPR new_value "${${var}} + 1")
    set(${var} "${new_value}" PARENT_SCOPE)
endfunction()

set(value 10)
increment(value)
message(STATUS "Result is ${value}!")