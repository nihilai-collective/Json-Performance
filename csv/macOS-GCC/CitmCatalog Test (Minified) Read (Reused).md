
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2405.01 | 1.24787 | 6683.22ms | 500299 | 40 | 2.45148e+08 | 198387 | 0.736519 | 1(Win) | true |
| Glaze | 1436.49 | 0.203718 | 5188.23ms | 500299 | 80 | 3.66269e+07 | 332144 | 2.86278 | 2(Loss) | true |
| Jsonifier (two-stage) | 1316.84 | 1.97571 | 10102ms | 500299 | 40 | 2.04975e+09 | 362323 | 2.11234 | 3(Loss) | true |
| simdjson (reflection) | 1164.73 | 0.632596 | 6416.01ms | 500299 | 30 | 2.01458e+08 | 409643 | 1.88444 | 4(Loss) | true |
| simdjson (ondemand) | 1047.94 | 0.386488 | 6103.07ms | 500299 | 640 | 1.98169e+09 | 455295 | 0.792536 | 5(Loss) | true |
