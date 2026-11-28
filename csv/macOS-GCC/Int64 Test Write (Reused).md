
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 2502.35 | 1.98623 | 63.8569ms | 1313 | 2560 | 252892 | 500.4 | 2.7972 | 1(Win) | true |
| Jsonifier | 1993.37 | 1.18584 | 71.9178ms | 1313 | 4890 | 271340 | 628.169 | 1.6783 | 2(Loss) | true |
| Glaze | 803.5 | 2.54949 | 170.743ms | 1313 | 160 | 252571 | 1558.4 | 2.31092 | 3(Loss) | true |
