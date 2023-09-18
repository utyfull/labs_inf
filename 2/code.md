```

┌──(utyfull㉿kali)-[~]
└─$ ssh m_pinchuk@185.5.249.140
Enter passphrase for key '/home/utyfull/.ssh/id_ed25519': 
Welcome to Ubuntu 20.04.6 LTS (GNU/Linux 5.4.0-162-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage
New release '22.04.3 LTS' available.
Run 'do-release-upgrade' to upgrade to it.

Last login: Mon Sep 18 10:47:20 2023 from 85.143.224.30
m_pinchuk@vds2476450:~$ cd /home
m_pinchuk@vds2476450:/home$ who -m
m_pinchuk pts/10       2023-09-18 10:51 (85.143.224.30)
m_pinchuk@vds2476450:/home$ cd m_pinchuk
m_pinchuk@vds2476450:~$ pwd
/home/m_pinchuk
m_pinchuk@vds2476450:~$ cd -
/home
m_pinchuk@vds2476450:/home$ ls
a_bolotin  a_pereverzev  a_shiapov  d_kuleshov   d_shirshov  f_lerner    k_denisov    k_nikolskiy  mivallion  m_vlasko       n_gavrilov  n_radion     n_stepanov   v_frolov
a_ganyak   a_popov       d_jgenti   d_nurgaliev  e_fedorova  i_tatarkin  k_ismailova  m_hulagov    m_pinchuk  m_yavmetdinov  n_ivanov    n_soliviova  t_grigoriev  v_romanov
m_pinchuk@vds2476450:/home$ cd m_pinchuk
m_pinchuk@vds2476450:~$ mkdir 2
m_pinchuk@vds2476450:~$ cd 2
m_pinchuk@vds2476450:~/2$ nano test.txt
m_pinchuk@vds2476450:~/2$ cat test.txt
1
error
2
3
4
m_pinchuk@vds2476450:~/2$ cp /home/m_pinchuk/2/test.txt /home/m_pinchuk
m_pinchuk@vds2476450:~/2$ cd-
Could not find command-not-found database. Run 'sudo apt update' to populate it.
cd-: command not found
m_pinchuk@vds2476450:~/2$ cd -
/home/m_pinchuk
m_pinchuk@vds2476450:~$ ls
2  test.txt
m_pinchuk@vds2476450:~$ rm test.txt
m_pinchuk@vds2476450:~$ ls
2
m_pinchuk@vds2476450:~$ cd 2
m_pinchuk@vds2476450:~/2$ mv test.txt /home/m_pinchuk
m_pinchuk@vds2476450:~/2$ cd -
/home/m_pinchuk
m_pinchuk@vds2476450:~$ ls
2  test.txt
m_pinchuk@vds2476450:~$ grep "error" test.txt
error
m_pinchuk@vds2476450:~$ head test.txt
1
error
2
3
4
m_pinchuk@vds2476450:~$ tail n1 test.txt
tail: cannot open 'n1' for reading: No such file or directory
==> test.txt <==
1
error
2
3
4
m_pinchuk@vds2476450:~$ tail -n1 test.txt
4
m_pinchuk@vds2476450:~$ ps -A
    PID TTY          TIME CMD
      1 ?        00:00:41 systemd
      2 ?        00:00:00 kthreadd
      3 ?        00:00:00 rcu_gp
      4 ?        00:00:00 rcu_par_gp
      6 ?        00:00:00 kworker/0:0H-kblockd
      8 ?        00:00:00 mm_percpu_wq
      9 ?        00:00:45 ksoftirqd/0
     10 ?        00:06:43 rcu_sched
     11 ?        00:00:05 migration/0
     12 ?        00:00:00 idle_inject/0
     14 ?        00:00:00 cpuhp/0
     15 ?        00:00:00 kdevtmpfs
     16 ?        00:00:00 netns
     17 ?        00:00:00 rcu_tasks_kthre
     18 ?        00:00:00 kauditd
     19 ?        00:00:00 khungtaskd
     20 ?        00:00:00 oom_reaper
     21 ?        00:00:00 writeback
     22 ?        00:00:00 kcompactd0
     23 ?        00:00:00 ksmd
     24 ?        00:00:00 khugepaged
     70 ?        00:00:00 kintegrityd
     71 ?        00:00:00 kblockd
     72 ?        00:00:00 blkcg_punt_bio
     73 ?        00:00:00 tpm_dev_wq
     74 ?        00:00:00 ata_sff
     75 ?        00:00:00 md
     76 ?        00:00:00 edac-poller
     77 ?        00:00:00 devfreq_wq
     78 ?        00:00:00 watchdogd
     80 ?        00:00:00 kswapd0
     81 ?        00:00:00 ecryptfs-kthrea
     83 ?        00:00:00 kthrotld
     84 ?        00:00:00 acpi_thermal_pm
     85 ?        00:00:00 scsi_eh_0
     86 ?        00:00:00 scsi_tmf_0
     87 ?        00:00:00 scsi_eh_1
     88 ?        00:00:00 scsi_tmf_1
     90 ?        00:00:00 vfio-irqfd-clea
     92 ?        00:00:00 ipv6_addrconf
    101 ?        00:00:00 kstrp
    104 ?        00:00:00 kworker/u3:0
    117 ?        00:00:00 charger_manager
    152 ?        00:00:03 kworker/0:1H-kblockd
    171 ?        00:00:07 jbd2/vda2-8
    172 ?        00:00:00 ext4-rsv-conver
    204 ?        00:01:52 systemd-journal
    239 ?        00:00:10 systemd-udevd
    246 ?        00:00:07 systemd-resolve
    250 ?        00:00:08 systemd-timesyn
    268 ?        00:00:49 accounts-daemon
    269 ?        00:00:09 cron
    270 ?        00:00:03 dbus-daemon
    279 ?        00:00:00 networkd-dispat
    280 ?        00:00:18 rsyslogd
    282 ?        00:00:08 systemd-logind
    415 tty1     00:00:00 agetty
    416 ?        00:00:31 sshd
  55574 ?        00:00:01 kworker/u2:0-events_unbound
  56808 ?        00:00:00 sshd
  56863 ?        00:00:00 systemd
  56864 ?        00:00:00 (sd-pam)
  56887 ?        00:00:00 sshd
  56888 pts/9    00:00:00 bash
  57031 ?        00:00:00 sshd
  57046 ?        00:00:00 systemd
  57049 ?        00:00:00 (sd-pam)
  57071 ?        00:00:00 sshd
  57072 pts/12   00:00:00 bash
  57295 ?        00:00:00 sshd
  57397 ?        00:00:00 systemd
  57398 ?        00:00:00 (sd-pam)
  57422 ?        00:00:00 sshd
  57423 pts/2    00:00:00 bash
  58414 ?        00:00:00 sshd
  58417 ?        00:00:00 systemd
  58418 ?        00:00:00 (sd-pam)
  58440 ?        00:00:00 sshd
  58441 pts/3    00:00:00 bash
  58758 ?        00:00:00 sshd
  58761 ?        00:00:00 systemd
  58762 ?        00:00:00 (sd-pam)
  58784 ?        00:00:00 sshd
  58785 pts/1    00:00:00 bash
  58965 ?        00:00:00 sshd
  58975 ?        00:00:00 systemd
  58977 ?        00:00:00 (sd-pam)
  59000 ?        00:00:00 sshd
  59001 pts/5    00:00:00 bash
  59450 pts/2    00:00:00 ssh
  59451 ?        00:00:00 sshd
  59609 ?        00:00:00 sshd
  59610 pts/6    00:00:00 bash
  59754 ?        00:00:00 sshd
  59764 ?        00:00:00 systemd
  59766 ?        00:00:00 (sd-pam)
  59790 ?        00:00:00 sshd
  59791 pts/8    00:00:00 bash
  59872 ?        00:00:00 sshd
  60020 ?        00:00:00 sshd
  60034 ?        00:00:00 systemd
  60035 ?        00:00:00 (sd-pam)
  60057 ?        00:00:00 sshd
  60058 pts/10   00:00:00 bash
  60077 ?        00:00:00 systemd
  60079 ?        00:00:00 (sd-pam)
  60102 ?        00:00:00 sshd
  60105 pts/11   00:00:00 bash
  60700 ?        00:00:00 sshd
  60712 ?        00:00:00 systemd
  60713 ?        00:00:00 (sd-pam)
  60754 ?        00:00:00 sshd
  60757 pts/13   00:00:00 bash
  60878 ?        00:00:00 systemd
  60882 ?        00:00:00 (sd-pam)
  60917 ?        00:00:00 sshd
  60947 ?        00:00:00 sshd
  60948 pts/7    00:00:00 bash
  61103 ?        00:00:00 sshd
  61113 ?        00:00:00 systemd
  61115 ?        00:00:00 (sd-pam)
  61139 ?        00:00:00 sshd
  61140 pts/0    00:00:00 bash
  61310 ?        00:00:00 kworker/0:2-events
  61374 ?        00:00:00 kworker/u2:2-events_power_efficient
  61513 pts/7    00:00:00 cat
  61604 ?        00:00:00 sshd
  61670 ?        00:00:00 systemd
  61672 ?        00:00:00 (sd-pam)
  61694 ?        00:00:00 sshd
  61695 pts/15   00:00:00 bash
  61952 pts/7    00:00:00 scp
  61953 pts/7    00:00:00 ssh
  62004 ?        00:00:00 kworker/0:4-events
  62040 ?        00:00:00 sshd
  62049 ?        00:00:00 systemd
  62051 ?        00:00:00 (sd-pam)
  62076 ?        00:00:00 sshd
  62077 pts/16   00:00:00 bash
  62136 ?        00:00:00 sshd
  62140 ?        00:00:00 systemd
  62145 ?        00:00:00 (sd-pam)
  62167 ?        00:00:00 sshd
  62168 pts/4    00:00:00 bash
  62189 ?        00:00:00 sshd
  62240 ?        00:00:00 systemd
  62245 ?        00:00:00 (sd-pam)
  62282 ?        00:00:00 sshd
  62291 pts/14   00:00:00 bash
  62364 pts/7    00:00:00 scp
  62365 pts/7    00:00:00 ssh
  62368 pts/7    00:00:00 scp
  62369 pts/7    00:00:00 ssh
  62372 ?        00:00:00 sshd
  62381 ?        00:00:00 systemd
  62383 ?        00:00:00 (sd-pam)
  62409 pts/17   00:00:00 bash
  62436 ?        00:00:00 sshd
  62439 ?        00:00:00 systemd
  62440 ?        00:00:00 (sd-pam)
  62462 ?        00:00:00 sshd
  62463 pts/18   00:00:00 bash
  62472 pts/7    00:00:00 ssh
  62473 ?        00:00:00 sshd
  62508 ?        00:00:00 sshd
  62509 pts/19   00:00:00 bash
  62553 pts/19   00:00:00 man
  62564 pts/19   00:00:00 pager
  62573 pts/4    00:00:00 man
  62584 pts/4    00:00:00 pager
  62710 ?        00:00:00 sshd
  62741 ?        00:00:00 sshd
  62742 ?        00:00:00 bash
  62743 ?        00:00:00 sh
  62779 ?        00:00:00 kworker/u2:1-events_power_efficient
  62829 ?        00:00:00 kworker/0:0-events
  62895 pts/10   00:00:00 ps
m_pinchuk@vds2476450:~$ echo test.txt
test.txt
m_pinchuk@vds2476450:~$ sudo su
[sudo] password for m_pinchuk: 
m_pinchuk is not in the sudoers file.  This incident will be reported.
m_pinchuk@vds2476450:~$ ls
2  test.txt
m_pinchuk@vds2476450:~$ rm 2 -r
m_pinchuk@vds2476450:~$ ls
test.txt
m_pinchuk@vds2476450:~$ rm test.txt

┌──(utyfull㉿kali)-[~/Desktop]
└─$ tar cvf my_archive.tar code.md
code.md
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ ls
 code.md   git   Markdown_console_listening.md   Markdown_console_listening.txt   my_archive.tar  'New Folder'   otchet.md   python
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ ls my_archive.tar     
my_archive.tar
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ scp my_archive.tar m_pinchuk@185.5.249.140 /home/m_pinchuk
/home/m_pinchuk: No such file or directory
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ ssh m_pinchuk@185.5.249.140                               
Enter passphrase for key '/home/utyfull/.ssh/id_ed25519': 
Welcome to Ubuntu 20.04.6 LTS (GNU/Linux 5.4.0-162-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage
New release '22.04.3 LTS' available.
Run 'do-release-upgrade' to upgrade to it.

Last login: Mon Sep 18 10:51:08 2023 from 85.143.224.30
m_pinchuk@vds2476450:~$ ls
m_pinchuk@vds2476450:~$ cd /home
m_pinchuk@vds2476450:/home$ ls
a_bolotin  a_pereverzev  a_shiapov  d_kuleshov   d_shirshov  f_lerner    k_denisov    k_nikolskiy  mivallion  m_vlasko       n_gavrilov  n_radion     n_stepanov   v_frolov
a_ganyak   a_popov       d_jgenti   d_nurgaliev  e_fedorova  i_tatarkin  k_ismailova  m_hulagov    m_pinchuk  m_yavmetdinov  n_ivanov    n_soliviova  t_grigoriev  v_romanov
m_pinchuk@vds2476450:/home$ pwd
/home
m_pinchuk@vds2476450:/home$ exit
logout
Connection to 185.5.249.140 closed.
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ scp my_archive.tar m_pinchuk@185.5.249.140 /home/m_pinchuk/my_archive.tar
/home/m_pinchuk/my_archive.tar: No such file or directory
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ scp my_archive.tar m_pinchuk@185.5.249.140:/home/m_pinchuk               
Enter passphrase for key '/home/utyfull/.ssh/id_ed25519': 
my_archive.tar                                                                                                                                                                                           100%   10KB   1.0MB/s   00:00    
                                                                                                                                                                                                                                           
┌──(utyfull㉿kali)-[~/Desktop]
└─$ ssh m_pinchuk@185.5.249.140                               
Enter passphrase for key '/home/utyfull/.ssh/id_ed25519': 
Welcome to Ubuntu 20.04.6 LTS (GNU/Linux 5.4.0-162-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage
New release '22.04.3 LTS' available.
Run 'do-release-upgrade' to upgrade to it.

Last login: Mon Sep 18 11:29:45 2023 from 85.143.224.30
m_pinchuk@vds2476450:~$ ls
my_archive.tar
m_pinchuk@vds2476450:~$ ls     
my_archive.tar
m_pinchuk@vds2476450:~$ mkdir 1
m_pinchuk@vds2476450:~$ rmdir 1
m_pinchuk@vds2476450:~$ mkdir 2
m_pinchuk@vds2476450:~$ mv my_archive.tar /2   
mv: cannot move 'my_archive.tar' to '/2': Permission denied
m_pinchuk@vds2476450:~$ mv my_archive.tar /home/m_pinchuk/2
m_pinchuk@vds2476450:~$ cd 2
m_pinchuk@vds2476450:~/2$ ls
my_archive.tar
m_pinchuk@vds2476450:~/2$ tar xvf my_archive.tar
code.md
m_pinchuk@vds2476450:~/2$ ls
code.md  my_archive.tar
m_pinchuk@vds2476450:~/2$ rm my_archive.tar
m_pinchuk@vds2476450:~/2$ ls
code.md

```
