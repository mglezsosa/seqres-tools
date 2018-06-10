# SeqRes tools

SeqRes tools stands for **Seq**uences **Res**emblance tools.

<sub><sup>SeqRes is meant for learning purposes only.</sup></sub>

## Dependencies

* POSIX platforms support only.
* [OpenMP](https://www.openmp.org/) compatible compiler.
* [Cmake](https://cmake.org/) for pre-compilation.

## Installation

1. Clone source project with git.
    ```bash
    git clone https://github.com/mglezsosa/seqres-tools.git
    ```
   
2. Compile. Inside the folder:
    ```bash
    cmake . && make
    ```

## Usage

* For compute distances:
    ```bash
    bash bin/distances.sh k first.fasta second.fasta
    ```
   
* For determine hits:
    ```bash
    bash bin/hits.sh k first.fasta second.fasta hits-file.txt
    ```

* For further information of `seqres` commands run:
    ```bash
    ./seqres --help
    ```