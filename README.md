# **CSV Summary maker with improved atof() function**       ![GitHub last commit](https://img.shields.io/github/last-commit/caojasamalex/atof_improved)


## Basic Overview

The main goal of this project is to develop a software solution that will efficiently and effectively summarize large CSV files provided by a scientific institutes into a much smaller files.

Function atof()  (_atof - alpha-to-float_) is function that, as a name says, converts alpha values into float values. But there is one problem - Function is not working with scientific notation of numbers, like 43.23e<sup>+23</sup>

Here, you can find new implemented function that fulfills the need of conversion scientific notation of numbers.

#### Example:

**Input CSV file would look like the table below:** (You can find this file in repository: "input.csv")

| Date        | Result        | Comment             |
| :--------:  | :--------:    | :--------:          |
| 12.01.2022. | 11            | All Cool            |
| 16/02/2022  | 3             | N/A                 |
| 15.01.2022. | 1e+1          | Scientific notation |
| 30.02.2022  | 213.21e+4     | N/A                 |
| 29.03.2022. | 23.435e+test23| Passed testing      |
| 29.02.2022. | 432.23e+tes   | Strange             |
| 30.01.2022. | 342           | N/A                 |
| 35.23.2022. | test          |                     |
| 21.09.2022. | 32.43e+2      |                     |
| 20.07.2022. | 43.23e+5      |                     |
| 31/12/2022  | 533.555e+6    | New Year testing    |

You can see that there are some values that are irregular, like some dates and results, etc...

There is implementation of checking and avoiding these values so the output summary is 100% erorr-free.

**Output CSV file would look like the table below:**

| Date        | Year        | NumOfRecords | Sum                 |
| :---------: | :---------: |:-----------: | :-----------------: |
| Januar      | 2022        | 3            | 363.00              |
| Februar     | 2022        | 1            | 3.00                |
| Jul         | 2022        | 1            | 4323000.00          |
| Septembar   | 2022        | 1            | 3243.00             |
| Decembar    | 2022        | 1            | 533555000.00        |

So, as you can see, the output file did not take into count rows with irregular values.

As for irregular results, like 432.23e<sup>+tes</sup>, the program saves them in another file in the following format:

>Line {num} cannot be converted into a number. Original value {val}, date {DD.MM.YYYY.}

## How To Use

#### Step 1 - Getting repository on your system


*You need to open command line. After that, type next line:*
```bash
# Clone this repository
$ git clone https://github.com/caojasamalex/atof_improved
```

#### Step 2 - Editing code (Skip this step if you don't want to edit anything)

*If you want to do some changes in the code you can do it from a command line typing commands below:*

```bash
# Get in repository
cd atof_improved

# Open main.cpp to edit
vi main.cpp
```

*If you don't want to open file with command line, you can use any c++ IDE*


#### Step 3 - Run

##### Command Line:

*After you opened command line, you need to type these commands:*

```bash
#Get in repository
cd atof_improved

#Locate files
ls

#Execute
./main
```

##### IDE:

*After you opened file from a IDE, you can press Run button and code will execute*

