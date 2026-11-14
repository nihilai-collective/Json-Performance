
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14302.1 | 0.895491 | 748.54ms | 108313 | 80 | 334638 | 7222.4 | 0.044287 | 1(Win) | true |
| simdjson (reflection) | 7894.96 | 0.187517 | 1315.92ms | 108313 | 2560 | 1.54093e+06 | 13083.7 | 0.139673 | 2(Loss) | true |
| Glaze | 2046.51 | 0.135454 | 5219.58ms | 108313 | 4890 | 2.28575e+07 | 50473.9 | 0.282354 | 3(Loss) | true |
