
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2117.62 | 0.133151 | 7226.67ms | 631514 | 320 | 4.58893e+07 | 284404 | 0.00574591 | 1.16895 | 1(Win) | true |
| Glaze | 1808.15 | 0.202336 | 8556.71ms | 631514 | 160 | 7.26719e+07 | 333081 | 0.323822 | 1.36907 | 2(Loss) | true |
| Jsonifier | 1648.19 | 0.0979612 | 9600.06ms | 631514 | 320 | 4.10023e+07 | 365406 | 0.473401 | 1.50195 | 3(Loss) | true |
| simdjson (ondemand) | 1128.85 | 0.169331 | 6586.52ms | 631514 | 80 | 6.52908e+07 | 533513 | 0.357471 | 2.19301 | 4(Loss) | true |
