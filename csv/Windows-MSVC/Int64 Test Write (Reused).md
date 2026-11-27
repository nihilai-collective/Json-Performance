
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1274.48 | 0.619272 | 107.21ms | 1313 | 40 | 1480.77 | 982.5 | 0.0847458 | 1.8905 | 1(Win) | true |
| Glaze | 666.05 | 0.395096 | 216.103ms | 1313 | 30 | 1655.17 | 1880 | 0.17762 | 3.66469 | 2(Loss) | true |
