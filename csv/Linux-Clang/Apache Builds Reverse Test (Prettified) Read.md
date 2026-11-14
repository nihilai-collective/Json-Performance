
----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.46 | 0.023084 | 9009.06ms | 124597 | 2560 | 939981 | 83009.8 | 0.0410175 | 3.56412 | 16.5479 | 3.28321 | 0.00845738 | 9.41786e-06 | 4.31391e-06 | 1(Win) | true |
| simdjson (ondemand) | 939.936 | 0.0252969 | 6807.61ms | 124597 | 2560 | 2.61813e+06 | 126418 | 0.111507 | 5.42273 | 26.6555 | 5.30039 | 0.00941692 | 1.67948e-05 | 8.01647e-06 | 2(Loss) | true |
