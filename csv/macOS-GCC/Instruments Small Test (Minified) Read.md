
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1151.02 | 0.247063 | 391.223ms | 4669 | 2560 | 233852 | 3868.5 | 0.157436 | 1(Win) | true |
| simdjson (ondemand) | 1046.39 | 0.176163 | 430.955ms | 4669 | 4890 | 274790 | 4255.31 | 0.394148 | 2(Loss) | true |
