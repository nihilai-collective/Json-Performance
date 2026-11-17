
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23912.1 | 0.134893 | 429.56ms | 108313 | 30 | 1018.65 | 4319.8 | 0.353699 | 0.102906 | 1(Win) | true |
| simdjson (reflection) | 14630.4 | 0.0293063 | 701.521ms | 108313 | 40 | 171.251 | 7060.32 | 0.630814 | 0.168594 | 2(Loss) | true |
| Glaze | 2536.23 | 0.117581 | 4092.74ms | 108313 | 1280 | 2.93539e+06 | 40727.8 | 0.123616 | 0.975582 | 3(Loss) | true |
