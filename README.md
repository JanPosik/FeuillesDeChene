# Feuilles de Chênes
Multi-platform program that runs on Linux and Windows. Currently as a CLI only program. In future, it is planned to be available as Qt and Web application powered by the same core.

**Learn words from any language**. On Linux, the CLI offers colored interface, therefore making it easier to read.

## Data Input: Words Entries & Commands
The program features with only one interface with two modes. The default one; the word translation, is available with no special effort. 
The second one is there to change program's configuration or variables, the program recognizes a command, when the string starts with # sign.

### Every command is listed below:

| Command | Description |
| :--- | :--- |
| `#help` | prints message containing all commands and its use |
| `#exit` | closes program |
| `#easy` | changes word filter to only easy difficulty words |
| `#medium` | changes word filter to only medium difficulty words |
| `#hard` | changes word filter to only hard difficulty words |
| `#any` | no filter; uses every word from database |
| `#` | skips current word |

## Language Independent
With external database files, ten of them are provided in source code, the program becomes more flexible and thus could be used for any language. It is also possible to use your own database when following few rules, the rules can be found [here](#custom-databases).

## Custom Databases
With small effort, not counting writing down the words and its translation, it is easy to start using custom words lists. However, there are some criteria to that must be followed.

### Rules for making custom databases

| Rule | Example | Description |
| :--- | :---    | :---        |
| first line | `en;fr` | defines languages hints, must be at first line |
| word | `sky;ciel;1` | three segmented word with its difficulty |
| difficulty | `EASY;MEDIUM;HARD` | in range 1–3, every difficulty must have atleast one word assigned |
| comments | `# fruits` | with # at first position, the comment can be used |
| blank lines | | blank lines will not be processed |
| uncomplete word | `sun;soleil` | not completed words will not be processed |
| format | `en_fr.txt` | format is not specified, .txt is recommended |

### Linking database
When executing the binary file, the `-d` switch can be used followed by path to the database `./data/en_fr.txt`, the switch must be typed before the path, otherwise, defualt path would be used.

Example of execution in CLI:

`username@computer:~/Programs/FeuillesDeChene/$ ./FeuillesDeChene -d ../data/en_fr.txt`
