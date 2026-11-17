
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.482 | 0.0412416 | 8382.32ms | 4203058 | 30 | 1.43261e+08 | 5.29867e+06 | 0.202182 | 6.80294 | 30.1525 | 6.16082 | 0.024738 | 0.0889217 | 0.00835213 | 1(Win) | true |
| simdjson (ondemand) | 594.579 | 0.121395 | 10428.1ms | 4203058 | 30 | 2.00925e+09 | 6.74149e+06 | 0.264429 | 8.52398 | 33.4786 | 6.06033 | 0.0325685 | 0.101678 | 0.0100648 | 2(Loss) | true |
