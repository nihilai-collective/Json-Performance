
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1158.85 | 0.0799355 | 103.134ms | 1213 | 640 | 407.499 | 998.237 | 0.0203525 | 1(Win) | true |
| Glaze | 174.76 | 0.0888054 | 670.647ms | 1213 | 30 | 1036.66 | 6619.4 | 0.0226555 | 2(Loss) | true |
