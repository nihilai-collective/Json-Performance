
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2567.68 | 0.0267766 | 2824ms | 56369 | 4890 | 153681 | 20936.3 | 0.0962879 | 1.98829 | 8.9343 | 1.73788 | 0.00256562 | 2.58304e-05 | 1.65322e-05 | 1(Win) | true |
| Glaze | 2041.7 | 0.0360695 | 3368.15ms | 56369 | 4890 | 441049 | 26329.8 | 0.145662 | 2.50722 | 11.1974 | 2.27331 | 0.00641168 | 2.33634e-05 | 1.36879e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1835.09 | 0.0199434 | 3653.95ms | 56369 | 4890 | 166907 | 29294.3 | 0.0114608 | 2.7877 | 12.8619 | 2.22999 | 0.00377463 | 2.62258e-05 | 1.75697e-05 | 3(Loss) | true |
| simdjson (reflection) | 1615.77 | 0.207428 | 4063.17ms | 56369 | 30 | 142883 | 33270.7 | 0.148059 | 3.18061 | 13.5965 | 2.31319 | 0.00408972 | 2.6019e-05 | 1.18268e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1344.7 | 0.0378835 | 4738.37ms | 56369 | 2560 | 587178 | 39977.4 | 0.220135 | 3.80462 | 15.0594 | 2.75152 | 0.00896604 | 2.55155e-05 | 1.62642e-05 | 5(Loss) | true |
