
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 3299.83 | 0.22932 | 95.0032ms | 2889 | 4890 | 17927 | 834.943 | 4.00785 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3152.21 | 2.28948 | 89.9455ms | 2889 | 640 | 256282 | 874.042 | 0.624443 | 1(Tie) | true |
| Jsonifier | 3081.16 | 0.311488 | 94.8241ms | 2889 | 2560 | 19860.6 | 894.198 | 0.433384 | 3(Loss) | true |
| Glaze | 2068.85 | 0.118221 | 154.042ms | 2889 | 320 | 793.196 | 1331.74 | 0.155819 | 4(Loss) | true |
