
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 5864.8 | 0.251723 | 66.104ms | 3808 | 640 | 1554.94 | 619.219 | 0.126008 | 0.403638 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 5833.88 | 0.531991 | 73.1448ms | 3808 | 160 | 1754.72 | 622.5 | 0.201207 | 0.405119 | 1(Tie) | true |
| simdjson (ondemand) | 3365.51 | 0.211109 | 115.213ms | 3808 | 320 | 1660.56 | 1079.06 | 0.259965 | 0.717663 | 3(Loss) | true |
| Glaze | 3318.42 | 0.142963 | 115.286ms | 3808 | 320 | 783.307 | 1094.38 | 0.114351 | 0.724162 | 4(Loss) | true |
