
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1773.94 | 0.144509 | 7771.54ms | 4219119 | 80 | 8.59505e+08 | 2.26821e+06 | 0.916511 | 2.87054 | 10.3254 | 1.83207 | 0.0162632 | 0.0531638 | 0.00291181 | 1(Win) | true |
| simdjson (ondemand) | 1496 | 0.141917 | 9104.32ms | 4219119 | 160 | 2.33114e+09 | 2.68962e+06 | 0.0770874 | 3.36275 | 11.9558 | 1.94835 | 0.0155895 | 0.0550912 | 0.00522736 | 2(Loss) | true |
