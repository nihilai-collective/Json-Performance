
----
### Random Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1374.27 | 0.741314 | 5872.1ms | 461466 | 160 | 9.01701e+08 | 320235 | 0.0835084 | 1(Win) | true |
| Jsonifier (two-stage) | 1224.4 | 1.05827 | 6094.89ms | 461466 | 80 | 1.15748e+09 | 359430 | 0.544247 | 2(Loss) | true |
| Glaze | 1003.59 | 0.236903 | 7484.04ms | 461466 | 320 | 3.45348e+08 | 438514 | 0.896938 | 3(Loss) | true |
| simdjson (reflection) | 925.621 | 1.11296 | 8303.59ms | 461466 | 30 | 8.40034e+08 | 475452 | 1.36315 | 4(Loss) | true |
| simdjson (ondemand) | 740.197 | 0.811999 | 8696.4ms | 461466 | 160 | 3.72919e+09 | 594555 | 2.45243 | 5(Loss) | true |
