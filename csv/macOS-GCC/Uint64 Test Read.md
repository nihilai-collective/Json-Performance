
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1818.66 | 1.99837 | 171.674ms | 3873 | 30 | 49415.7 | 2030.93 | 1.65289 | 1(Win) | true |
| Glaze | 1296.18 | 1.76166 | 273.635ms | 3873 | 160 | 403209 | 2849.6 | 0.735294 | 2(Loss) | true |
| Jsonifier (two-stage) | 670.877 | 1.73745 | 499.818ms | 3873 | 160 | 1.46405e+06 | 5505.6 | 1.85396 | 3(Loss) | true |
| simdjson (ondemand) | 416.244 | 0.902167 | 976.52ms | 3873 | 160 | 1.0254e+06 | 8873.6 | 1.28159 | 4(Loss) | true |
