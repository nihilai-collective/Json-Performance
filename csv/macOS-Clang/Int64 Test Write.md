
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1163.33 | 0.616754 | 115.969ms | 1313 | 30 | 1322.1 | 1076.37 | 0.654593 | 1(Win) | true |
| Glaze | 162.434 | 0.379226 | 784.331ms | 1313 | 2560 | 2.18783e+06 | 7708.82 | 0.0213488 | 2(Loss) | true |
