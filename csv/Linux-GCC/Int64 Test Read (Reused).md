
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.11 | 0.0340565 | 976.924ms | 3862 | 4890 | 3969.95 | 2645.69 | 0.0879699 | 3.75589 | 17.6567 | 1.90471 | 0.00026497 | 6.09473e-05 | 8.26045e-06 | 1(Win) | true |
| simdjson (ondemand) | 760.839 | 0.0478049 | 1196.44ms | 3862 | 1280 | 6854.79 | 4840.83 | 0.0271689 | 6.8222 | 31.5601 | 3.45236 | 0.00109076 | 2.44773e-05 | 2.02292e-06 | 2(Loss) | true |
