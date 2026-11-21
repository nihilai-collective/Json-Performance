
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 687.239 | 0.221167 | 826.175ms | 4630 | 40 | 8076.92 | 6425 | 0.232919 | 3.58844 | 1(Win) | true |
| Jsonifier (two-stage) | 639.62 | 0.147061 | 850.125ms | 4630 | 30 | 3091.95 | 6903.33 | 0.0483092 | 3.85318 | 2(Loss) | true |
| Glaze | 186.335 | 0.114894 | 2572.38ms | 4630 | 2560 | 1.89762e+06 | 23696.7 | 0.319993 | 13.2721 | 3(Loss) | true |
| simdjson (ondemand) | 185.63 | 0.0523042 | 2536.43ms | 4630 | 30 | 4643.68 | 23786.7 | 0.0841515 | 13.3191 | 4(Loss) | true |
