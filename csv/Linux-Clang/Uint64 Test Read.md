
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4889.23 | 0.145607 | 780.582ms | 3873 | 640 | 774.392 | 755.453 | 0.0421754 | 1.11015 | 5.29176 | 0.530855 | 0.0007754 | 2.78369e-05 | 4.03434e-06 | 1(Win) | true |
| simdjson (stage-1) | 1926.94 | 0.0365836 | 904.151ms | 3873 | 4890 | 2404.58 | 1916.81 | 0.0238255 | 2.72288 | 14.3145 | 1.14821 | 0.000854798 | 3.33703e-05 | 3.32647e-06 | 2(Loss) | true |
