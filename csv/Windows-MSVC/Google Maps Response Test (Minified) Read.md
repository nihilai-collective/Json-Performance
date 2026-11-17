
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1282.42 | 0.172598 | 892.731ms | 11812 | 4890 | 1.124e+06 | 8783.99 | 0.294405 | 1.92401 | 1(Win) | true |
| Jsonifier (two-stage) | 1083.85 | 0.121471 | 1060.38ms | 11812 | 30 | 4781.61 | 10393.3 | 0.287816 | 2.27819 | 2(Loss) | true |
| Glaze | 856.639 | 0.198872 | 1387.64ms | 11812 | 30 | 20517.2 | 13150 | 0.0253421 | 2.88563 | 3(Loss) | true |
| simdjson (ondemand) | 532.577 | 0.218501 | 2130.67ms | 11812 | 1280 | 2.73399e+06 | 21151.5 | 0.0816951 | 4.64216 | 4(Loss) | true |
