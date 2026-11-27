
----
### Apache Builds Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14472.7 | 0.0870518 | 899.111ms | 136037 | 4890 | 297770 | 8964.14 | 0.0865392 | 1(Win) | true |
| Glaze | 5323.51 | 0.163622 | 2475.76ms | 136076 | 4890 | 7.7796e+06 | 24377.2 | 0.290737 | 2(Loss) | true |
| simdjson (reflection) | 392.345 | 0.108127 | 8645.48ms | 136037 | 320 | 4.09071e+07 | 330666 | 0.135668 | 3(Loss) | true |
