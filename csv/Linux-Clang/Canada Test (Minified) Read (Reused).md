
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 920.843 | 0.48119 | 7984.7ms | 2090234 | 40 | 4.34022e+09 | 2.16476e+06 | 0.06331 | 5.48019 | 27.2873 | 5.09175 | 0.0221006 | 0.0787975 | 0.000158535 | 1(Win) | true |
| simdjson (ondemand) | 885.193 | 0.30906 | 8238.97ms | 2090234 | 80 | 3.87517e+09 | 2.25194e+06 | 0.240375 | 5.7171 | 26.429 | 4.36112 | 0.0219782 | 0.0783751 | 0.000431961 | 2(Loss) | true |
