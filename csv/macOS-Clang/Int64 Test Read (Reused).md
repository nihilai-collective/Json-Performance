
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1386.06 | 0.236407 | 94.3889ms | 1313 | 160 | 729.802 | 903.406 | 0.257328 | 1(Win) | true |
| Glaze | 859.872 | 0.0561017 | 149.5ms | 1313 | 1280 | 854.327 | 1456.23 | 0.101391 | 2(Loss) | true |
| simdjson (ondemand) | 323.145 | 0.0730603 | 394.348ms | 1313 | 30 | 240.447 | 3874.97 | 0.357431 | 3(Loss) | true |
