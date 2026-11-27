
----
### CitmCatalog Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14007.4 | 0.0439975 | 5419.55ms | 1439562 | 2560 | 4.76039e+06 | 98010.7 | 0.0810816 | 0.360954 | 1.39302 | 0.220363 | 0.000678186 | 0.0191336 | 8.46313e-06 | 1(Win) | true |
| Glaze | 5273.98 | 0.161575 | 6843.53ms | 1439584 | 320 | 5.66106e+07 | 260315 | 0.282266 | 0.954555 | 3.07321 | 0.528545 | 0.00100071 | 0.0627799 | 5.7382e-05 | 2(Loss) | true |
