
----
### Prettify Test Write Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Prettify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2925.99 | 0.64331 | 6111.42ms | 699405 | 160 | 3.44091e+08 | 227959 | 0.796384 | 0.845988 | 1(Win) | true |
| Jsonifier | 2428.58 | 0.458881 | 7047.78ms | 699405 | 40 | 6.35349e+07 | 274648 | 0.00455108 | 1.01908 | 2(Loss) | true |
| simdjson (ondemand) | 1373.27 | 0.278342 | 6701.4ms | 767297 | 320 | 7.03923e+08 | 532854 | 0.652567 | 1.80256 | 3(Loss) | true |
