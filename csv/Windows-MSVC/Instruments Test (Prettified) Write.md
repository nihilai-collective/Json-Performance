
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13864.5 | 1.07424 | 1580.04ms | 213963 | 80 | 1.99969e+06 | 14717.5 | 0.289608 | 0.218816 | 1(Win) | true |
| Glaze | 4182.27 | 0.263472 | 4977.17ms | 213963 | 2560 | 4.2302e+07 | 48789.5 | 0.93339 | 0.726362 | 2(Loss) | true |
