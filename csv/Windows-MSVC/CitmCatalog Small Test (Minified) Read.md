
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 717.624 | 0.181269 | 432.203ms | 3223 | 4890 | 294770 | 4283.15 | 0.0261099 | 3.41447 | 1(Win) | true |
| Jsonifier (two-stage) | 636.391 | 0.191672 | 500.561ms | 3223 | 4890 | 419081 | 4829.88 | 0.112406 | 3.85473 | 2(Loss) | true |
| Glaze | 460.729 | 0.266155 | 681.422ms | 3223 | 2560 | 807124 | 6671.37 | 0.135074 | 5.33822 | 3(Loss) | true |
| simdjson (ondemand) | 425.94 | 0.363111 | 731.947ms | 3223 | 1280 | 878844 | 7216.25 | 0.319308 | 5.7909 | 4(Loss) | true |
