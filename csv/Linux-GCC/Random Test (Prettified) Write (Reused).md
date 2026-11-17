
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20541.2 | 0.048394 | 4659.96ms | 837491 | 640 | 226606 | 38882.5 | 0.0591176 | 0.246368 | 0.834691 | 0.124725 | 0.000130236 | 0.0116976 | 1.56606e-05 | 1(Win) | true |
| Glaze | 5721.02 | 0.0963721 | 7555.71ms | 837491 | 640 | 1.1585e+07 | 139607 | 0.0442285 | 0.877815 | 4.42726 | 0.728068 | 0.00588362 | 0.0203773 | 6.38328e-05 | 2(Loss) | true |
| simdjson (reflection) | 534.298 | 0.316568 | 9500.77ms | 837491 | 320 | 7.16599e+09 | 1.49485e+06 | 0.250038 | 9.40146 | 37.2114 | 7.11018 | 0.028981 | 0.352007 | 0.00220981 | 3(Loss) | true |
