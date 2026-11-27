
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5046.67 | 0.294046 | 58.6757ms | 2889 | 1280 | 3298.57 | 545.938 | 0.633641 | 0.582586 | 1(Win) | true |
| Jsonifier (two-stage) | 4972.23 | 0.172658 | 58.0419ms | 2889 | 4890 | 4475.84 | 554.11 | 0.4755 | 0.591204 | 2(Loss) | true |
| simdjson (ondemand) | 3685.84 | 0.751626 | 71.4425ms | 2889 | 80 | 2525.32 | 747.5 | 0 | 0.798308 | 3(Loss) | true |
| Glaze | 3037.04 | 0.215101 | 97.2742ms | 2889 | 1280 | 4874.02 | 907.188 | 0.137979 | 0.98028 | 4(Loss) | true |
