
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22878.4 | 0.172626 | 1949.36ms | 466906 | 2560 | 2.88975e+06 | 19462.8 | 0.193249 | 0.107992 | 1(Win) | true |
| simdjson (ondemand) | 21330.8 | 0.126573 | 2155.76ms | 466906 | 4890 | 3.41378e+06 | 20874.8 | 0.717768 | 0.115906 | 2(Loss) | true |
| Glaze | 1715.04 | 0.139664 | 6688ms | 466906 | 320 | 4.20753e+07 | 259630 | 0.421113 | 1.44344 | 3(Loss) | true |
