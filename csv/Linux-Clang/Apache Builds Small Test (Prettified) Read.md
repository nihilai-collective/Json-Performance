
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2349.38 | 0.0864938 | 855.373ms | 3370 | 320 | 447.996 | 1367.97 | 0.0655194 | 2.24184 | 8.89466 | 1.5724 | 0.000526706 | 3.98739e-05 | 3.7092e-06 | 1(Win) | true |
| simdjson (ondemand) | 1996.18 | 0.129188 | 877.785ms | 3370 | 1280 | 5537.57 | 1610.02 | 0.102199 | 2.64159 | 9.75727 | 1.66469 | 0.00186202 | 0.000107103 | 5.54062e-05 | 2(Loss) | true |
