
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2650.86 | 0.960989 | 5226.56ms | 466906 | 40 | 1.04228e+08 | 167974 | 0.190869 | 1(Win) | true |
| Glaze | 2108.44 | 0.240016 | 6973.36ms | 466906 | 40 | 1.02772e+07 | 211187 | 0.20447 | 2(Loss) | true |
| Jsonifier (two-stage) | 1856.18 | 1.3804 | 6968.34ms | 466906 | 30 | 3.28968e+08 | 239889 | 0.797516 | 3(Loss) | true |
| simdjson (reflection) | 1498.33 | 0.0969158 | 8587.41ms | 466906 | 320 | 2.6545e+07 | 297182 | 0.18245 | 4(Loss) | true |
| simdjson (ondemand) | 1073.4 | 0.139246 | 5779.29ms | 466906 | 640 | 2.13542e+08 | 414829 | 0.234476 | 5(Loss) | true |
