
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5510.33 | 0 | 54.7332ms | 2889 | 30 | 0 | 500 | 0 | 0.428349 | 1(Win) | true |
| Jsonifier | 5363.67 | 0.187012 | 54.9253ms | 2889 | 1280 | 1181.19 | 513.672 | 0.136695 | 0.437025 | 2(Loss) | true |
| Glaze | 2900.99 | 0.43552 | 97.6729ms | 2889 | 4890 | 83662.2 | 949.734 | 0.128467 | 0.827639 | 3(Loss) | true |
| simdjson (ondemand) | 2819.48 | 0.240429 | 106.573ms | 2889 | 320 | 1766.36 | 977.188 | 0.0960307 | 0.855183 | 4(Loss) | true |
