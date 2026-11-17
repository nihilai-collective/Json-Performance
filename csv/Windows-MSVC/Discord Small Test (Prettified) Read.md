
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1093.65 | 0.227441 | 622.077ms | 6701 | 30 | 5298.85 | 5843.33 | 0.397727 | 2.25429 | 1(Win) | true |
| Jsonifier | 1065.1 | 0.139065 | 656.375ms | 6701 | 80 | 5569.62 | 6000 | 0.0834028 | 2.31511 | 2(Loss) | true |
| Glaze | 1017.11 | 0.251104 | 658.505ms | 6701 | 2560 | 637219 | 6283.05 | 0.0435388 | 2.42225 | 3(Loss) | true |
| simdjson (ondemand) | 853.214 | 0.256547 | 784.142ms | 6701 | 40 | 14769.2 | 7490 | 0.178333 | 2.88392 | 4(Loss) | true |
