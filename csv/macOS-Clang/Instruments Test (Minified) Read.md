
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2772.92 | 0.0376208 | 3768.5ms | 108313 | 80 | 15712.1 | 37251.5 | 0.0520513 | 1(Win) | true |
| Jsonifier (two-stage) | 1749.19 | 0.221179 | 6151.06ms | 108313 | 160 | 2.72958e+06 | 59053.1 | 0.115398 | 2(Loss) | true |
| Glaze | 1537.92 | 0.149495 | 6925.12ms | 108313 | 320 | 3.22623e+06 | 67165.5 | 0.305818 | 3(Loss) | true |
| simdjson (ondemand) | 686.493 | 0.0622316 | 8287.81ms | 108313 | 1280 | 1.12233e+07 | 150468 | 0.286536 | 4(Loss) | true |
