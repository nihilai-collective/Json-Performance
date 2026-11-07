
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3734.72 | 0.514224 | 5504.63ms | 837491 | 80 | 9.6747e+07 | 213856 | 0.41496 | 0.662615 | 1(Win) | true |
| Glaze | 2253.71 | 0.326043 | 9181.28ms | 837491 | 40 | 5.3404e+07 | 354390 | 0.213058 | 1.0982 | 2(Loss) | true |
