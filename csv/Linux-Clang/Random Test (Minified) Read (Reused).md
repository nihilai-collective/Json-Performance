
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1602.21 | 0.135166 | 7561.89ms | 409725 | 80 | 8.69307e+06 | 243879 | 0.0219579 | 3.20571 | 15.648 | 3.01558 | 0.00652035 | 0.00580694 | 7.81012e-06 | 1(Win) | true |
| simdjson (ondemand) | 1101.91 | 0.134118 | 5166.74ms | 409725 | 80 | 1.80949e+07 | 354606 | 0.0643539 | 4.60132 | 18.1683 | 3.11728 | 0.0171538 | 0.012368 | 7.51419e-05 | 2(Loss) | true |
