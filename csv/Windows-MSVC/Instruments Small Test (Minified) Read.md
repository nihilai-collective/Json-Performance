
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2312.62 | 0.146609 | 196.525ms | 4669 | 1280 | 10199.2 | 1925.39 | 0.198429 | 1.30007 | 1(Win) | true |
| Jsonifier (two-stage) | 1479.46 | 0.25315 | 299.99ms | 4669 | 640 | 37151.7 | 3009.69 | 0.0311397 | 2.04094 | 2(Loss) | true |
| Glaze | 1376.42 | 0.283269 | 329.916ms | 4669 | 40 | 3358.97 | 3235 | 0.0514933 | 2.20019 | 3(Loss) | true |
| simdjson (ondemand) | 881.424 | 0.0995296 | 510.231ms | 4669 | 2560 | 64717.6 | 5051.72 | 0.24683 | 3.43586 | 4(Loss) | true |
