
----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 965.259 | 0.365346 | 7154.01ms | 1151920 | 320 | 5.53243e+09 | 1.13809e+06 | 0.298397 | 3.14851 | 1(Win) | true |
| simdjson (ondemand) | 678.797 | 0.234903 | 5082.73ms | 1151920 | 160 | 2.3124e+09 | 1.61839e+06 | 0.20033 | 4.47719 | 2(Loss) | true |
