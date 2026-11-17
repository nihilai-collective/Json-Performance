
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1376.37 | 0.0806143 | 983.501ms | 3873 | 80 | 374.401 | 2683.56 | 0.0647041 | 3.79796 | 17.6558 | 1.89801 | 0.00119739 | 8.06868e-05 | 1.61374e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.98 | 0.0485092 | 1209.73ms | 3873 | 1280 | 7266.77 | 4911.81 | 0.130835 | 6.87853 | 31.3016 | 3.56468 | 0.00759525 | 4.43777e-05 | 3.22747e-06 | 2(Loss) | true |
