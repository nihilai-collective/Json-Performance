
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4010.59 | 0.852986 | 103.465ms | 3808 | 30 | 1789.71 | 905.5 | 0.454848 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3973.73 | 0.433652 | 109.023ms | 3808 | 30 | 471.197 | 913.9 | 0.152955 | 1(Tie) | true |
| Jsonifier | 3806.81 | 0.24031 | 102.75ms | 3808 | 2560 | 13454.1 | 953.972 | 1.12788 | 3(Loss) | true |
| Glaze | 2468.96 | 0.240561 | 162.129ms | 3808 | 30 | 375.61 | 1470.9 | 0.650666 | 4(Loss) | true |
