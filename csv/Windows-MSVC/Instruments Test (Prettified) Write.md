
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13627.6 | 0.0711225 | 1600.76ms | 213963 | 30 | 3402.3 | 14973.3 | 0.244282 | 0.181286 | 1(Win) | true |
| Glaze | 3578.59 | 0.35748 | 5917.28ms | 213963 | 80 | 3.3239e+06 | 57020 | 0.271098 | 0.691467 | 2(Loss) | true |
