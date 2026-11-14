
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 946.897 | 0.105348 | 7767.47ms | 2090234 | 80 | 3.93481e+08 | 2.10519e+06 | 0.132684 | 5.36284 | 25.0602 | 4.35795 | 0.0223106 | 0.080224 | 0.00132787 | 1(Win) | true |
| Jsonifier (generic) | 856.956 | 0.161019 | 8421.83ms | 2090234 | 80 | 1.12232e+09 | 2.32614e+06 | 0.294494 | 5.92078 | 25.8085 | 5.11874 | 0.0208602 | 0.0784304 | 0.000671318 | 2(Loss) | true |
