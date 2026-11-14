
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 890.363 | 0.112215 | 7988.99ms | 4506447 | 40 | 1.17355e+09 | 4.82689e+06 | 0.0247602 | 5.70673 | 26.5408 | 5.38696 | 0.0108981 | 0.0812864 | 0.00684429 | 1(Win) | true |
| simdjson (ondemand) | 548.31 | 0.254742 | 5816.78ms | 4506447 | 40 | 1.59469e+10 | 7.83805e+06 | 0.47167 | 9.22485 | 40.1256 | 7.93318 | 0.0288838 | 0.0791796 | 0.0135899 | 2(Loss) | true |
