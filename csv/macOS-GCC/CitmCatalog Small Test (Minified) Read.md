
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1107.64 | 0.663877 | 287.862ms | 3223 | 1280 | 434422 | 2775 | 0.480562 | 1(Win) | true |
| Jsonifier (two-stage) | 802.717 | 0.589198 | 372.6ms | 3223 | 4890 | 2.48902e+06 | 3829.11 | 0.242006 | 2(Loss) | true |
| Glaze | 745.648 | 0.278356 | 402.26ms | 3223 | 4890 | 643817 | 4122.18 | 2.14277 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 672.875 | 1.35768 | 482.091ms | 3223 | 160 | 615418 | 4568 | 1.48378 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 663.406 | 0.530735 | 458.613ms | 3223 | 2560 | 1.54795e+06 | 4633.2 | 2.70066 | 4(Tie) | true |
