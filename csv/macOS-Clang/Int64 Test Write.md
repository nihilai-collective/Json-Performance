
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1201.78 | 0.139804 | 108.065ms | 1313 | 160 | 339.498 | 1041.93 | 0.0257868 | 1(Win) | true |
| Glaze | 178.14 | 0.046097 | 715.948ms | 1313 | 160 | 1679.85 | 7029.14 | 0.0448822 | 2(Loss) | true |
