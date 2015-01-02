function check_output {
  printf "\n--[ $1 ]--\n"
  output=$2
  ok_123=$3
  ok_singular=$4
  out_123=$(echo "$output" | grep after --after-context 8 | tail -n 3 | sed "s/ //g")
  out_singular=$(echo "$output" | grep ": singular matrix");
  if [ "$out_123" = "$ok_123" ]; then
    printf "[OK] "
  else
    printf "[WRONG] "
  fi
  echo "Solving random system with solution 1, 2, 3"
  if [ "$out_singular" = "$ok_singular" ]; then
    printf "[OK] "
  else
    printf "[WRONG] "
  fi
  echo "Failing with singular matrix"
}

ludcmp=$(unbuffer ./test_ludcmp 2>&1)
gaussj=$(unbuffer ./test_gaussj 2>&1)
gaussjbs=$(unbuffer ./test_gaussjbs 2>&1)

ok_123=$'1.000000\n2.000000\n3.000000'
ok_singular="ludcmp: singular matrix"
ok_singular2="gaussj: singular matrix"
ok_singular3="gaussjbs: singular matrix"

check_output "ludcmp" "$ludcmp" "$ok_123" "$ok_singular"
check_output "gaussj" "$gaussj" "$ok_123" "$ok_singular2"
check_output "gaussjbs" "$gaussjbs" "$ok_123" "$ok_singular3"
