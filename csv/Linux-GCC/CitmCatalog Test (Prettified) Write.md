
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18512.2 | 0.0375341 | 8246.89ms | 1439562 | 4890 | 3.78882e+06 | 74160.3 | 0.0169998 | 0.275876 | 0.694256 | 0.0753139 | 0.00050395 | 0.0187126 | 2.99384e-06 | 1(Win) | true |
| Glaze | 5775.71 | 0.0766274 | 6288.97ms | 1439584 | 1280 | 4.2466e+07 | 237701 | 0.321531 | 0.874589 | 3.12248 | 0.499194 | 0.000874132 | 0.0618603 | 1.07437e-05 | 2(Loss) | true |
| simdjson (reflection) | 575.822 | 1.02754 | 7333.94ms | 1439562 | 40 | 2.40075e+10 | 2.3842e+06 | 0.408509 | 8.71327 | 35.5653 | 6.42571 | 0.0157799 | 0.312585 | 0.000826571 | 3(Loss) | true |
