
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1063.41 | 0.205268 | 201.999ms | 2158 | 320 | 5050.06 | 1935.31 | 0.402059 | 2.29022 | 1(Win) | true |
| Jsonifier | 909.878 | 0.159875 | 237.138ms | 2158 | 320 | 4184.56 | 2261.88 | 0.11065 | 2.68473 | 2(Loss) | true |
| Glaze | 740.298 | 0.134562 | 173.111ms | 2158 | 160 | 2238.99 | 2780 | 0.269058 | 3.30162 | 3(Loss) | true |
| simdjson (ondemand) | 679.966 | 0.314175 | 342.728ms | 2158 | 30 | 2712.64 | 3026.67 | 0 | 3.59314 | 4(Loss) | true |
