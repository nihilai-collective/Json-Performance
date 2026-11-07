
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2370.2 | 0.0761978 | 273.752ms | 6701 | 80 | 337.663 | 2696.21 | 0.0319791 | 1.03392 | 1(Win) | true |
| Glaze | 1888.68 | 0.0997451 | 338.885ms | 6701 | 40 | 455.625 | 3383.62 | 0.0238839 | 1.30049 | 2(Loss) | true |
| Jsonifier | 1777.57 | 0.0994816 | 363.059ms | 6701 | 40 | 511.651 | 3595.12 | 0.0368691 | 1.38283 | 3(Loss) | true |
| simdjson (ondemand) | 1109.51 | 0.220753 | 582.853ms | 6701 | 1280 | 206938 | 5759.82 | 0.394616 | 2.22124 | 4(Loss) | true |
