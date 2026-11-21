
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.18 | 0.926703 | 6960.8ms | 461466 | 30 | 4.60377e+07 | 133677 | 0.00249352 | 0.751514 | 1(Win) | true |
| Glaze | 2643.16 | 0.159749 | 8573.79ms | 461466 | 2560 | 1.81113e+08 | 166501 | 0.182153 | 0.93647 | 2(Loss) | true |
