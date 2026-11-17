
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4043.19 | 0.151583 | 5117.34ms | 837491 | 1280 | 1.14768e+08 | 197540 | 0.557598 | 0.751084 | 1(Win) | true |
| Glaze | 2276.26 | 0.152818 | 8998.22ms | 837491 | 1280 | 3.68023e+08 | 350879 | 0.423603 | 1.33451 | 2(Loss) | true |
