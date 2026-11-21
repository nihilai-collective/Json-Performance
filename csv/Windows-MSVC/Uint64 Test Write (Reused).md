
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3740.33 | 0.536278 | 115.327ms | 3873 | 40 | 1121.79 | 987.5 | 0.0844595 | 0.648477 | 1(Win) | true |
| Glaze | 1744.76 | 0.385194 | 224.257ms | 3873 | 2560 | 170224 | 2116.95 | 0.467168 | 1.40003 | 2(Loss) | true |
