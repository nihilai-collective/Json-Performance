
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1481.9 | 0.401527 | 91.0877ms | 1213 | 160 | 1571.93 | 780.625 | 0.08 | 1.61793 | 1(Win) | true |
| Glaze | 654.433 | 0.313435 | 187.308ms | 1213 | 4890 | 150105 | 1767.65 | 0.407818 | 3.72215 | 2(Loss) | true |
