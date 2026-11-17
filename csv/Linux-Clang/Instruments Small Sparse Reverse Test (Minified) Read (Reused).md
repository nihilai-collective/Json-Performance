
----
### Instruments Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3469.76 | 0.387689 | 845.592ms | 4669 | 80 | 1980.18 | 1283.29 | 0.155116 | 1.53073 | 7.37803 | 1.25123 | 0.00136539 | 2.94496e-05 | 8.0317e-06 | 1(Win) | true |
| simdjson (ondemand) | 2674.79 | 0.037433 | 888.376ms | 4669 | 4890 | 1898.84 | 1664.7 | 0.128834 | 1.96305 | 9.51596 | 1.46755 | 0.00231825 | 1.19134e-05 | 1.62057e-06 | 2(Loss) | true |
