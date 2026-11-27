
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1475.86 | 0.329794 | 89.7732ms | 1313 | 320 | 2505.39 | 848.438 | 0.110619 | 1.62331 | 1(Win) | true |
| Glaze | 412.352 | 0.294683 | 312.431ms | 1313 | 30 | 2402.3 | 3036.67 | 0.219058 | 5.91813 | 2(Loss) | true |
| simdjson (ondemand) | 314.091 | 0.158338 | 407.215ms | 1313 | 30 | 1195.4 | 3986.67 | 0.167504 | 7.82374 | 3(Loss) | true |
