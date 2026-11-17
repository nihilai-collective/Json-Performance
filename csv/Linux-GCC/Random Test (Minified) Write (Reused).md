
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14455.2 | 0.241519 | 3030.04ms | 461466 | 640 | 3.46031e+06 | 30444.9 | 0.0422868 | 0.171095 | 1(Win) | true |
| simdjson (reflection) | 10646.4 | 0.12608 | 4215.6ms | 461466 | 1280 | 3.47673e+06 | 41336.6 | 0.224732 | 0.232365 | 2(Loss) | true |
| Glaze | 3571.3 | 0.0857526 | 6391.67ms | 461466 | 640 | 7.14664e+06 | 123229 | 0.330659 | 0.693081 | 3(Loss) | true |
