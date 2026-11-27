
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3220.84 | 0.0927665 | 5419.79ms | 699405 | 320 | 1.18101e+07 | 207090 | 0.0528958 | 1(Win) | true |
| Glaze | 2469.28 | 0.077934 | 7042.31ms | 699405 | 320 | 1.41814e+07 | 270121 | 0.142252 | 2(Loss) | true |
| simdjson (ondemand) | 1658.54 | 0.152399 | 5772.74ms | 767297 | 40 | 1.80844e+07 | 441203 | 0.0764556 | 3(Loss) | true |
