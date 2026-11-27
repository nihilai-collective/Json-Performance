
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2394.16 | 0.311351 | 5370.48ms | 2090326 | 40 | 2.68832e+08 | 832646 | 0.094118 | 1(Win) | true |
| simdjson (reflection) | 2149.85 | 0.188711 | 5947.36ms | 2090326 | 40 | 1.2248e+08 | 927270 | 0.0253137 | 2(Loss) | true |
| Glaze | 1884.37 | 0.136051 | 6850.56ms | 2090234 | 30 | 6.21414e+07 | 1.05786e+06 | 0.315214 | 3(Loss) | true |
