
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2335.57 | 0.178352 | 63.3496ms | 1313 | 30 | 27.4299 | 536.133 | 0.124502 | 1.00782 | 1(Win) | true |
| Glaze | 1164.27 | 0.0733683 | 117.914ms | 1313 | 160 | 99.6226 | 1075.5 | 0.282787 | 2.07647 | 2(Loss) | true |
