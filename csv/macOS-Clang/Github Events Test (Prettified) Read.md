
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1842.8 | 0.256099 | 3383.42ms | 65103 | 160 | 1.19119e+06 | 33691.6 | 0.037106 | 1(Win) | true |
| Jsonifier (two-stage) | 1770.86 | 0.019504 | 3603.51ms | 65103 | 80 | 3740.86 | 35060.4 | 0.0564345 | 2(Loss) | true |
| Glaze | 1702.63 | 0.054399 | 3730.39ms | 65103 | 4890 | 1.92422e+06 | 36465.5 | 0.0168253 | 3(Loss) | true |
| simdjson (ondemand) | 1066.48 | 0.0509475 | 6028.06ms | 65103 | 4890 | 4.30179e+06 | 58216.6 | 0.0578731 | 4(Loss) | true |
