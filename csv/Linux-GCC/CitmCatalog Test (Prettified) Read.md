
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3619.07 | 0.219909 | 7789.78ms | 1151920 | 40 | 1.78236e+07 | 303546 | 0.970088 | 0.684014 | 1(Win) | true |
| Jsonifier | 3199.14 | 0.171913 | 8876.86ms | 1151920 | 1280 | 4.46071e+08 | 343391 | 0.280686 | 0.773826 | 2(Loss) | true |
| simdjson (ondemand) | 3110.67 | 0.0452135 | 9004.96ms | 1151920 | 1280 | 3.2635e+07 | 353157 | 0.0455684 | 0.795823 | 3(Loss) | true |
| simdjson (reflection) | 3055.85 | 0.0701568 | 9155.04ms | 1151920 | 1280 | 8.14199e+07 | 359493 | 0.185024 | 0.8101 | 4(Loss) | true |
| Glaze | 2476.58 | 0.0652131 | 5623.45ms | 1151920 | 640 | 5.35539e+07 | 443579 | 0.387477 | 0.999612 | 5(Loss) | true |
