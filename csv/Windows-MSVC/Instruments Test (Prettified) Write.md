
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14108.2 | 0.070192 | 1551.31ms | 213963 | 30 | 3091.95 | 14463.3 | 1.07151 | 0.175075 | 1(Win) | true |
| Glaze | 3568.71 | 0.283839 | 5787.34ms | 213963 | 1280 | 3.37138e+07 | 57177.7 | 0.382534 | 0.693366 | 2(Loss) | true |
