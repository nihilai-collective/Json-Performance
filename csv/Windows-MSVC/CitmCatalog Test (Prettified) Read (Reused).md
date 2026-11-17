
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2919.87 | 0.0968036 | 5280.37ms | 1151920 | 40 | 5.30592e+06 | 376235 | 0.0482621 | 1.04078 | 1(Win) | true |
| Jsonifier | 2616.93 | 0.0587842 | 5822.71ms | 1151920 | 160 | 9.74319e+06 | 419788 | 0.0206992 | 1.16134 | 2(Loss) | true |
| Glaze | 1657.63 | 0.0831295 | 8900.04ms | 1151920 | 160 | 4.85622e+07 | 662726 | 0.163074 | 1.83352 | 3(Loss) | true |
| simdjson (ondemand) | 1324.41 | 0.224761 | 5416.89ms | 1151920 | 80 | 2.78055e+08 | 829466 | 0.383792 | 2.29468 | 4(Loss) | true |
