
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1166.4 | 0.669416 | 274.152ms | 3223 | 1280 | 398317 | 2635.2 | 2.34581 | 1(Win) | true |
| Jsonifier (two-stage) | 988.834 | 0.240969 | 316.198ms | 3223 | 2560 | 143627 | 3108.4 | 0.0514469 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 887.735 | 1.62146 | 363.4ms | 3223 | 80 | 252148 | 3462.4 | 0.368324 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 850.026 | 1.55462 | 378.506ms | 3223 | 80 | 252811 | 3616 | 0.35524 | 3(Tie) | true |
| simdjson (ondemand) | 824.311 | 0.375084 | 381.441ms | 3223 | 1280 | 250384 | 3728.8 | 0.182032 | 5(Loss) | true |
