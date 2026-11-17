
----
### Apache Builds Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.49 | 0.0921564 | 9950.16ms | 4211999 | 80 | 4.7047e+08 | 2.63145e+06 | 0.0573698 | 3.33246 | 15.4783 | 2.99723 | 0.0125735 | 0.0681156 | 0.00154355 | 1(Win) | true |
| simdjson (ondemand) | 920.06 | 0.0763055 | 7399.23ms | 4211999 | 80 | 8.87862e+08 | 4.36588e+06 | 0.0140994 | 5.5443 | 18.9107 | 3.359 | 0.0242068 | 0.0685317 | 0.0138654 | 2(Loss) | true |
