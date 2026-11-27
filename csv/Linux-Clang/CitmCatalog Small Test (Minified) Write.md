
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7604.27 | 0.240826 | 775.394ms | 3223 | 320 | 303.224 | 404.206 | 0.246788 | 0.737706 | 2.42166 | 0.319268 | 0.000466374 | 3.97533e-05 | 9.69594e-06 | 1(Win) | true |
| Glaze | 2856.86 | 0.21875 | 845.235ms | 3223 | 2560 | 14180.1 | 1075.9 | 0.0998346 | 1.8369 | 5.18275 | 0.772263 | 0.000316815 | 6.24176e-05 | 2.04827e-05 | 2(Loss) | true |
