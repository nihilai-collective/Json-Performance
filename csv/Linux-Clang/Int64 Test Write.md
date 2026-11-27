
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 336.728 | 0.0605872 | 1094.81ms | 1313 | 4890 | 24822.3 | 3718.65 | 0.186581 | 15.4504 | 74.0807 | 15.5248 | 0.0187965 | 0.000191416 | 4.99956e-05 | 1(Win) | true |
| Glaze | 306.514 | 0.111857 | 1137.2ms | 1313 | 1280 | 26728.1 | 4085.21 | 0.00686594 | 16.8489 | 83.2468 | 16.5423 | 0.0271212 | 0.000146373 | 2.49905e-05 | 2(Loss) | true |
