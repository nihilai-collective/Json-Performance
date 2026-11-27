
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2576.85 | 0.0663301 | 5522.64ms | 1151920 | 640 | 5.11762e+07 | 426318 | 0.712945 | 1.97371 | 8.56124 | 1.44239 | 0.00756694 | 0.0369119 | 3.7348e-05 | 1(Win) | true |
| simdjson (ondemand) | 2416.81 | 0.122236 | 6026.62ms | 1151920 | 80 | 2.4697e+07 | 454548 | 0.155818 | 2.09957 | 8.77842 | 1.3344 | 0.00961518 | 0.0366848 | 3.00043e-05 | 2(Loss) | true |
