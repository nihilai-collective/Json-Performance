
----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 800.509 | 0.448843 | 250.641ms | 2158 | 2560 | 340878 | 2570.9 | 2.87715 | 1(Win) | true |
| simdjson (ondemand) | 647.138 | 0.393215 | 352.941ms | 2158 | 1280 | 200161 | 3180.2 | 0.119347 | 2(Loss) | true |
