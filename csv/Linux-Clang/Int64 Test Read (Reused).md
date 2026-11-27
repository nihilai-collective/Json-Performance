
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.853 | 0.0702756 | 155.809ms | 1313 | 40 | 46.7635 | 1538.58 | 0.0687393 | 2.98755 | 1(Win) | true |
| simdjson (ondemand) | 359.22 | 0.193607 | 355.526ms | 1313 | 2560 | 116598 | 3485.82 | 1.03432 | 6.83897 | 2(Loss) | true |
