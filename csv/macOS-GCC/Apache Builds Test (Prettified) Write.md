
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12973.5 | 0.379962 | 1018.82ms | 136037 | 320 | 461988 | 10000 | 0.175691 | 1(Win) | true |
| Glaze | 3979.24 | 0.253571 | 3206.74ms | 136076 | 2560 | 1.75066e+07 | 32612.3 | 0.285882 | 2(Loss) | true |
| simdjson (reflection) | 337.292 | 0.312143 | 10179.8ms | 136037 | 80 | 1.15318e+08 | 384637 | 0.0824313 | 3(Loss) | true |
