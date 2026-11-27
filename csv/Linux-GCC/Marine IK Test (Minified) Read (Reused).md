
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 691.886 | 0.112104 | 8545.95ms | 1834197 | 160 | 1.28525e+09 | 2.5282e+06 | 0.15168 | 7.36155 | 29.5043 | 6.33443 | 0.0417524 | 0.117997 | 0.00605714 | 1(Win) | true |
| simdjson (ondemand) | 669.335 | 0.0943911 | 8856.32ms | 1834197 | 160 | 9.73616e+08 | 2.61338e+06 | 0.111402 | 7.57544 | 31.2502 | 5.44056 | 0.0368703 | 0.11835 | 0.00688669 | 2(Loss) | true |
