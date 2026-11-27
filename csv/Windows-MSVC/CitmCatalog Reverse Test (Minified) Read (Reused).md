
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 493.997 | 0.182447 | 6386.7ms | 500299 | 30 | 9.31549e+07 | 965840 | 0.136138 | 6.15226 | 1(Win) | true |
| simdjson (ondemand) | 313.941 | 0.17549 | 9806.28ms | 500299 | 320 | 2.27625e+09 | 1.51978e+06 | 0.0186739 | 9.68103 | 2(Loss) | true |
