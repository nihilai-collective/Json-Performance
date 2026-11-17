
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14303.5 | 0.143407 | 5580.04ms | 837491 | 4890 | 3.13565e+07 | 55839.2 | 1.50829 | 1(Win) | true |
| Glaze | 2466.52 | 0.342853 | 8508.13ms | 837491 | 160 | 1.97209e+08 | 323814 | 0.115488 | 2(Loss) | true |
| simdjson (reflection) | 299.042 | 0.426728 | 8215.66ms | 837491 | 160 | 2.07835e+10 | 2.67084e+06 | 0.697384 | 3(Loss) | true |
