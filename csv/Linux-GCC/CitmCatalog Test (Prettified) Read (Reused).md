
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3302.09 | 0.060325 | 9606.44ms | 1151920 | 1280 | 5.1555e+07 | 332685 | 0.0660362 | 1.54037 | 7.35976 | 1.22816 | 0.00526904 | 0.0319592 | 2.88689e-05 | 1(Win) | true |
| simdjson (ondemand) | 2650.61 | 1.06288 | 5853.73ms | 1151920 | 80 | 1.55242e+09 | 414454 | 0.637467 | 1.91261 | 7.96665 | 1.24336 | 0.00824682 | 0.0311708 | 1.8697e-05 | 2(Loss) | true |
