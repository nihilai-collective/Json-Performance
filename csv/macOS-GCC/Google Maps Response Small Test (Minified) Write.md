
----
### Google Maps Response Small Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9452.77 | 2.55141 | 46.6501ms | 4390 | 2560 | 326898 | 442.9 | 0.842441 | 1(Win) | true |
| simdjson (reflection) | 6660.25 | 5.25321 | 62.5549ms | 4390 | 1280 | 1.39575e+06 | 628.6 | 2.57833 | 2(Loss) | true |
| Glaze | 1635.2 | 0.385601 | 259.514ms | 4390 | 4890 | 476620 | 2560.31 | 0.951135 | 3(Loss) | true |
