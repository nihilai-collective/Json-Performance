
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11535.6 | 0.395465 | 3894.24ms | 461466 | 160 | 3.64195e+06 | 38150.4 | 0.109161 | 1(Win) | true |
| simdjson (reflection) | 7790.58 | 0.0827779 | 5596.68ms | 461466 | 4890 | 1.06925e+07 | 56489.8 | 0.629138 | 2(Loss) | true |
| Glaze | 2322.08 | 0.198494 | 9763.04ms | 461466 | 80 | 1.13216e+07 | 189523 | 0.0878764 | 3(Loss) | true |
