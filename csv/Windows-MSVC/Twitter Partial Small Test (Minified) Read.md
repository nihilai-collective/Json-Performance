
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4653.44 | 0.119311 | 61.851ms | 2889 | 2560 | 1277.46 | 592.07 | 0.348455 | 0.632367 | 1(Win) | true |
| Jsonifier (two-stage) | 4622.03 | 0.109875 | 62.2843ms | 2889 | 4890 | 2097.65 | 596.094 | 0.124717 | 0.637829 | 2(Loss) | true |
| simdjson (ondemand) | 3754.74 | 0.133201 | 75.4991ms | 2889 | 4890 | 4671.51 | 733.783 | 0.308599 | 0.789871 | 3(Loss) | true |
| Glaze | 2836.72 | 0.369557 | 100.409ms | 2889 | 160 | 2061.32 | 971.25 | 0.517464 | 1.04649 | 4(Loss) | true |
