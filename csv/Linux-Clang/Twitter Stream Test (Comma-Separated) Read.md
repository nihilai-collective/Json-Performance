
----
### Twitter Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1798.4 | 0.264918 | 7821ms | 4219119 | 40 | 1.40525e+09 | 2.23736e+06 | 0.202039 | 1.37656 | 1(Win) | true |
| simdjson (ondemand) | 1689.53 | 0.185891 | 8301.55ms | 4219119 | 80 | 1.56791e+09 | 2.38153e+06 | 1.66375 | 1.46534 | 2(Loss) | true |
