
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 679.587 | 0.151435 | 650.019ms | 4630 | 1280 | 123918 | 6497.34 | 0.510007 | 4.45899 | 1(Win) | true |
| Jsonifier (two-stage) | 641.87 | 0.0825985 | 691.443ms | 4630 | 2560 | 82651.9 | 6879.14 | 0.0748987 | 4.7211 | 2(Loss) | true |
| simdjson (ondemand) | 361.883 | 0.0828077 | 1228.52ms | 4630 | 1280 | 130670 | 12201.5 | 0.0326442 | 8.38366 | 3(Loss) | true |
| Glaze | 349.328 | 0.134646 | 1276.97ms | 4630 | 30 | 8689.66 | 12640 | 0.0790514 | 8.68444 | 4(Loss) | true |
