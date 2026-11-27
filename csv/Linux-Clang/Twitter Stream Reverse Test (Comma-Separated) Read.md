
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 757.923 | 0.217169 | 8317.66ms | 4219119 | 80 | 1.06336e+10 | 5.3088e+06 | 0.0983594 | 6.71825 | 25.5494 | 4.72308 | 0.0220553 | 0.0546553 | 0.00449884 | 1(Win) | true |
| simdjson (ondemand) | 283.98 | 0.1318 | 10150ms | 4219119 | 30 | 1.04621e+10 | 1.41688e+07 | 0.506158 | 17.8215 | 72.1678 | 12.5827 | 0.081434 | 0.0556729 | 0.0144372 | 2(Loss) | true |
