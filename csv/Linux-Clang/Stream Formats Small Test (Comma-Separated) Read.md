
----
### Stream Formats Small Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3582.1 | 0.136876 | 6465.27ms | 16002591 | 80 | 2.72049e+09 | 4.26042e+06 | 0.365201 | 1.41146 | 7.88139 | 1.31417 | 0.000824569 | 0.0358505 | 0.00637037 | 1(Win) | true |
| simdjson (ondemand) | 2022.47 | 0.225687 | 5350.61ms | 16002591 | 30 | 8.70068e+09 | 7.54587e+06 | 0.880634 | 2.51781 | 12.65 | 2.08617 | 0.00138177 | 0.0515488 | 0.00801653 | 2(Loss) | true |
