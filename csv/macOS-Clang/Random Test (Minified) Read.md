
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1137.05 | 0.253574 | 5014.2ms | 461466 | 640 | 6.16465e+08 | 387044 | 0.148816 | 1(Win) | true |
| Jsonifier (two-stage) | 882.847 | 0.629894 | 6371.54ms | 461466 | 30 | 2.95778e+08 | 498488 | 0.47142 | 2(Loss) | true |
| Glaze | 753.572 | 0.483209 | 7572.67ms | 461466 | 320 | 2.5483e+09 | 584003 | 3.24873 | 3(Loss) | true |
| simdjson (ondemand) | 590.509 | 0.468051 | 9692.87ms | 461466 | 160 | 1.94685e+09 | 745270 | 0.114894 | 4(Loss) | true |
