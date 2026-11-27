
----
### Random Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 929.607 | 0.0883033 | 7771.15ms | 4506446 | 80 | 1.33325e+09 | 4.62312e+06 | 0.403592 | 5.48698 | 25.7063 | 5.16589 | 0.0180281 | 0.0811166 | 0.00433917 | 1(Win) | true |
| simdjson (ondemand) | 467.61 | 0.109363 | 6797.36ms | 4506446 | 40 | 4.04115e+09 | 9.19073e+06 | 0.219811 | 10.8918 | 44.1346 | 9.15229 | 0.0334735 | 0.0865945 | 0.0134371 | 2(Loss) | true |
