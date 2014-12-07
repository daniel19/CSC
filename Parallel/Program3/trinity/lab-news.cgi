<!-- HTML Generated Dynamically by J-Web 0.02 -->
<html>
<head><title>The Computer Science Department</title>
<!-- <base target="_blank"> -->
</head>
<body bgcolor="FFFFFF" text="#000000" link="#990000" vlink="#F1650E" alink="#8504F6" background=/IMAGES/pattern1.jpg>
<!--
<br><p><img src="/IMAGES/cs-bar2.gif" align=bottom alt="Trinity University Computer Science"></p><br>
<br><p><center><img src="/Pictures/TU_FS_CT_WEB.gif" align=bottom alt="Trinity University Computer Science"></p><h1>Computer Science</h1></center><br>
-->
<br><p><table><td><a href=http://www.trinity.edu><img src="/Pictures/TU_L_K.gif" align=bottom alt="Trinity University"
border=none></a></td><td><a href=http://www.cs.trinity.edu><img src=/Pictures/cs.gif alt="Trinity University Computer Science" border=none></a></td></table>
<a href=#2008.02.11> <h2>2008.02.11 Disk space quotas</h2></a>
<a href=#2006.09.15> <h2>2006.09.15 How to ensure the privacy of files in your home directory</h2></a>
<a href=#2006.09.14> <h2>2006.09.14 Engineering Student's access to Rex home directories</h2></a>
<a href=#2006.08.18> <h2>2006.08.18 OpenOffice Startup Problems</h2></a>
<a href=#2006.08.17> <h2>2006.08.17 Summer Lab Upgrades</h2></a>
<a href=#2005.01.26> <h2>2005.01.26 Missing Files When Logging into CS Department OS X Machines</h2></a>
<a href=#2004.09.23> <h2>2004.09.23 Gnome Login Problems (again)</h2></a>
<a href=#2004.09.09> <h2>2004.09.09 SSH Authentication</h2></a>
<a href=#2004.09.08> <h2>2004.09.08 Adding . to your Executable Path</h2></a>
<a href=#2004.09.02> <h2>2004.09.02 Reading Mail from the CS Mail Server</h2></a>
<a href=#2004.08.27> <h2>2004.08.27 Path Problems</h2></a>
<a href=#2004.08.18> <h2>2004.08.18 Summer Lab Upgrades</h2></a>
<a href=#2003.09.18> <h2>2003.09.18 Gnome Login Problems</h2></a>
<a href=#2003.09.17> <h2>2003.09.17 How to Report Problems</h2></a>
<a href=#2003.08.20> <h2>2003.08.20 Summer Lab Upgrades</h2></a>
<a href=#2002.09.09> <h2>2002.09.09 NFS File System Performance</h2></a>
<a href=#2002.08.30> <h2>2002.08.30 Summer Lab Upgrades</h2></a>
<a href=#2002.03.07> <h2>2002.02.07 Removing the Nimda Virus</h2></a>
<a href=#2002.01.27> <h2>2002.01.27 Password Cracking Again</h2></a>
<a href=#2002.01.15> <h2>2002.01.15 Firewall Access</h2></a>
<a href=#2002.01.14> <h2>2002.01.14 EXT3 Filesystems</h2></a>
<a href=#2002.01.03> <h2>2002.01.03 Sol Upgrade</h2></a>
<a href=#2001.12.11> <h2>2001.12.11 EXT3 Filesystem on Sol</h2></a>
<a href=#2001.11.26> <h2>2001.11.26 No Passwords Cracked!</h2></a>
<a href=#2001.11.24> <h2>2001.11.24 WEB Manual Pages</h2></a>
<a href=#2001.11.10> <h2>2001.11.10 Password Robot</h2></a>
<a href=#2001.08.29> <h2>2001.08.29 Summer Lab Upgrades</h2></a>

<a name=2008.02.11>
<font color=#00aa00><h1>2008.02.11</h1></font>
Disk space usage in users' home directories on Sol is subject to 
quotas.  If your usage exceeds your quota, you will (after a short
grace period) be unable to create new files.  This has been observed
to result in a number of baffling symptoms, including long delays
during login/logout.  You can find out your current
quota by typing <tt>quota</tt> at a command prompt.
We have also set up a system
whereby users who exceed their quotas will be notified by e-mail.
Users over quota should first try to identify and remove unneeded
files.  Two local commands, <tt>sorted-disk-usage</tt> and
<tt>find-big-files</tt> 
(both in <tt>/usr/local/bin</tt>), may help with this.
Read the commands (scripts) to see how to use them.
Users with a valid academic need for additional space can 
request a larger quota by contacting
<a href=mailto:csadmin@mail.cs.trinity.edu>CSAdmin-Group</a>.
<p>

<a name=2006.09.15>
<font color=#00aa00><h1>2006.09.15</h1></font>
Unix provides a file access security mechanism which may be used to implement 
almost any security policy.  The file access modes for the owner,group,public are
usually taught in PAD1.  We are all familiar with these RWX (Read Write eXecute) attributes for
each class of user (owner, group, and public).  We may be less familiar with the umask
command and what it provides.  The RWX attributes, coded as a 3 bit binary,
number give the following permissions:<p>
<pre>
RWX  Decimal  Permission   
000     0     no access
001     1     execute or cd to dir
010     2     write
011     3     write and execute or cd to dir
100     4     read
101     5     read and execute or cd to dir
110     6     read and write
111     7     read and write and execute or cd to dir
</pre>
Each of these permissions apply to and may be set for owner,group, and public using the chmod
command.  For example to set the permissions of the file <tt>foo</tt> so that the
owner can read and write, the group can read, but the public has no access,
enter the command:<p>
<pre>
chmod 640 foo
</pre>
<tt>chmod</tt> also supports symbolic modes; the equivalent of the 
preceding command would be:<p>
<pre>
chmod u=rwx foo
chmod g=rx foo
chmod o= foo
</pre>
The access permissions are automatically set whenever a program is run which creates
a file (e.g. <tt>cat > foo, mkdir, vi foo, cc, make</tt>, etc. ).  The resulting permissions
for owner, group, and public are determined according to the following equation

<pre>
7 - umask-value
</pre>
So umask provides an upper limit on file access permissions for the owner, group, and
public.<p>

The default umask used for new accounts is 077 which means that there are no restrictions
on the owner (the permissions could be as high as 7) and there are maximum restrictions
on group and public (7-7=0).  Any user can overide the default umask by setting
it in their .bash_profile file which is executed once for logon shells.  For example,<p>

<pre>
umask 022
</pre>

would allow permissions as high as 755 for owner, group, and public respectively.
In addition to a umask of 077 for new accounts, we set the permissions of the
home directory to be 755 and the permissions of ~/Local to 755 and ~/Local/HTML-Documents to
755 so that users may set up web sites on their accounts without permissions changes.<p>

However, if a more secure umask of 077 is used, then users will have to use chmod after creating web
files to change the permissions to 644 (for web pages) and 755 (for web directories) as the
web server will not serve pages with lesser permissions.<p>

<font color=#770000><h3>IMPORTANT NOTE:</h3></font> When the new FC5 software was installed on
the CS lab machines in August 2006, a system default umask of 002 was configured rather
than the more secure umask of 077.  This mistake will be fixed shortly, however,
users who are concerned about the public readability of their newly created files
may install their own more secure default umask by executing the following command:<p>
<pre>
echo "umask 077" >> ~/.bashrc
</pre>

This command adds a line of<p>
<pre>
umask 077
</pre>
to the <tt> ~/.bashrc </tt> file.  The <tt> ~/.bashrc </tt> is executed before
a new shell is created (i.e. before any command is executed).<p>
<a name=2006.09.14>
<font color=#00aa00><h1>2006.09.14</h1></font>
<p ><h2>Things Engineering students need to know about their new (CS/ENGR) Linux accounts</h2></p>
<p>We have replaced the Sun Workstations and several Linux boxes with a mostly dual-boot system (XP and Linux).
The Linux side provides storage space for users and a host of other facilities and applications. 
The server is shared with Computer Science as is the storage space.
Most of the unique "engineering" software is on the client computers in Moody
and may not be present on CS lab computers.</p>
<p>You have a mail account with the CS/ENGR system if you want to use it.
You have a quota of 200MB (currently) of storage.  The quota will increase when we install
a new server and supporting facilities.
You have space for Web pages.  As the semester progresses, we will provide more detail.</p>
<p><h3>Engineering students who had CS accounts before the Fall:</h3></p>
<ol>
  <li>If you previously had a CS account,
it is still there, but any materials that you had in Engineering Science
UNIX (Rex.Engr.Trinity.Edu) and Linux home directories are at:
<pre>
/users/engrold/your_user_name
</pre>
and at
<pre>
/users/engrold/linuxhome/your_user_name.
</pre>
where <tt>your_user_name</tt> is your TU username.</li>
  <li>Your password is your CS password (i.e. it
has not been changed for most users).</li>
  <li>Move anything you need to keep from your
ENGR UNIX and Linux directories to your CS/ENGR home directory BY THE END OF THE YEAR.
 After that, it will be lost. Do NOT copy, but MOVE, since copying will take up twice the
storage space as moving. Do not move everything, but only what you know you need (e.g. no *.* moves).
Do not move the whole home directory, just those things under it that you need.</li>
</ol>
<p><h3>Engineering students who did not have CS accounts before the Fall:</h3></p>
<ol>
  <li>You have been sent an email that indicates your username and an initial password on the CS/ENGR Linux system.</li>
  <li>If you had anything in Engineering Science
UNIX and Linux accounts last year, you can get to it as described above.
MOVE things you want to keep as described above.</li>
</ol>
<p>One more thing.  Previously, engineering students running Windows saw an X: drive that
was mapped to their UNIX home space on rex.  That mapping may still be in place for some of you.  Please do not
use it, as we do NOT plan any further backup of the UNIX users file system.  Sometime soon, we will add the
(new) Linux home directory to your mapped drives as X: .</p>
<a name=2006.08.18>
<font color=#00aa00><h1>2006.08.18</h1></font>
If you have used the version of OpenOffice installed last year on
on our FC4 lab machines, OpenOffice on one of the upgraded (Fedora Core 5)
machines may hang on startup.  The easiest fix is to remove the
configuration-files directory <tt>.openoffice.org2.0</tt>, thus:

<pre>
rm -rf ~/.openoffice.org2.0
</pre>

and try the application again, letting it recreate the directory.
(Obviously this loses any customizations.)  Experiment suggests
that the older version of OpenOffice will be able to use the
<tt>.openoffice.org2.0</tt> directory created by the newer version,
so it should be possible to use both versions (e.g., the old one on
a not-yet-upgraded desktop machine and the new one on a lab machine).
<p>
<a name=2006.08.17>
<font color=#00aa00><h1>2006.08.17</h1></font>
During the Summer 2006 break, new Linux and Windows XP images were
prepared and installed on the XenaXX machines in Halsell 340, JanusXX
machines in Halsell 228, AtlasXX machines in Halsell 329 and the various
machines in Halsell 200.  The Linux images are based on Fedora Core 5.  FC5
distributions are packaged differently than earlier Fedora Core systems we
have used.  The Sysadmin Group has attempted to install updated versions
of all of the packages we have used in the past, but due to different package
setup we may have missed something you feel is important.  If you identify
missing software, please let us know by sending mail to 
<a href=http://CSAdmin@Mail.CS.Trinity.Edu>CSAdmin@Mail.CS.Trinity.Edu</a>.
<p>
Please remember our Lab Policy of re-booting a machine into Linux after
using Windows XP.  The XenaXX machines in Halsell 340 and the various machines
in Halsell 200 are Linux only and should never be rebooted or powered down.
Most of these machines are in use remotely even while you are sitting at
the console, so you will probably be destroying someone else's session by
rebooting or powering down.  The JanusXX machines in Halsell 228 and the
AtlasXX machines in Halsell 329 are dual boot.  You must reboot these machines
to Linux after using Windows XP.

<a name=2005.01.26>
<font color=#00aa00><h1>2005.01.26</h1></font>
If you receive error messages similar to the following
<pre>
-bash: /users/userid/Local/powerpc/bash/shell/*.path: No such file or directory
-bash: /users/userid/Local/powerpc/bash/shell/*.env: No such file or directory
-bash: /users/userid/Local/powerpc/bash/shell/*.alias: No such file or directory
</pre>

where <tt>userid</tt> is your login id when logging into CS Department OS X
machines, then your

<pre>
Local/powerpc
</pre>

filesystem is missing a <tt>bash</tt> subdirectory.  You can fix this problem by downloading
the <a href=http://www.cs.trinity.edu/bash.tgz> bash.tgz </a> file system and saving
that file in your

<pre>
Local/powerpc
</pre>

directory and executing the following commands

<pre>
cd ~/Local/powerpc
tar xzvf bash.tgz
rm bash.tgz
</pre>
<a name=2004.09.23>
<font color=#00aa00><h1>2004.09.23</h1></font>
The upgrade to Fedora Core 2 on all Computer Science Linux workstations was
not completed during the summer as planned.  As a result,
because of incompatibilities between Gnome versions in
RedHat 7.3, RedHat 9 and Fedora Core 2, there can be difficulties logging
into a Fedora Core 2 system after logging into a RedHat 7.3 or a RedHat 9
system and visa-versa.  The systems in HAS 340, HAS 329 and HAS 228
(Xena, Atlas and Janus machines) have all been converted to
Fedora Core 2.  Upgrades of the remaining machines is in progress and should
be completed soon.  The 
Dwarf, Juliet, Charon, Bianca Miranda in HAS 200 and a few other isolated
machines or faculty workstations have not
yet been upgraded.  You can check the upgrade status of a workstation by noting
the date on the login screen.  Fedora Core 2 machines have an August 2004 date,
RedHat 9 machines have an August 2003 date and RedHat 7.3 machines have an
August 2002 date.
<p>
Users may avoid this problem by not logging into the RedHat 7.3 or RedHat 9 machines
after having converted their Gnome directories to Fedora Core 2. If you must
login to RedHat 7.3 or RedHat 9 machines you can perform the following procedure
before logging in (this procedure will reset your Gnome desktop to its
default configuration).<p>
1) login to a console text session at the machine (press ctrl-alt-F1 to get a text console; pressing
ctrl-alt-F7 will return you to the X11 graphical login screen after performing the steps below and
logging out).<p>

2) You should be at the top-level of your home directory before
performing this procedure.  Enter the following command (BE CAREFUL to type this command correctly!
To avoid errors, copy the command from your browser window and paste into
your terminal window.):

<pre>
rm  -r  .gno*  .gcon*  .nautilus*  .metacity  .gtkrc*
</pre>

3) logout and press ctrl-alt-F7 to return to the graphical X11 login screen.<p>

To remove the possibility of typing errors in step 2) above,
we have added the command:

<pre>
gnome-cleanup
</pre>

which may be used in place of the command outlined in step 2).
<a name=2004.09.09>
<font color=#00aa00><h1>2004.09.09</h1></font>
Some CS Department Unix users have asked how to configure SSH so that they
can safely log into CS Unix machines without entering a password.
Daniel Robbins (<a href=mailto:drobbins@gentoo.org>President and CEO, Gentoo Technologies, Inc.</a>)
has written a 3 part article on OpenSSH key management (
<a href=http://www-106.ibm.com/developerworks/linux/library/l-keyc.html>Part1</a> ,
<a href=http://www-106.ibm.com/developerworks/library/l-keyc2/>Part2</a> ,
<a href=http://www-106.ibm.com/developerworks/linux/library/l-keyc3/>Part3</a> )
which explains how to do this.<p>
Also available is an 
<a href=http://www.gentoo.org/proj/en/keychain/index.xml> article </a> on OpenSSH Keychain.
<p>
Or, if you are too impatient to wade through the details and theory, try this
<a href="http://www.cs.trinity.edu/~knickels/howto/#ssh">short how-to</a> written by 
Dr.&nbsp;Nickels in the Engineering Science department.
Notice that the directory <tt>$HOME/.ssh</tt> should
<i>not</i> be world-readable!
<p>
<a name=2004.09.08>
<font color=#00aa00><h1>2004.09.08</h1></font>
It was recently discovered that new accounts (those which were
added after the end of the Spring 2004 Semester) do not have <tt>.</tt>
in their path (symptom: not being able to
execute programs in the working directory unless
proceeded by <tt>./</tt> ). 

If your account has this problem, you should
edit the file <tt>.bash_profile</tt> in the top level of your home
directory so that the line

<pre>
PATH=$PATH:$HOME/bin
</pre>

is changed to

<pre>
PATH=$PATH:$HOME/bin:.
</pre>

The next time you log in, <tt>.</tt> will be at the end of the path.
To add <tt>.</tt> to the path for the current session (the one where
the <tt>.bash_profile</tt> is edited) simply source the <tt>.bash_profile</tt> file,
i.e.,

<pre>
. .bash_profile
</pre>
<p>
<a name=2004.09.02>
<font color=#00aa00><h1>2004.09.02</h1></font>
The Computer Science Department runs a sendmail based mail server,
<tt>Mail.CS.Trinity.Edu</tt> (aka <tt>WWW.CS.Trinity.Edu</tt> or <tt>FTP.CS.Trinity.Edu</tt> or <tt>Sol.CS.Trinity.Edu</tt>).
This server supports POP3 and IMAP access with and without SSL service.
If you choose to have <tt>Mail.CS.Trinity.Edu</tt> provide your mail, then your e-mail
address will be <tt>userid@cs.trinity.edu</tt> rather than <tt>userid@trinity.edu</tt> .
If you decide to use <tt>Mail.CS.Trinity.Edu</tt>, then you should contact ITS and
have them setup a mail forwarding entry so that mail addressed to 
<tt>userid@trinity.edu</tt> will be forwarded to <tt>userid@cs.trinity.edu</tt> so that
all of your mail may be read from a single mail setup.<p>
Advantages of using the CS mail system include:<p>
<menu>
a) No limit on mail message size
</menu>
<menu>
b) No limit on attachement size (attachments will not be
removed from mail messages).
</menu>
<menu>
c) User configurable and trainable spam processing.
</menu>
The CS mail system supports two types of spam processing systems, Spamassassin
and SpamBayes.  Documentation is available on setting up
<a href=spamassassin.cgi>spamassassin</a> or <a href=spambayes.cgi>spambayes</a>.
Further assistance may be obtained by contacting <a href=mailto:csadmin@mail.cs.trinity.edu>CSAdmin-Group</a>.
<a name=2004.08.27>
<font color=#00aa00><h1>2004.08.27</h1></font>
<a name=2004.08.18>
Recently, it was discovered that CS Unix accounts which were
added to our system after December 2003 did not have a proper
execution path for all available programs.  You can test whether
or not your account has this problem by trying the command
<pre>
java
</pre>
If the java interpreter cannot be found then you need to add
a missing line to your <tt>.bash_profile</tt> file.  The line to
add is:
<pre>
source ~defaults/system/SYSTEM.bashrc
</pre>
This line should be added after the line
<pre>
# User specific environment and startup programs
</pre>
<font color=#00aa00><h1>2004.08.18</h1></font>
During the summer of 2004, new Linux images (based on Fedora Core 2)
and Windows XP images were created and installed on most lab machines
in HAS 329, HAS 340 and HAS 200.<p>
The Unix lab machines (Xena00-Xena21), with the possible exception of
the instructor's machine Xena00, are available, via the network,
24 hours per day, 7 days per week.
Most of the
software we add to the RedHat Linux or the Trinity University
licensed Microsoft software is available from
<a href=ftp://ftp.cs.trinity.edu/pub/FC2-Software-Additions/>ftp://ftp.cs.trinity.edu/pub/FC2-Software-Additions/</a>
and <a href=ftp://ftp.cs.trinity.edu/pub/winxp-software/>ftp://ftp.cs.trinity.edu/pub/winxp-software/</a> respectively.  Students may use the consoles
of the XenaXX machines during normal Halsell building hours whenever
HAS 340 is not in use by a class.<p>
<a name=2003.09.18>
<font color=#00aa00><h1>2003.09.18</h1></font>
The upgrade to RedHat 9 on all Computer Science Linux workstations was
not completed during the summer as planned.  As a result,
because of incompatibilities between Gnome versions in
RedHat 7.3 and RedHat 9, there can be difficulties logging
into a RedHat 9 system after logging into a RedHat 7.3
system and visa-versa.  The systems in HAS 340 and HAS 228
(Janus and Xena machines) have all been converted to
RedHat 9.  The Atlas machines in HAS 329 and
Dwarf, Hardy, Juliet, Charon, Bianca in HAS 200 have not
yet been upgraded.  You can check the upgrade status by
searching for one of the above machines in the
<a href=http://www.cs.trinity.edu/~jhowland/local-only/sysadmin/sysadmin-entire.cgi>Sysadmin Database</a>.
If the search results in records containing <tt>wwww</tt>, then that machine is not yet converted.

Users may avoid this problem by not logging into the RedHat 7.3 machines
after having converted their Gnome directories to RedHat 9. If you must
login to RedHat 7.3 machines you can perform the following procedure
before logging in (this procedure will reset your Gnome desktop to its
default configuration). <p>
1) login to a console text session at the machine (press ctrl-alt-F1 to get a text console; pressing
ctrl-alt-F7 will return you to the X11 graphical login screen after performing the steps below and
logging out).<p>

2) You should be at the top-level of your home directory before
performing this procedure.  Enter the following command (BE CAREFUL to type this command correctly!):

<pre>
rm  -r  .gno*  .gcon*  .nautilus .metacity
</pre>

3) logout and press ctrl-alt-F7 to return to the graphical X11 login screen.<p>
<a name=2003.09.17>
<font color=#00aa00><h1>2003.09.17</h1></font>
If you notice a problem with lab machines, printers
or software on any of the machines in HAS 200, 228, 329 or 340,
please send an email message detailing the problem to
<a href=mailto:csadmin@mail.cs.trinity.edu>csadmin@mail.cs.trinity.edu</a>.
Your help in reporting problems is greatly appreciated.  Sometimes problems
go unreported for a surprising length of time.  We can't fix it
if we don't know it is broken.<p>
<a name=2003.08.20>
<font color=#00aa00><h1>2003.08.20</h1></font>
During the summer, new Linux images (based on RedHat 9.0)
and Windows XP images were created and installed on most
lab machines in HAS 329, HAS 340, and HAS 200.  In addition,
the lab computers in HAS 340 (Unix Lab) were upgraded to
2.4Ghz Pentium IV processors, 512Mb memory and 40Gb disk drives.
The Unix lab machines (Xena00-Xena21), with the possible exception of
the instructor's machine Xena00, are available, via the network,
24 hours per day, 7 days per week.
Most of the
software we add to the RedHat Linux or the Trinity University
licensed Microsoft software is available from
<a href=ftp://ftp.cs.trinity.edu/pub/RedHat9-Software-Additions/>ftp://ftp.cs.trinity.edu/pub/RedHat9-Software-Additions/</a>
and <a href=ftp://ftp.cs.trinity.edu/pub/winxp-software/>ftp://ftp.cs.trinity.edu/pub/winxp-software/</a> respectively.  Students may use the consoles
of the XenaXX machines during normal Halsell building hours whenever
HAS 340 is not in use by a class.<p>
Other lab upgrades include a new 4 processor (2.4Ghz Xeon), 2Gb
memory, 265Gb disk (Raid 5) replacement machine for Sol.  The new Sol
machine is currently being configured and tested concurrent with
operation of the old Sol.  It is anticipated that the new Sol will become fully
operational early in the semester.  Since Sol functions as our primary
server for NIS (passwords), NFS (home directories), HTTP (web - WWW.CS.Trinity.Edu),
FTP, SMB (windows file sharing), DNS (name resolution) and SMTP (mail),
it is important that extensive testing be completed before making the
machine fully operational.  Users will be notified when the switch-over
occurs and if all goes well, the only anticipated inconvenience will be
a short period of down time while user's home directories and mail files are copied
to the new machine.  One feature, in addition to significantly
improved performance, of the new Sol will include
improved spam filtering of incoming mail.
<a name=2002.09.09>
<font color=#00aa00><h1>2002.09.09</h1></font>
After the upgrade of Sol.CS.Trinity.Edu from RedHat 7.1 to 7.3 we
have begun to notice a degradation of NFS file system (user home
directories) performance on client workstations.  This problem
has been recently (2002.10.21) traced to os kernel context switching problems
which are related to the journaling EXT3 file system used on Sol.
On 2002.10.25 (Fall Break) Sol will be down for a few minutes
on Friday morning (2002.10.25) to install a newer kernel.  If
this does not improve performance, then Sol will be down for a few hours,
at a date to be announced later, to allow
conversion of its file system back to EXT2.  If file system performance
improves, then an EXT2 filesystem will be used until this kernel
performance issue can be resolved.  This is the first re-boot of Sol
this year and the Sysadmin staff apologizes for any inconvenience
resulting from this change.
<a name=2002.08.30>
<font color=#00aa00><h1>2002.08.30</h1></font>
During the summer, new versions of RedHat 7.3 Linux and Windows 2000
were installed on Computer Science Department lab machines. Most of the
software we add to the RedHat Linux or the Trinity University
licensed Microsoft software is available from
<a href=ftp://ftp.cs.trinity.edu/pub/Other-RedHat-RPMS/>ftp://ftp.cs.trinity.edu/pub/Other-RedHat-RPMS/</a>
and <a href=ftp://ftp.cs.trinity.edu/pub/w2k-software/>ftp://ftp.cs.trinity.edu/pub/w2k-software/</a> respectively.<p>
The machines in the <a href=http://www.cs.trinity.edu/About/The_Facilities/ws.lab.cgi>
Workstation Laboratory</a> (HAS 228) are dual-boot (Linux and Windows 2000) machines.
The computers in the
<a href=http://www.cs.trinity.edu/About/The_Facilities/unix.lab.cgi> UNIX Laboratory</a>
(HAS 340) are now <b> Linux only </b> machines.  There are a few rules which
<b>must</b> be followed when using these machines.  First, after using Windows 2000,
reboot the machine to Linux.  There are users who wish to use these machines remotely
or who need to use the machines as a parallel processing cluster.  Second, <b>never</b>
reboot a machine by pressing the reset button.  Always use the reboot option which is
available from the pop-up menu on either the Linux login screen or the Windows 2000
login screen.  Third, never turn off these lab machines or their monitors (both
Linux and Windows 2000 will put the monitor in power-save mode after a short time).<p>
To improve system security, remote login access to these Unix machines is restriced
to secure shell (ssh).  To access Computer Science Department Unix/Linux machines from
Windows, you must install a ssh client program such as 
<a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Putty/053b/putty.exe><tt>putty</tt></a>.  
<tt>putty.exe</tt> is a single program which may be saved anywhere on your
Windows filesystem.  When you run <tt>putty</tt>, be sure to select the
ssh option.  Additional <a href=http://www.cs.trinity.edu/~bmassing/Misc/remote-access.html>
instructions </a> for secure shell access have been written by Dr. Massingill.<P>
Another way to provide secure shell capability for a Windows computer is
to install <a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Cygwin/setup.exe>cygwin</a>.
The cygwin system provides much more than secure shell client capability and requires
more than 200MB of disk space.  cygwin <a href=http://www.cygwin.com/> features</a> include
all of the <a href=http://www.gnu.org/>GNU</a> program development tools for developing
both Win32 and Unix applications under Windows.  An XWindows capablility is now
available for cygwin and the Computer Science Department cygwin
<a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Cygwin/setup.exe>package</a> includes
the X11 software.<p>
<a name=2002.03.07>
<font color=#00aa00><h1>2002.03.07</h1></font>
The Computer Science Department NIS/NFS/FTP/WEB/MAIL server can
also be used as a Windows File Server (via Samba).  You access
this server by finding the Cs domain and double clicking on
the Sol machine.  If your windows machine is infected with the Nimda
virus, your Unix home directory can also be infected with this
virus.  When this happens, you should follow
Dr. Semmes <a href=http://www.cs.trinity.edu/NimdaSOL.pdf> instructions(PDF) </a>
for removing the Nimda virus from your Unix home directory.
<a name=2002.01.27>
<font color=#00aa00><h1>2002.01.27</h1></font>
The Password cracking robot found 4 passwords which were crackable this weekend.
These passwords have been changed and the users have been notified.
Lab users, particularly new users, are encouraged to choose good passwords.
You should read the <a href=http://www.cs.trinity.edu/About/The_Courses/passwd.cgi>
instructions </a> for choosing a password.<p> 
<a name=2002.01.15>
<font color=#00aa00><h1>2002.01.15</h1></font>
The University controls access to the Trinity.Edu network (131.194.) by
various firewall machines.  The Computer Science Department provides
access to Trinity.Edu through its firewall machine Bianca.CS.Trinity.Edu .
Computer Science will configure access to Trinity.Edu through Bianca
for CS Faculty, Staff and CS Majors from other networks if the user
can provide a single ip-number from which the access will be made.
Most ISP's use DHCP to assign ip-numbers to customers.  Since customers
use a variety of different machines and operating systems and often these
systems are hidden behind the customer's own router or firewall, it is
often difficult for a user to easily determine the ip-number which is
provided by the ISP.  To simplify this problem the CS Department provides
a URL <a href=http://www.cs.trinity.edu/ip-no.cgi> http://www.cs.trinity.edu/ip-no.cgi </a> which, when
accessed, will determine a user's remote ip-number.  Use this facility
when requesting <a href=mailto:jhowland@ariel.cs.trinity.edu> access </a>
to the Trinity.Edu network through Bianca.CS.Trinity.Edu .<p>

There is also a new URL <a href=http://www.cs.trinity.edu/nslookup.cgi>
http://www.cs.trinity.edu/nslookup.cgi</a> which may be used to
lookup ip-numbers or ip-names in the DNS database.<p>

Finally, there is a new URL <a href=http://www.cs.trinity.edu/whois.cgi>
http://www.cs.trinity.edu/whois.cgi</a> which may be used to lookup
DNS domain names in the whois database.<p>
<a name=2002.01.14>
<font color=#00aa00><h1>2002.01.14</h1></font>
EXT3 journaling filesystems were installed today on the JanusXX, XenaXX, DwarfX, SnowWhite
and AtlasX Linux machines.  We expect to see improved reliability as
a result of this change.  Please report any problems to
<a href=mailto:jhowland@ariel.cs.trinity.edu> Dr. Howland</a>.<p>
<a name=2002.01.03>
<font color=#00aa00><h1>2002.01.03</h1></font>
Two new SCSI Drives were added to the Raid 5 array on Sol.CS.Trinity.Edu
increasing the disk space on Sol to more than 84G bytes.  The swap file
size was also increased to 2G bytes.  These changes should improve
Sol's ability to handle special user's space needs.  This work was performed
by John Howland with assistance from Aaron Konstam.  The procedure
required complete re-formatting of the disk array after installing
the new drives.  The system was then restored from backup images
mantained on another machine.<p>
Users should note that a very conservative restoration procedure was
used to recover each user's home directory from several recent backup
images.  The end result of this procedure is that the most recent
version of each user's file has been restored, however some files
which users recently deleted have also been restored.  Each user
is encouraged to look at their files and delete all files which are
no longer needed.<p> 
<a name=2001.12.11>
<font color=#00aa00><h1>2001.12.11</h1></font>
A journaling EXT3 filesystem was installed on Sol.CS.Trinity.Edu by
John Howland with assistance from Aaron Konstam and Neal Pape.  This
change will improve system restart speed in the rare event (hasn't
happened in more than a year) when a hard restart is required.  System
reliability should also be improved.<p>
<a name=2001.11.26>
<font color=#00aa00><h1>2001.11.26</h1></font>
Congratulations to users of the CS Unix machines!.  Our passwd cracking
robot found no crackable passwords this week.<p>
<a name=2001.11.24>
<font color=#00aa00><h1>2001.11.24</h1></font>
A web system for viewing man pages for software installed on our
lab machines is now available at
<a href=http://www.cs.trinity.edu/cgi-bin/man/man2html> http://www.cs.trinity.edu/cgi-bin/man/man2html </a><p>
<a name=2001.11.10>
<font color=#00aa00><h1>2001.11.10</h1></font>
On the weekend of November 10, 2001, the Computer Science Department sysadmin
staff began regular operation of systems which detect weak passwords.  You
may receive a message which indicates that your passwd is crackable.  The
standard procedure will be to automatically change your password to one which
is more secure.  You may <a href=http://www.cs.trinity.edu/About/The_Courses/passwd.cgi>
change</a> this password using
the<a href="http://www.cs.trinity.edu/cgi-bin/man/man2html?1+yppasswd"> <tt>yppasswd</tt> </a>
command.<p>
<a name=2001.08.29>
<font color=#00aa00><h1>2001.08.29</h1></font>
During the summer, new versions of RedHat 7.1 Linux and Windows 2000
were installed on Computer Science Department lab machines. Most of the
software we add to the RedHat Linux or the Trinity University
licensed Microsoft software is available from
<a href=ftp://ftp.cs.trinity.edu/pub/Other-RedHat-RPMS/>ftp://ftp.cs.trinity.edu/pub/Other-RedHat-RPMS/</a>
and <a href=ftp://ftp.cs.trinity.edu/pub/w2k-software/>ftp://ftp.cs.trinity.edu/pub/w2k-software/</a> respectively.<p>
The machines in the <a href=http://www.cs.trinity.edu/About/The_Facilities/ws.lab.cgi>
Workstation Laboratory</a> (HAS 228) and the
<a href=http://www.cs.trinity.edu/About/The_Facilities/unix.lab.cgi> UNIX Laboratory</a>
(HAS 340) are dual-boot (Linux and Windows 2000) machines.  There are a few rules which
<b>must</b> be followed when using these machines.  First, after using Windows 2000,
reboot the machine to Linux.  There are users who wish to use these machines remotely
or who need to use the machines as a parallel processing cluster.  Second, <b>never</b>
reboot a machine by pressing the reset button.  Always use the reboot option which is
available from the pop-up menu on either the Linux login screen or the Windows 2000
login screen.  Third, never turn off these lab machines or their monitors (both
Linux and Windows 2000 will put the monitor in power-save mode after a short time).<p>
To improve system security, remote login access to these Unix machines is restriced
to secure shell (ssh).  To access Computer Science Department Unix/Linux machines from
Windows, you must install a ssh client program such as 
<a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Putty/053b/putty.exe><tt>putty</tt></a>.  
<tt>putty.exe</tt> is a single program which may be saved anywhere on your
Windows filesystem.  When you run <tt>putty</tt>, be sure to select the
ssh option.  Additional <a href=http://www.cs.trinity.edu/~bmassing/Misc/remote-access.html>
instructions </a> for secure shell access have been written by Dr. Massingill.<P>
Another way to provide secure shell capability for a Windows computer is
to install <a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Cygwin/setup.exe>cygwin</a>.
The cygwin system provides much more than secure shell client capability and requires
more than 200MB of disk space.  cygwin <a href=http://www.cygwin.com/> features</a> include
all of the <a href=http://www.gnu.org/>GNU</a> program development tools for developing
both Win32 and Unix applications under Windows.  An XWindows capablility is now
available for cygwin and the Computer Science Department cygwin
<a href=http://www.cs.trinity.edu/ftp/pub/winxp-software/Cygwin/setup.exe>package</a> includes
the X11 software.<p>
<hr><table>
<!--
<td align=center width=5%> <img src=/Pictures/tu-seal.gif></td>
<td align=center width=5%> <img src=/Pictures/TU_FS_WEB.gif></td>
-->
<td align=center width=5%> <a href=http://www.trinity.edu><img src=/Pictures/TU_FS_CT_WEB_small.gif alt="Trinity University" border=none></a></td>
<td align=left width=35%>
<p><a href=/site-index.cgi> Site Index</a><br>
<a href="mailto:webmaster@www.cs.trinity.edu">Comments or Suggestions</a><br>
<a href=http://www.cs.trinity.edu>Computer Science Department</a><br>
<a href=http://www.trinity.edu>Trinity University</a><br>
<a href=http://www.trinity.edu/departments/public_relations/tour/map/color_campus_map.pdf>One Trinity Place</a><br>
<a href=http://www.mysa.com/>San Antonio, Texas</a>  78212-7200<br>
voice:  (210) 999-7480<br>
fax:  (210) 999-7477<p>
</td>
<!--
<td align=right> <a href=http://www.google.com/search?q=site%3Awww.cs.trinity.edu&hl=en&num=10&lr=&ft=i&cr=&safe=images&tbs=#sclient=psy&hl=en&lr=&q=site:www.cs.trinity.edu&aq=f&aqi=&aql=&oq=&pbx=1&bav=on.2,or.&fp=ef34c9a9ed856910><img src=/Pictures/google.gif alt="google site search" width=69 height=27 border=none></a>
-->
<td align=right> <a href=http://www.google.com/search?q=site%3Awww.cs.trinity.edu&hl=en&num=10&lr=&ft=i&cr=&safe=images&tbs=#sclient=psy&hl=en&lr=&q=site:www.cs.trinity.edu&aq=f&aqi=&aql=&oq=&pbx=1&bav=on.2,or.&fp=ef34c9a9ed856910><img src=/Pictures/google.gif alt="Trinity google site search" width=69 height=27 border=none></a>
<br><a href=https://www.cs.trinity.edu/webmail/>CS WebMail</a>
<br><a href=http://www.cs.trinity.edu/mailman/listinfo/>CS ListServer</a></td>
</table></body></html>
