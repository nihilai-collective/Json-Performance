
----
### CitmCatalog Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10411.1 | 0.0711641 | 4615.71ms | 500299 | 2560 | 2.72287e+06 | 45828.1 | 0.0542827 | 0.237638 | 1(Win) | true |
| Glaze | 3743.09 | 0.138953 | 6434.06ms | 500299 | 320 | 1.0039e+07 | 127468 | 0.0571044 | 0.661216 | 2(Loss) | true |
