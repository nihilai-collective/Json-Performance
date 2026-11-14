
----
### Google Maps Response Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1150.59 | 0.100367 | 5523.29ms | 4203058 | 40 | 4.89026e+08 | 3.48374e+06 | 0.131551 | 4.44492 | 19.9837 | 3.95304 | 0.0162264 | 0.0889822 | 0.00178356 | 1(Win) | true |
| simdjson (ondemand) | 779.009 | 0.105273 | 8044.57ms | 4203058 | 40 | 1.17364e+09 | 5.14545e+06 | 0.439712 | 6.53325 | 25.0228 | 4.44937 | 0.0278738 | 0.10438 | 0.00949836 | 2(Loss) | true |
