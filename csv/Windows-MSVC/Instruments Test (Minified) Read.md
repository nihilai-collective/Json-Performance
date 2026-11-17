
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1997.05 | 0.197972 | 5119.65ms | 108313 | 640 | 6.71075e+06 | 51724.1 | 0.0640008 | 1.52113 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.98 | 0.199827 | 7126.71ms | 108313 | 30 | 604609 | 71043.3 | 0.0986286 | 2.09003 | 2(Loss) | true |
| Glaze | 1306.13 | 0.0553909 | 7928.47ms | 108313 | 640 | 1.22813e+06 | 79085 | 0.0854241 | 2.32633 | 3(Loss) | true |
| simdjson (ondemand) | 835.918 | 0.0431185 | 6326.69ms | 108313 | 2560 | 7.26778e+06 | 123571 | 0.0359608 | 3.63529 | 4(Loss) | true |
