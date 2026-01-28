# Feuilles de Chêne
Multi-platform program running on Linux and Windows for learning words from any language. It is an independend core that powers CLI, Qt and web application. Project is built with CMake, developed on Linux. This program is language independent; any word database can be attached, when some rules are followed. The concept is comparing one string with another, thus it could be potentionaly used more widly, e.g. Morse code, yes/no question etc.

## CLI version
On Linux, the CLI version offers colored interface, therefore making it easier to read, that's not accomplished on Windows.

The program features a single interface with two modes. The default one; the word translation, is available with no special effort. That's when the words are translated.
The second one is there to change program's state configuration or variables, the program recognizes a command, when the string starts with `#` sign.

### Every command is listed below:

| Command | Description |
| :--- | :--- |
| `#help` | prints message containing all commands and its use |
| `#exit` | closes program |
| `#easy` | changes word filter to only easy difficulty words |
| `#medium` | changes word filter to only medium difficulty words |
| `#hard` | changes word filter to only hard difficulty words |
| `#any` | no filter; uses every word from database |
| `#flip` | flips targeted language |
| `#record` | sets record to current score |
| `#` | skips current word |

### Attaching databases
With external databases, ten of them are provided in `data/` folder, the program becomes more flexible and could be used for any language. It is possible to make custom databases, when following some rules, that can be found [here](#custom-databases).

When executing program in the terminal, the `-d` switch can be used followed with path to database to use it. For example: `user@computer:~/FeuillesDeChene$ ./FeuillesDeChene -d ./data/en_fr.txt`.

### Modes and Records
Currently, program contains only one mode **Classic** and one record. If the record is beated, is saves in `records.txt` file. Unfortunately, if the program is not opened in its directory, the record file won't be reached.

## Qt version
Qt version serves more friendly UI, of course, using the same core as CLI. These two version are practicly same, they just differently abstract core functions and dealing with input/output.

### Choosing resources
In the tab menu, there is possible to load database and records and change modes and difficulty. Database and records can be changed in runtime.

### Design
The design is minimalistic, with no animations or images. It shows fundemantal things as score, mode, difficulty.. also progress bar to new records, and if the answer is incorrect it shows the correct answer at the bottom of the window.

## Web version
This online version uses WebAssembly to access c++ core, then the functions is bridged with JavaScript for interaction with core and document elements. Application is built with Emscripten and CMake.
Web page is responsive, featuring shortcuts, animations, custom options and of course attaching custom databases, but doesn't resolves record, should be updated in future, when local storage saving will be implemented.
To build, you can run commands:
`emcmake cmake [path_to_CMakeLists.txt]`
`emmake make`
commands in this example are executed in `build` folder.

## Custom Databases
With small effort, not counting writing down the words and its translation, it is easy to start using custom words lists.

### Rules for making custom databases

| Rule | Example | Description |
| :--- | :---    | :---        |
| first line | `@feuilles_de_chene` | with this key core identifies the database |
| second line | `en;fr` | defines languages hints, must be right after the key |
| word | `sky;ciel;1` | three segmented word with its difficulty |
| difficulty | `EASY;MEDIUM;HARD` | in range 1–3, every difficulty must have at least one word assigned |
| comments | `# fruits` | with # at first position, the comment can be used |
| blank lines | | blank lines will not be processed |
| uncomplete word | `sun;soleil` | not completed words will not be processed |
| format | `en_fr.txt` | format is not specified, .txt is recommended |
