
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2039.76 | 1.03048 | 6100.65ms | 2090234 | 80 | 8.11343e+09 | 977274 | 0.268434 | 1(Win) | true |
| Glaze | 1419.1 | 0.873691 | 8647.19ms | 2090234 | 80 | 1.20495e+10 | 1.40469e+06 | 2.75397 | 2(Loss) | true |
| simdjson (reflection) | 745.51 | 0.613868 | 8736.91ms | 2090326 | 160 | 4.31114e+10 | 2.674e+06 | 3.00174 | 3(Loss) | true |
