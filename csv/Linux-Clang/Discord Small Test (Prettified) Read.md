
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2118.84 | 0.194229 | 301.885ms | 6701 | 4890 | 167811 | 3016.07 | 0.66657 | 1.15757 | 1(Win) | true |
| Glaze | 1662.8 | 0.182827 | 386.07ms | 6701 | 4890 | 241427 | 3843.25 | 0.490569 | 1.47735 | 2(Loss) | true |
| Jsonifier | 1636.85 | 0.14408 | 397.029ms | 6701 | 4890 | 154731 | 3904.18 | 0.0500827 | 1.50118 | 3(Loss) | true |
| simdjson (ondemand) | 1092.94 | 0.262426 | 623.502ms | 6701 | 30 | 7063.5 | 5847.13 | 0.022798 | 2.25429 | 4(Loss) | true |
