
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11053.1 | 0.231696 | 799.216ms | 6938 | 4890 | 9406.92 | 598.62 | 0.305429 | 0.488662 | 1.66388 | 0.29951 | 0.000144812 | 2.9711e-05 | 5.86557e-06 | 1(Win) | true |
| Glaze | 3554.27 | 0.202887 | 927.936ms | 6960 | 4890 | 70200 | 1867.49 | 0.327567 | 1.45558 | 3.8717 | 0.645259 | 0.000296847 | 3.14094e-05 | 9.25534e-06 | 2(Loss) | true |
