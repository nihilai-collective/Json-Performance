
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 819.571 | 0.302591 | 8217.15ms | 1834197 | 40 | 1.66836e+09 | 2.13432e+06 | 0.244518 | 1(Win) | true |
| Jsonifier (two-stage) | 687.313 | 0.229975 | 8972.34ms | 1834197 | 160 | 5.48107e+09 | 2.54502e+06 | 0.162668 | 2(Loss) | true |
| Glaze | 497.513 | 1.68376 | 6041.55ms | 1834197 | 40 | 1.40186e+11 | 3.51594e+06 | 0.163458 | 3(Loss) | true |
| simdjson (ondemand) | 453.259 | 0.182898 | 6380.97ms | 1834197 | 40 | 1.99287e+09 | 3.85922e+06 | 0.885656 | 4(Loss) | true |
