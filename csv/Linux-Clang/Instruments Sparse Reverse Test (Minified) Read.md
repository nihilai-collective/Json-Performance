
----
### Instruments Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.37 | 0.212678 | 3858.97ms | 108313 | 320 | 1.42909e+06 | 31421.9 | 0.418021 | 1.56792 | 8.18969 | 1.44361 | 0.0014845 | 2.48123e-06 | 1.73109e-07 | 1(Win) | true |
| simdjson (ondemand) | 2585.35 | 0.0791023 | 4763.28ms | 108313 | 1280 | 1.27853e+06 | 39954.2 | 0.0509094 | 1.98633 | 10.3457 | 1.59747 | 0.00292903 | 4.02479e-06 | 1.3993e-06 | 2(Loss) | true |
