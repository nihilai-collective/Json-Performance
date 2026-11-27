
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9071.4 | 0.204611 | 753.219ms | 3223 | 30 | 14.4195 | 338.833 | 0.343137 | 0.64561 | 2.01644 | 0.245734 | 0.00031027 | 0.00013445 | 4.13693e-05 | 1(Win) | true |
| simdjson (reflection) | 7820.99 | 0.0697652 | 758.133ms | 3223 | 1280 | 96.2244 | 393.005 | 0.0686291 | 0.723001 | 2.29693 | 0.27583 | 0.000310512 | 1.76951e-05 | 2.42398e-06 | 2(Loss) | true |
| Glaze | 4086.84 | 0.213248 | 789.9ms | 3223 | 4890 | 12578.3 | 752.094 | 0.370741 | 1.34023 | 4.40242 | 0.633571 | 0.000311666 | 0.000111862 | 5.8818e-05 | 3(Loss) | true |
