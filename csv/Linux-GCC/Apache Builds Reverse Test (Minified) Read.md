
----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1113.32 | 0.058559 | 8827.6ms | 94653 | 320 | 721388 | 81080.4 | 0.0573679 | 4.54869 | 20.6428 | 4.21044 | 0.010938 | 1.22157e-05 | 6.471e-06 | 1(Win) | true |
| simdjson (ondemand) | 700.137 | 0.0305407 | 6968.92ms | 94653 | 2560 | 3.96917e+06 | 128929 | 0.166858 | 7.24311 | 34.1184 | 7.06154 | 0.0128311 | 6.81849e-05 | 5.31918e-05 | 2(Loss) | true |
