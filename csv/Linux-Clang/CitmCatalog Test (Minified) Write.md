
----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10063.9 | 0.0884961 | 5519.11ms | 500299 | 640 | 1.12657e+06 | 47409.5 | 0.126709 | 0.50404 | 2.22115 | 0.242375 | 0.00176688 | 0.00327968 | 5.80903e-06 | 1(Win) | true |
| Glaze | 5068.67 | 0.067904 | 5216.89ms | 500299 | 2560 | 1.04593e+07 | 94131.6 | 0.039137 | 0.99636 | 4.19156 | 0.585182 | 0.00113306 | 0.0243559 | 2.93887e-05 | 2(Loss) | true |
