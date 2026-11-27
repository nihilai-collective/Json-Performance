
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1041.93 | 0.389778 | 199.726ms | 2158 | 2560 | 151739 | 1975.2 | 0.893126 | 1(Win) | true |
| simdjson (ondemand) | 1006.08 | 0.620528 | 209.494ms | 2158 | 320 | 51560.2 | 2045.6 | 0.117463 | 2(Loss) | true |
