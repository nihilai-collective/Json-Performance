
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16458.5 | 0.126953 | 2765.76ms | 475954 | 1280 | 1.5691e+06 | 27578.8 | 0.135068 | 1(Win) | true |
| simdjson (reflection) | 12229.1 | 0.226269 | 3799.01ms | 475954 | 160 | 1.12853e+06 | 37116.8 | 0.326545 | 2(Loss) | true |
| Glaze | 4110.27 | 0.148471 | 5648.09ms | 475954 | 320 | 8.60247e+06 | 110432 | 0.112883 | 3(Loss) | true |
