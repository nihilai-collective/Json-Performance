
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 796.355 | 0.111627 | 7942.71ms | 4203059 | 80 | 2.5255e+09 | 5.03337e+06 | 0.0356101 | 6.38066 | 28.0166 | 5.62766 | 0.0229145 | 0.089484 | 0.0153223 | 1(Win) | true |
| simdjson (ondemand) | 706.035 | 0.153947 | 8934.72ms | 4203059 | 40 | 3.05549e+09 | 5.67727e+06 | 0.119469 | 7.20683 | 28.8471 | 5.14704 | 0.0312362 | 0.0879426 | 0.00731048 | 2(Loss) | true |
