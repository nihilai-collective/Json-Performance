
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 779.443 | 0.145301 | 7975.91ms | 2090234 | 30 | 4.14269e+08 | 2.55747e+06 | 0.162116 | 6.52433 | 32.6606 | 6.35605 | 0.0229047 | 0.104268 | 2.38251e-05 | 1(Win) | true |
| simdjson (ondemand) | 765.031 | 0.0707108 | 8082.47ms | 2090234 | 160 | 5.43155e+08 | 2.60565e+06 | 0.0757604 | 6.60949 | 31.7559 | 5.64958 | 0.0228756 | 0.10564 | 0.000262692 | 2(Loss) | true |
