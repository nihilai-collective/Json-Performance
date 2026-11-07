
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1612.02 | 0.0982926 | 291.247ms | 4669 | 320 | 2358.84 | 2762.19 | 0.0113148 | 1.52188 | 1(Win) | true |
| Jsonifier (two-stage) | 1181.68 | 0.0980741 | 404.754ms | 4669 | 160 | 2185.14 | 3768.12 | 0.0830013 | 2.07872 | 2(Loss) | true |
| Glaze | 1038.11 | 0.170495 | 453.533ms | 4669 | 4890 | 261512 | 4289.24 | 0.109502 | 2.3707 | 3(Loss) | true |
| simdjson (ondemand) | 755.346 | 0.337094 | 635.083ms | 4669 | 1280 | 505439 | 5894.92 | 0.0119262 | 3.26257 | 4(Loss) | true |
