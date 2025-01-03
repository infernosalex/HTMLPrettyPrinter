# HTMLPrettyPrinter
<p align="center">
  <img src="https://github.com/user-attachments/assets/7014efdd-031b-4120-aff4-ceef1fcd4c31" alt="HPP logo" width="150" height="150" style="border-radius: 50%;">
  <br>
  <a href="https://github.com/infernosalex/HTMLPrettyPrinter">
    <img src="https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white" alt="GitHub">
  </a>
</p>

This is a simple HTML pretty printer that takes an HTML file and prints it in a more readable format. It is written in Bash.

## Usage
Make it executable:
```bash
chmod +x hpp
```

Move it to your PATH (e.g., `/usr/local/bin`):
```bash
sudo mv hpp /usr/local/bin
```
### Examples

```bash
hpp test.html
hpp test_compressed.html -o test.html
hpp test_compressed.html -r 
```

Authors: [Scanteie Alexandru](https://github.com/infernosalex), [Andreiana Bogdan](https://github.com/bogdanws)