
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3204.66 | 0.515729 | 7122.93ms | 461466 | 160 | 8.02562e+07 | 137328 | 1.98091 | 0.771862 | 1(Win) | true |
| Glaze | 2619.76 | 0.0870737 | 8701.04ms | 461466 | 2560 | 5.47733e+07 | 167988 | 0.00188347 | 0.944802 | 2(Loss) | true |
