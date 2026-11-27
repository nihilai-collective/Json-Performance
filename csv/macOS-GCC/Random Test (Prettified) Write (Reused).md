
----
### Random Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18581 | 0.127263 | 4409.53ms | 837491 | 640 | 1.91517e+06 | 42984.4 | 0.0512076 | 1(Win) | true |
| Glaze | 2966.9 | 0.262862 | 7300.67ms | 837491 | 30 | 1.50221e+07 | 269201 | 0.136119 | 2(Loss) | true |
| simdjson (reflection) | 356.702 | 0.128112 | 7059.09ms | 837491 | 160 | 1.31658e+09 | 2.23911e+06 | 1.23087 | 3(Loss) | true |
