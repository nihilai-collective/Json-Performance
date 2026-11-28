
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2756.27 | 2.24597 | 56.3868ms | 1313 | 2560 | 266522 | 454.3 | 0.419982 | 1(Win) | true |
| simdjson (reflection) | 2475.52 | 1.43826 | 63.329ms | 1313 | 4890 | 258808 | 505.822 | 3.87258 | 2(Loss) | true |
| Glaze | 921.123 | 1.1141 | 149.739ms | 1313 | 1280 | 293599 | 1359.4 | 0.577094 | 3(Loss) | true |
