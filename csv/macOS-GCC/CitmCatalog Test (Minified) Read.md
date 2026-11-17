
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1825.77 | 0.29897 | 6999.72ms | 500299 | 1280 | 7.81323e+08 | 261326 | 1.88664 | 1(Win) | true |
| Glaze | 1194.59 | 1.22941 | 5355.29ms | 500299 | 30 | 7.23328e+08 | 399403 | 0.766432 | 2(Loss) | true |
| Jsonifier (two-stage) | 1101.38 | 2.01838 | 5052.17ms | 500299 | 40 | 3.05808e+09 | 433203 | 0.182858 | 3(Loss) | true |
| simdjson (ondemand) | 987.16 | 0.489708 | 6072.5ms | 500299 | 640 | 3.58541e+09 | 483328 | 0.499348 | 4(Loss) | true |
| simdjson (reflection) | 885.881 | 0.474089 | 6502.51ms | 500299 | 640 | 4.17262e+09 | 538585 | 1.53081 | 5(Loss) | true |
