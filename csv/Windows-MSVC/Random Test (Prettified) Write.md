
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3768.37 | 0.764629 | 5501.6ms | 837491 | 30 | 7.87909e+07 | 211947 | 0.854945 | 0.656721 | 1(Win) | true |
| Glaze | 2071.07 | 0.276532 | 9804.61ms | 837491 | 160 | 1.81962e+08 | 385643 | 0.875796 | 1.19506 | 2(Loss) | true |
