
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7479.14 | 0.269835 | 774.572ms | 3223 | 1280 | 1574.08 | 410.969 | 0.0475475 | 0.743852 | 2.35774 | 0.410177 | 0.000450134 | 2.32702e-05 | 2.18159e-06 | 1(Win) | true |
| Glaze | 2765.18 | 0.22988 | 845.984ms | 3223 | 2560 | 16715.4 | 1111.57 | 0.104788 | 1.89792 | 5.21719 | 0.779088 | 0.000318027 | 5.13885e-05 | 6.18116e-06 | 2(Loss) | true |
