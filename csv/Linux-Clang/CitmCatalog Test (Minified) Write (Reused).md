
----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10054.5 | 0.0299039 | 5512.64ms | 500299 | 4890 | 984695 | 47453.5 | 0.020496 | 0.502731 | 2.2201 | 0.242137 | 0.00171541 | 0.00299855 | 1.20333e-05 | 1(Win) | true |
| Glaze | 5827.39 | 0.059503 | 8953.06ms | 500299 | 4890 | 1.16064e+07 | 81875.8 | 0.0921381 | 0.86636 | 4.17823 | 0.582038 | 0.00110908 | 0.00262959 | 3.306e-05 | 2(Loss) | true |
