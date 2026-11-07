
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3504.79 | 0.099526 | 6488.95ms | 461466 | 2560 | 3.99824e+07 | 125568 | 0.243237 | 0.705908 | 1(Win) | true |
| Glaze | 2805.54 | 0.267514 | 8176.8ms | 461466 | 160 | 2.81747e+07 | 156864 | 0.0183314 | 0.882246 | 2(Loss) | true |
