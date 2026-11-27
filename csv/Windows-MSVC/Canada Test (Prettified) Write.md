
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2767.71 | 0.120942 | 7295.24ms | 6661989 | 80 | 6.16612e+08 | 2.29554e+06 | 0.388697 | 0.894488 | 1(Win) | true |
| Glaze | 1040.62 | 1.30872 | 8700.68ms | 6661897 | 40 | 2.55364e+11 | 6.10526e+06 | 1.15295 | 2.3789 | 2(Loss) | true |
