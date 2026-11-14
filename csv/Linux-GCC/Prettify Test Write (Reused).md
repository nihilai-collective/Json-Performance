
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4167.45 | 0.296777 | 8619.3ms | 699405 | 160 | 3.60992e+07 | 160051 | 0.0219062 | 1.22176 | 4.79552 | 1.19825 | 0.00196256 | 0.000983059 | 1.02498e-05 | 1(Win) | true |
| Glaze | 3180.09 | 0.0677249 | 5556.1ms | 699405 | 320 | 6.45693e+06 | 209744 | 0.19944 | 1.59938 | 6.2869 | 1.35566 | 0.00195399 | 0.0012893 | 3.41228e-05 | 2(Loss) | true |
| simdjson (ondemand) | 2405.96 | 0.996484 | 7906.74ms | 767297 | 160 | 1.46964e+09 | 304141 | 0.657457 | 2.11303 | 8.04405 | 1.07991 | 0.00360279 | 0.0931552 | 8.34911e-05 | 3(Loss) | true |
