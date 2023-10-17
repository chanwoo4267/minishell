<a name="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]

<br />
<div align="center">

<h3 align="center">Minishell</h3>

  <p align="center">
    This project is about creating a simple shell. Your own little bash.
    <br />
    <a href="https://cdn.intra.42.fr/pdf/pdf/102776/en.subject.pdf"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/chanwoo4267/minishell/issues">Report Bug</a>
    ·
    <a href="https://github.com/chanwoo4267/minishell/issues">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]]() <!-- ?? -->



<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C][C-shield]][C-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

* C99+

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/chanwoo4267/minishell
   ```
3. Compile source codes
   ```sh
   make all
   ```
4. execute executable file
   ```js
   ./minishell
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

Implemented Features :

* bash-prompt
* working history
* search and laungh executable
* signal handling
* environment variables
* redirections
* pipes
* interrupts
* few builtins

Implemented Builtins :

* echo with -n option
* cd with relative or absolute path
* pwd
* export
* unset
* env
* exit

Unimplemented Featurs :

* && or || with parenthesis
* wildcard

_For more examples, please refer to the [Documentation](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
* [Notion](https://www.notion.so/Minishell-c84036f4661f466dbd58afefe2f82ef7?pvs=4)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/github_username/repo_name.svg?style=for-the-badge
[contributors-url]: https://github.com/github_username/repo_name/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/github_username/repo_name.svg?style=for-the-badge
[forks-url]: https://github.com/github_username/repo_name/network/members

[C-shield]: https://img.shields.io/badge/C-35495E?style=for-the-badge&logo=c&logoColor=White
[C-url]: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2731.pdf

[product-screenshot]: image/minishell.png