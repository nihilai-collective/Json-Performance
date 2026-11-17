
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1955.62 | 0.173689 | 6056.86ms | 466906 | 80 | 1.2512e+07 | 227691 | 0.0309699 | 1.2658 | 1(Win) | true |
| Jsonifier (two-stage) | 1768.03 | 0.192253 | 6627.08ms | 466906 | 160 | 3.75099e+07 | 251849 | 0.0291136 | 1.40013 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1656.06 | 0.24251 | 6903.14ms | 466906 | 40 | 1.70069e+07 | 268877 | 0.180274 | 1.4948 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1642.68 | 0.356469 | 6952.03ms | 466906 | 40 | 3.73472e+07 | 271068 | 0.1833 | 1.50696 | 3(Tie) | true |
| simdjson (ondemand) | 986.881 | 0.200628 | 5789.53ms | 466906 | 80 | 6.55545e+07 | 451195 | 0.0565483 | 2.50852 | 5(Loss) | true |
