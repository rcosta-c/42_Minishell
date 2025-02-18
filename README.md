<div style="max-width:900px; margin:2rem auto; background:#fff; padding:2rem; box-shadow:0 0 10px rgba(0,0,0,0.1); border-radius:5px; font-family:Arial, sans-serif; color:#333;">
  <h1 style="color:#0056b3; text-align:center; font-size:2.5rem; margin-bottom:1rem;">Minishell</h1>
  <p>
    Minishell is a simplified Bash shell implementation designed to deepen your understanding of process management, file descriptors, user input handling, and more. This project demystifies how a shell operates behind the scenes—from parsing user commands to executing them—while also strengthening teamwork and communication skills in a collaborative environment.
  </p>

https://github.com/user-attachments/assets/e69826cc-063f-49a9-953d-b1e0100ae04f

  <h2 style="color:#0056b3; border-bottom:2px solid #0056b3; padding-bottom:0.3rem;">Project Overview</h2>
  <p>
    Minishell replicates the core functionality of the Bash shell on a reduced, but fully functional scale. Through this project, you will learn:
  </p>
  <ul>
    <li><strong>How shells parse and handle user input.</strong></li>
    <li><strong>Analyze the project in order to phase all the development work.</strong></li>
    <li><strong>The internal mechanisms for command execution and process management.</strong></li>
    <li><strong>Techniques for handling environment variables, pipes, and redirections.</strong></li>
  </ul>
  <p>
    This project not only reinforces technical programming skills but also emphasizes collaborative problem-solving and effective communication.
  </p>

  <h2 style="color:#0056b3; border-bottom:2px solid #0056b3; padding-bottom:0.3rem;">Core Components</h2>

  <h3 style="color:#0056b3;">1. Tokenizer</h3>
  <ul>
    <li>
      <strong>Tokenization</strong>: Splits user input into tokens using pipes (<code>|</code>) as delimiters, then further divides each segment by spaces while correctly handling quoted strings.
    </li>
    <li>
      <strong>Token Classification</strong>: Identifies and labels tokens as simple commands, arguments, built-ins, files, redirections, etc.
    </li>
  </ul>

  <h3 style="color:#0056b3;">2. Expander</h3>
  <ul>
    <li>
      <strong>Environment Variable Expansion</strong>: Scans tokens for the <code>$</code> symbol and replaces variables with their corresponding values from the local environment. If a variable is not found, it is replaced with an empty string.
    </li>
    <li>
      <strong>Quote Handling</strong>: Removes quotes from tokens according to specific rules, ensuring that arguments are interpreted correctly.
    </li>
  </ul>

  <h3 style="color:#0056b3;">3. Parser</h3>
  <ul>
    <li>
      <strong>Parser</strong>: It reads the tokens and "assembles" the commands to be executed. This assembly is easily performed due to the counters and flags that were provided by Tokenizer for each token.
    </li>
    <li>
      <strong>Redirects and error management</strong>: It manages the redirects at this stage, and makes an initial check if the existing command structure is correct to be executed.
    </li>
  </ul>

  <h3 style="color:#0056b3;">4. Executor</h3>
  <ul>
    <li>
      <strong>Command Assembly</strong>: Constructs arrays of strings (in a format accepted by <code>execve</code>) from the parsed tokens.
    </li>
    <li>
      <strong>Process Management</strong>:
      <ul>
        <li>Determines the number of processes based on the count of pipes.</li>
        <li>Creates child processes to handle commands when necessary.</li>
        <li>Executes built-in commands in the parent process when there is only one command and no piping.</li>
      </ul>
    </li>
    <li>
      <strong>Path Resolution</strong>: Searches the directories listed in the <code>PATH</code> environment variable to locate system executables.
    </li>
  </ul>

  <h2 style="color:#0056b3; border-bottom:2px solid #0056b3; padding-bottom:0.3rem;">Supported Features</h2>
  <ul>
    <li><strong>Prompt Display</strong>: Custom shell prompt interface.</li>
    <li><strong>Command History</strong>: Navigate through previous commands using the up and down arrow keys.</li>
    <li>
      <strong>Executable Commands</strong>:
      <ul>
        <li>System Executables (<code>ls</code>, <code>cat</code>, <code>grep</code>, etc.)</li>
        <li>Local Executables (<code>./minishell</code>)</li>
      </ul>
    </li>
    <li>
      <strong>Built-in Commands</strong>:
      <ul>
        <li><code>echo</code> (supports the <code>-n</code> option)</li>
        <li><code>cd</code> (accepts only a relative or absolute path)</li>
        <li><code>pwd</code> (without options)</li>
        <li><code>export</code> (without options)</li>
        <li><code>unset</code> (without options)</li>
        <li><code>env</code> (without options or arguments)</li>
        <li><code>exit</code> (accepts an exit number but no other options)</li>
      </ul>
    </li>
    <li>
      <strong>Pipes (<code>|</code>)</strong>: Redirects the output of one command to the input of another.
    </li>
    <li>
      <strong>Redirections</strong>:
      <ul>
        <li><code>&gt;</code>: Redirects output to a file.</li>
        <li><code>&gt;&gt;</code>: Appends output to a file.</li>
        <li><code>&lt;</code>: Redirects input from a file.</li>
        <li>
          <code>&lt;&lt; DELIMITER</code>: Prompts for user input until the delimiter is encountered; the collected input is then fed to the command and expanded if needed.(without being added to history).
        </li>
      </ul>
    </li>
    <li>
      <strong>Environment Variable Expansion</strong>: Supports variables (e.g., <code>$USER</code>, <code>$VAR</code>) and the special variable <code>$?</code>, which holds the exit status of the last executed foreground pipeline, and the special variable <code>$$</code> to check the PID.
    </li>
    <li>
      <strong>Signal Handling</strong>:
      <ul>
        <li><code>Ctrl+C</code>: Interrupts the current command and displays a new prompt.</li>
        <li><code>Ctrl+D</code>: Exits Minishell.</li>
        <li><code>Ctrl+\</code>: Ignored (no action taken).</li>
      </ul>
    </li>
  </ul>

  <h2 style="color:#0056b3; border-bottom:2px solid #0056b3; padding-bottom:0.3rem;">Conclusion</h2>
  <p>
    Minishell is a challenging but rewarding project that provides a deep dive into the inner workings of a shell, offering a hands-on approach to understanding these fundamental concepts.
  </p>
  <p>
  </p>
</div>

# Usage 

Clone the repository and cd into it:
```sh
git clone git@github.com:cde-paiv/42_Minishell.git
```

Build the program:
```sh
cd 42_minishell
make
```

Run the program:
```sh
./minishell
```

Feel free to explore, contribute, and enhance your understanding of shell programming with our Minishell!

# Tests

Some tests we think every Minishell should handle

non-builtins
```sh
uname
ifconfig
iwconfig
```

relative/absolute path
```sh
ls
ls -la
/bin/ls
/bin/ls -la
```

builtins (pwd, cd, env)
```sh
pwd
cd ..
pwd
cd 42_Minishell/src
pwd
cd ~
pwd 
cd 42_Minishell/src
cd 42_Minishell src
env
```

builtins (export, unset, exit)
```sh
export
export XX=42
echo $XX
unset XX
echo $XX
export XX=42
echo $XX
export XX+=99
echo $XX
export ZZ
echo $ZZ
export
unset ZZ
unset XX
exit 42 42
echo $?
./minishell
exit 42
echo $?
./minishell
exit 242
echo $?
```

builtins (echo)
```sh
echo Hello
echo Hello there
echo "hello there $USER"
echo 'hello there $USER'
echo '"hello there $USER"'
echo "'hello there $USER'"
echo "$USER $HOME hello" "hello there mate!" '$USER'
echo -n 'hello there $USER'
echo $$
echo $?
ls notexist
echo $?
```

redir's and pipes
```sh
ls -l | grep src | wc -l
ls -l > test1.txt
cat < test1.txt
cat test1.txt
ls -la >> test1.txt
cat test1.txt
cat < test1.txt | grep src
cat << end1 > out1.txt | cat << end2 > out2.txt | cat << end3 > out3.txt
history
rm -rf ./.history
history
unset PATH
ls
```
