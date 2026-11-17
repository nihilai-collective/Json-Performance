
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2452.11 | 0.287215 | 9548.54ms | 16002591 | 40 | 1.27812e+10 | 6.22372e+06 | 0.259811 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1311.45 | 0.230883 | 8263.11ms | 16002591 | 40 | 2.88747e+10 | 1.16369e+07 | 8.36775 | -(Loss) | false |
