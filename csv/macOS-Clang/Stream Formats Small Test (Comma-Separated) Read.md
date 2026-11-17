
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1744.08 | 0.463168 | 5898.9ms | 16002591 | 40 | 6.57028e+10 | 8.75032e+06 | 0.312406 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1225.54 | 0.413242 | 8524.54ms | 16002591 | 40 | 1.05924e+11 | 1.24527e+07 | 8.98972 | -(Loss) | false |
