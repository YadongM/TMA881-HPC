make clean
make all -B
hyperfine --time-unit millisecond --warmup 10 --max-runs 100 "./newton -l1000 -t1 7"
hyperfine --time-unit millisecond --warmup 10 --max-runs 100 "./newton -l1000 -t4 5"
hyperfine --time-unit millisecond --warmup 10 --max-runs 100 "./newton -l3000 -t10 7"
make clean