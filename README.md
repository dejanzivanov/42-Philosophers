# 42-Philosophers
Intro project about using threads and multi-threading. The most common problem of [Dining Philosophers Problem. ](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
**![push_swap_mark](https://github.com/dejanzivanov/42-Philosophers/blob/master/philosophers.png)**  

This project is heavily configurational dependant. Depending of your system CPU usage results, may vary. If your cpu has very low percent of usage. 
Then results will be the same as requested in subject.

# How to use this project


Make sure that you have [GCC](https://gcc.gnu.org/), or [Clang](https://clang.llvm.org/) installed  
If you do not here is how to install them:

Install Clang:  
```
sudo apt-add-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-6.0 main"
```
```
sudo apt-get install -y clang-6.0 lld-6.0
```
Install GCC:  
```
sudo apt update
```
```
sudo apt install build-essential
```
```
sudo apt-get install manpages-dev
```
```
gcc --version
```
That’s it. GCC is now installed on your system, and you can start using it.  
<br/>

Clone the repository:  
```
https://github.com/dejanzivanov/42-Philosophers.git
```
Change the directory:  
```
cd 42-Philosophers/philo
```
Run the make command: 
```
make
```
There are 4 test cases that should work so your project could pass evaluations, and you can test this project with following commands:
1) 
```
./philo 5 800 200 200
```
2)
```
./philo 5 800 200 200 7
```
3)
```
./philo 4 410 200 200
```
4)
```
./philo 4 310 200 100
```
1) Test with 5 800 200 200, no one should die!
2) Test with 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each.
3) Test with 4 410 200 200, no one should die!
4) Test with 4 310 200 100, a philosopher should die!


## 📱 Connect With Me!
[![LinkedIn](https://img.shields.io/badge/-LinkedIn-0e76a8?style=flat-square&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/dejanzivanov/)
[![Email](https://img.shields.io/badge/Email-%20-d95040?style=flat-square&logo=mail&logoColor=white)](mailto:contact@dejanzivanov.com)
[![Personal Website](https://img.shields.io/badge/-Personal%20Website-f8f8fa?style=flat-square)](https://dejanzivanov.com/)
[![Github](https://img.shields.io/badge/GitHub-100000?style=flat-square&log=github&logoColor=white)](https://github.com/dejanzivanov)
[![Discord](https://img.shields.io/badge/Discord-7289DA?style=flat-square&logo=discord&logoColor=white)](castiel0504#9273)
