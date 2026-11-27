
----
### Canada Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2398.01 | 0.0863919 | 5357.12ms | 2090326 | 320 | 1.65052e+08 | 831309 | 0.05392 | 1(Win) | true |
| simdjson (reflection) | 2140.4 | 0.0930095 | 5916.36ms | 2090326 | 160 | 1.20064e+08 | 931363 | 0.0188935 | 2(Loss) | true |
| Glaze | 1788.53 | 0.275563 | 7123.26ms | 2090234 | 160 | 1.50925e+09 | 1.11455e+06 | 0.0547247 | 3(Loss) | true |
