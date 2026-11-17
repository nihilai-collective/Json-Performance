
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3581.12 | 0.0566585 | 6399.22ms | 16002591 | 80 | 4.66406e+08 | 4.26159e+06 | 0.209031 | 1.41211 | 7.89616 | 1.29591 | 0.000882413 | 0.0359179 | 0.00724997 | 1(Win) | true |
| simdjson (ondemand) | 1676.65 | 0.0768055 | 6384.58ms | 16002591 | 40 | 1.95497e+09 | 9.10223e+06 | 0.33334 | 3.02275 | 13.1392 | 2.15446 | 0.00283234 | 0.0539245 | 0.00569991 | 2(Loss) | true |
