
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2199.35 | 0.257411 | 5881.66ms | 2090234 | 320 | 1.74183e+09 | 906362 | 0.033022 | 1(Win) | true |
| Glaze | 1588.73 | 0.967391 | 8325.2ms | 2090234 | 30 | 4.41994e+09 | 1.25472e+06 | 2.39773 | 2(Loss) | true |
| simdjson (reflection) | 768.856 | 0.618189 | 8290.78ms | 2090326 | 30 | 7.70731e+09 | 2.5928e+06 | 0.0167877 | 3(Loss) | true |
