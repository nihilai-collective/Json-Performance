
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4626.79 | 0.531394 | 6732.25ms | 631514 | 640 | 3.0621e+08 | 130168 | 1.15515 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 4569.1 | 1.02469 | 6833.76ms | 631514 | 80 | 1.45941e+08 | 131811 | 0.461553 | 1(Tie) | true |
| simdjson (ondemand) | 4138.11 | 0.247589 | 7440.42ms | 631514 | 1280 | 1.66201e+08 | 145540 | 0.339752 | 3(Loss) | true |
| simdjson (reflection) | 3897.54 | 0.336064 | 7821.05ms | 631514 | 2560 | 6.9035e+08 | 154523 | 1.35221 | 4(Loss) | true |
| Glaze | 2896.08 | 0.341175 | 5255.23ms | 631514 | 320 | 1.61084e+08 | 207957 | 1.06844 | 5(Loss) | true |
