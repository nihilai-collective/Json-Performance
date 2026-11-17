
----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 804.768 | 0.0530379 | 1060.3ms | 2821 | 320 | 1005.97 | 3342.97 | 0.0181318 | 6.47819 | 26.3676 | 4.95427 | 0.00229861 | 4.65261e-05 | 2.21553e-06 | 1(Win) | true |
| simdjson (ondemand) | 397.62 | 0.0363903 | 1403.48ms | 2821 | 2560 | 15519.6 | 6766.05 | 0.0471515 | 13.0153 | 58.9309 | 11.9 | 0.0102692 | 0.000148025 | 7.17277e-05 | 2(Loss) | true |
