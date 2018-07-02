# Cpu-Scheduling-Algorithm

Hi! I'm **Emre TUFEKCI** this project made for  **Cyprus International University** *Operating Systems Course.*
By Following this tutorial you can reach how can you use this project on your machine.

# Functionality
![mainmenu](https://user-images.githubusercontent.com/23323000/42138481-f26bb92c-7d86-11e8-919d-8e7f5ceee6ae.png)

1) Scheduling Method
2) Preemptive Mod
3) Non-Preemtpive Mod
4) Show Result
5) End Program
Detail of this menu showed below.

# Compile

This project is mainly offered only source code, so for using this project you must compile it. Open Terminal and run that code.
```
    gcc -o <filename> cpuSchedulingAlgorithm.c 
```
After run this code, you should have a file with a \<filename> name.
    
## Run Application

In the terminal, you should run this code as well for using application compiled version.

```
./<filename> -f input.txt -o output.txt
```  
 **Warning!** If you don't have input.txt this project will not work correctly, however without output.txt file in your directory it will create automatically. So you just need a input.txt file.

## Input.txt file usage

In input.txt file you will see as a example

> -5:0:3
-4:1:2
-3:1:1
-4:2:2
-3:3:1

|Burst  Time  |Arrival Time  |Priority	|
|--|--|--|
|5|0|3|
|4|1|3|
|3|1|1|
|4|2|2|
|3|3|1|

>Note that: You can change all values from input.txt this values are just an example 

## Output.txt file usage

This file is used for storage all necesary output.
While using the program all results will be saved in output.txt as a open this file or Typing 4 in the main menu as a 
"4) Show Result"
 you will see the all result that you have reached.


## Scheduling Method

![menu1](https://user-images.githubusercontent.com/23323000/42138500-32b05ff6-7d87-11e8-969c-210a081498ba.png)

## Result Example
![menu4](https://user-images.githubusercontent.com/23323000/42138539-628f8828-7d87-11e8-98d4-f35ae1a88dbb.png)

