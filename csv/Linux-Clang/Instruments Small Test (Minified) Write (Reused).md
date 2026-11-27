
----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12929.8 | 0.158741 | 766.552ms | 4669 | 4890 | 1461.33 | 344.375 | 0.064939 | 0.438939 | 1.51253 | 0.207111 | 0.000214617 | 1.93155e-05 | 6.3509e-06 | 1(Win) | true |
| Glaze | 2777.15 | 0.129207 | 892.967ms | 4669 | 4890 | 20985.9 | 1603.34 | 0.758007 | 1.86651 | 3.1949 | 0.397516 | 0.000218033 | 2.48342e-05 | 6.1319e-06 | 2(Loss) | true |
