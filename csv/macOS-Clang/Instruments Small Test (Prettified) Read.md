
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2676.72 | 0.395345 | 333.509ms | 7932 | 40 | 4993.13 | 2826.05 | 0.0135624 | 1(Win) | true |
| Jsonifier (two-stage) | 2156.3 | 0.435795 | 358.565ms | 7932 | 1280 | 299172 | 3508.11 | 1.11297 | 2(Loss) | true |
| Glaze | 1572.2 | 0.709704 | 573.241ms | 7932 | 160 | 186563 | 4811.44 | 1.27296 | 3(Loss) | true |
| simdjson (ondemand) | 820.597 | 0.479409 | 933.424ms | 7932 | 4890 | 9.55054e+06 | 9218.34 | 0.960317 | 4(Loss) | true |
