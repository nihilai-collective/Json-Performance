
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3421.28 | 0.201084 | 6203.62ms | 837491 | 320 | 7.05161e+07 | 233449 | 1.12573 | 0.723297 | 1(Win) | true |
| Glaze | 1993.68 | 0.143038 | 5085.15ms | 837491 | 640 | 2.1015e+08 | 400612 | 0.26169 | 1.24145 | 2(Loss) | true |
