
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7453.23 | 0.133911 | 5934.35ms | 466906 | 2560 | 1.63849e+07 | 59742.7 | 0.0931597 | 1(Win) | true |
| Jsonifier | 6265.66 | 0.68646 | 6895.2ms | 466906 | 320 | 7.61564e+07 | 71066.2 | 0.618024 | 2(Loss) | true |
| Glaze | 1481.18 | 0.824542 | 7650.75ms | 466906 | 80 | 4.91543e+08 | 300623 | 0.495975 | 3(Loss) | true |
