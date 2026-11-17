
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1570.25 | 0.104852 | 9403.91ms | 1151920 | 320 | 1.72191e+08 | 699605 | 0.0534387 | 3.21808 | 15.7892 | 3.18802 | 0.00593913 | 0.0345924 | 1.2821e-05 | 1(Win) | true |
| simdjson (ondemand) | 970.373 | 0.513231 | 7479.42ms | 1151920 | 160 | 5.4015e+09 | 1.1321e+06 | 0.21553 | 5.22492 | 27.8221 | 5.58149 | 0.012822 | 0.0717891 | 3.94287e-05 | 2(Loss) | true |
