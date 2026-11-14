
----
### Twitter Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 859.974 | 0.0348665 | 1052.31ms | 2821 | 4890 | 5817.82 | 3128.37 | 0.0294763 | 6.06373 | 26.1372 | 4.83233 | 0.00119408 | 0.000117944 | 5.24115e-05 | 1(Win) | true |
| simdjson (ondemand) | 357.982 | 0.0354828 | 1472.8ms | 2821 | 2560 | 18203.7 | 7515.22 | 0.0401627 | 14.4611 | 67.0245 | 11.5509 | 0.0129219 | 9.05596e-05 | 2.49247e-05 | 2(Loss) | true |
