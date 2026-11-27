
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2660.36 | 0.635488 | 5351.66ms | 1151920 | 80 | 5.50894e+08 | 412935 | 0.635468 | 1.14236 | 1(Win) | true |
| Jsonifier (two-stage) | 2590.99 | 0.553614 | 5389.63ms | 1151920 | 640 | 3.52622e+09 | 423992 | 0.592843 | 1.17279 | 2(Loss) | true |
| Glaze | 1477.27 | 0.625617 | 9379.41ms | 1151920 | 640 | 1.38524e+10 | 743641 | 0.00516856 | 2.05717 | 3(Loss) | true |
| simdjson (ondemand) | 1275.01 | 0.336944 | 5493.75ms | 1151920 | 80 | 6.74257e+08 | 861608 | 0.139469 | 2.38361 | 4(Loss) | true |
