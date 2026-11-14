
----
### Apache Builds Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1490.22 | 0.0369021 | 935.489ms | 3370 | 4890 | 3097.18 | 2156.64 | 0.0294311 | 3.51854 | 13.657 | 2.65341 | 0.00449716 | 3.7623e-05 | 7.28186e-06 | 1(Win) | true |
| simdjson (ondemand) | 930.223 | 0.0338281 | 1063.56ms | 3370 | 640 | 874.219 | 3454.96 | 0.0466051 | 5.60307 | 24.0893 | 4.56706 | 0.00845095 | 4.59013e-05 | 9.273e-06 | 2(Loss) | true |
