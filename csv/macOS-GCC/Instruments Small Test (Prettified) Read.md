
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1385.96 | 0.501072 | 543.42ms | 7932 | 640 | 478683 | 5458 | 0.626844 | 1(Win) | true |
| simdjson (ondemand) | 1212.36 | 0.29646 | 587.765ms | 7932 | 2560 | 875932 | 6239.5 | 1.60066 | 2(Loss) | true |
