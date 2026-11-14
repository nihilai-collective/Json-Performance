
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 761.358 | 0.0758742 | 8314.39ms | 4219119 | 40 | 6.43154e+08 | 5.28486e+06 | 0.347998 | 6.6857 | 26.339 | 4.97693 | 0.0172933 | 0.0575623 | 0.000503192 | 1(Win) | true |
| simdjson (ondemand) | 284.299 | 0.118155 | 10065.1ms | 4219119 | 30 | 8.38914e+09 | 1.41529e+07 | 0.271178 | 17.7527 | 72.3434 | 12.5913 | 0.081114 | 0.0542475 | 0.0051299 | 2(Loss) | true |
