#!/bin/bash
#                                   ___
#                               ,-""   `.
#                             ,'  _   e )`-._
#                            /  ,' `-._<.===-'
#                           /  /
#                          /  ;
#              _.--.__    /   ;
# (`._    _.-""       "--'    |
# <_  `-""                     \
#  <`-                          :
#   (__   <__.                  ;
#     `-.   '-.__.      _.'    /
#        \      `-.__,-'    _,'
#         `._    ,    /__,-'
#            ""._\__,'< <____
#                 | |  `----.`.
#                 | |        \ `.
#                 ; |___      \-``
#                 \   --<
#                  `.`.<
#             	   `-'
# By ddemers@42

# Define an array of tests
tests=(
  "echo Bonjour"
  "pwd"
)

# compare the output of both #
for test in "${tests[@]}"; do
  # Run the test in Bash and capture the output using command substitution
  bash_output="$(bash -c "$test")"

  # Run the test in your C program and capture the output using command substitution
  c_program_output="$(./minishell "$test")"

  # Compare the output of Bash and your C program
  if [ "$bash_output" == "$c_program_output" ]; then
    echo "Test '$test' passed!"
  else
    echo "Test '$test' failed."
    echo "Expected output: $bash_output"
    echo "Minishell output: $c_program_output"
  fi
done