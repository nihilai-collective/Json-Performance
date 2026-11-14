
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4204.95 | 0.619675 | 92.9331ms | 3808 | 4890 | 140059 | 863.647 | 0.658115 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4154.66 | 0.855157 | 91.221ms | 3808 | 2560 | 143039 | 874.1 | 0.828228 | 1(Tie) | true |
| Jsonifier | 4019.03 | 1.37795 | 100.352ms | 3808 | 640 | 99220.5 | 903.6 | 0.758252 | 3(Loss) | true |
| simdjson (ondemand) | 3159 | 1.98851 | 99.4399ms | 3808 | 320 | 167224 | 1149.6 | 2.7897 | 4(Loss) | true |
| Glaze | 2977.34 | 0.52862 | 125.871ms | 3808 | 4890 | 203298 | 1219.74 | 0.3722 | 5(Loss) | true |
