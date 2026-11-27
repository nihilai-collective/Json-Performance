
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 953.08 | 0.729914 | 115.953ms | 1313 | 160 | 14714.1 | 1313.82 | 2.48778 | 1(Win) | true |
| Glaze | 182.854 | 0.132209 | 683.661ms | 1313 | 1280 | 104918 | 6847.93 | 0.580948 | 2(Loss) | true |
