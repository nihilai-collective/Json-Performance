
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 735.011 | 0.100327 | 8482.33ms | 2090234 | 80 | 5.92276e+08 | 2.71207e+06 | 0.645353 | 6.94995 | 35.6643 | 6.98898 | 0.0228326 | 0.157185 | 0.000112918 | 1(Win) | true |
| simdjson (ondemand) | 701.917 | 0.11149 | 8844.54ms | 2090234 | 30 | 3.00756e+08 | 2.83994e+06 | 0.237099 | 7.23081 | 36.0797 | 6.61044 | 0.022877 | 0.181413 | 0.000125648 | 2(Loss) | true |
