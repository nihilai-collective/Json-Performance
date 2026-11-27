
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1044.23 | 0.0458639 | 7691.01ms | 2251027 | 30 | 2.66705e+07 | 2.05581e+06 | 0.150058 | 2.3709 | 1(Win) | true |
| Jsonifier (two-stage) | 952.595 | 0.0515968 | 8303.04ms | 2251027 | 80 | 1.08163e+08 | 2.25358e+06 | 0.112871 | 2.59898 | 2(Loss) | true |
| Glaze | 934.585 | 0.0611663 | 8662.21ms | 2251027 | 30 | 5.92201e+07 | 2.297e+06 | 0.0116196 | 2.64906 | 3(Loss) | true |
| simdjson (ondemand) | 916.118 | 0.0871204 | 8728.56ms | 2251027 | 80 | 3.33418e+08 | 2.34331e+06 | 0.205371 | 2.70246 | 4(Loss) | true |
