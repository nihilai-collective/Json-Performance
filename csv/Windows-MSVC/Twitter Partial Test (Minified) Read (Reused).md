
----
### Twitter Partial Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7105.66 | 0.784785 | 6553.36ms | 466906 | 40 | 9.67413e+06 | 62665 | 1.19048 | 0.427503 | 1(Win) | true |
| Jsonifier | 6655.8 | 0.666168 | 6700.77ms | 466906 | 4890 | 9.71261e+08 | 66900.5 | 0.401281 | 0.456459 | 2(Loss) | true |
| simdjson (ondemand) | 4156.69 | 0.631766 | 5551.39ms | 466906 | 2560 | 1.17251e+09 | 107123 | 1.51675 | 0.730653 | 3(Loss) | true |
| Glaze | 2930.25 | 0.376311 | 7926.71ms | 466906 | 2560 | 8.37107e+08 | 151958 | 0.722485 | 1.03699 | 4(Loss) | true |
