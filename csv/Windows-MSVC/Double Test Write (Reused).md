
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 714.462 | 0.141305 | 291.594ms | 1997 | 160 | 2270.05 | 2665.62 | 0.117371 | 3.43571 | 1(Win) | true |
| Glaze | 369.35 | 0.0844458 | 496.686ms | 1798 | 160 | 2459.12 | 4642.5 | 0.0538793 | 6.66015 | 2(Loss) | true |
