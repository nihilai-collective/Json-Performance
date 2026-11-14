
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2090.77 | 0.187937 | 7879.81ms | 4212000 | 30 | 3.91118e+08 | 1.92124e+06 | 0.0484818 | 2.43232 | 11.3158 | 2.01958 | 0.0116307 | 0.0664041 | 0.00680157 | 1(Win) | true |
| simdjson (ondemand) | 1534.02 | 0.102067 | 9951.45ms | 4212000 | 30 | 2.14292e+08 | 2.61854e+06 | 0.369623 | 3.30909 | 12.5987 | 2.34147 | 0.0119655 | 0.0659368 | 0.00187844 | 2(Loss) | true |
