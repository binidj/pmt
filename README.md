# PMT

CLI Application to search pattern on text files. It is part of the first college project of **IF767 - Processamento de Cadeias de Caracteres**, course of Computer Science of Federal University of Pernambuco. 



## Running the project

clone the repository

```bash
  git clone https://github.com/binidj/pmt
```

Open the project folder

```bash
  cd pmt
```

Compile the application

```bash
  cmake -DCMAKE_BUILD_TYPE=Release ./
  make
```

Open the compiled file

```bash
  cd buil/src
```

Run it.

## Usage

#### Runs the application

```http
  pmt [options] pattern textfile [textfile...]\n"
```

| Argument   | Type       | Description                           |
| :---------- | :--------- | :---------------------------------- |
| `pattern` | `string` | **Required**. Pattern to be searched. |
| `textfile` | `path` | **Required**. Text file path. If there is more than one file, brackets or wildcards need to be used. |

## Extra options

| Command             | Function                                                |
| --------------------| ---------------------------------------------------------------- |
| `-e` `--edit emax` | Searches all aproximated ocurrences of the pattern with some distance *emax*
| `-p` `--pattern patternfile` | Specifies the pattern file *patternfile* that will be used on the search
| `-a` `--algorithm algorithm_name` | Specifies the algorithm *algorithm_name* that will be used on the pattern search
| `-c` `--count` | Prints the number of ocurrences of the specified pattern on all the text files.
| `-h` `--help` | Basic PMT options


#### Algorithms:
| Name         | String             |
| -------------| -------------------|
| Sliding Window | `sliding_window`
| KMP | `kmp`
| Boyer Moore | `boyer_moore`
| Sellers | `sellers`
| Wu Mamber | `wu_mamber`
| Aho Corasick | `aho_corasick`

README.md
