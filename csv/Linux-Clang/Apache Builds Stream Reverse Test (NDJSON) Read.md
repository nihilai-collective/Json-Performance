
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1563.79 | 0.0978468 | 9776.17ms | 4212000 | 40 | 2.5268e+08 | 2.56867e+06 | 0.071905 | 3.23642 | 15.2579 | 2.94039 | 0.0120455 | 0.0663078 | 0.00142923 | 1(Win) | true |
| simdjson (ondemand) | 1311.59 | 0.0945861 | 5461.94ms | 4212000 | 80 | 6.7131e+08 | 3.06259e+06 | 0.198649 | 3.87128 | 16.6363 | 2.89734 | 0.0102263 | 0.0662761 | 0.0031137 | 2(Loss) | true |
