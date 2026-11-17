
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14795.9 | 0.587237 | 5653.07ms | 837491 | 160 | 1.60777e+07 | 53980.8 | 0.0770051 | 1(Win) | true |
| Glaze | 2696.19 | 0.273455 | 7644.59ms | 837491 | 320 | 2.09981e+08 | 296230 | 0.412027 | 2(Loss) | true |
| simdjson (reflection) | 311.329 | 0.625829 | 8064.57ms | 837491 | 30 | 7.73311e+09 | 2.56544e+06 | 0.782088 | 3(Loss) | true |
