
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11920.7 | 0.259906 | 3825.43ms | 461466 | 640 | 5.89235e+06 | 36918 | 2.43864 | 1(Win) | true |
| simdjson (reflection) | 7001.95 | 0.252363 | 6138.45ms | 461466 | 2560 | 6.44068e+07 | 62852.2 | 0.747606 | 2(Loss) | true |
| Glaze | 2039.92 | 0.32638 | 5246.8ms | 461466 | 1280 | 6.34611e+08 | 215738 | 0.211291 | 3(Loss) | true |
