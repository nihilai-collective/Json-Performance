
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 791.888 | 0.110136 | 7794.71ms | 4197495 | 40 | 1.23985e+09 | 5.05506e+06 | 0.0385978 | 6.4113 | 27.6257 | 5.73487 | 0.000938947 | 0.083573 | 0.00164782 | 1(Win) | true |
| simdjson (ondemand) | 663.726 | 0.133578 | 9217.86ms | 4197495 | 80 | 5.19235e+09 | 6.03117e+06 | 0.0904506 | 7.63315 | 36.0099 | 7.18262 | 0.0167827 | 0.103093 | 0.012335 | 2(Loss) | true |
