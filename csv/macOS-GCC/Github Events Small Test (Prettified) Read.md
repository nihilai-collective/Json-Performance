
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1070.44 | 0.474059 | 192.523ms | 2158 | 2560 | 212659 | 1922.6 | 1.68746 | 1(Win) | true |
| simdjson (ondemand) | 1019.63 | 0.659453 | 223.287ms | 2158 | 2560 | 453547 | 2018.4 | 2.49848 | 2(Loss) | true |
