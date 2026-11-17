
----
### Instruments Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18196.4 | 0.160299 | 1128.21ms | 213963 | 1280 | 413598 | 11213.8 | 0.302326 | 1(Win) | true |
| Glaze | 2680.28 | 0.134535 | 7818ms | 213963 | 320 | 3.35687e+06 | 76130.4 | 0.0157649 | 2(Loss) | true |
| simdjson (reflection) | 318.895 | 0.215839 | 8425.64ms | 213963 | 320 | 6.10364e+08 | 639868 | 0.626061 | 3(Loss) | true |
