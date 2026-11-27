
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17254.7 | 0.252773 | 8265.65ms | 1439562 | 160 | 6.47186e+06 | 79565.4 | 0.00904049 | 0.143433 | 1(Win) | true |
| Glaze | 5385.25 | 0.0659025 | 6580.41ms | 1439584 | 640 | 1.80653e+07 | 254936 | 0.161873 | 0.459661 | 2(Loss) | true |
