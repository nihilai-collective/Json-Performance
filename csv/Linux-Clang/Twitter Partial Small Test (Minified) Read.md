
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7098.65 | 0.198331 | 40.3696ms | 2889 | 40 | 23.7019 | 388.125 | 0.0279042 | 0.324152 | 1(Win) | true |
| Jsonifier (two-stage) | 7047.06 | 0.224621 | 41.4712ms | 2889 | 30 | 23.1368 | 390.967 | 0.0938727 | 0.326953 | 2(Loss) | true |
| simdjson (ondemand) | 6923.11 | 0.320455 | 42.734ms | 2889 | 30 | 48.792 | 397.967 | 0.167238 | 0.335918 | 3(Loss) | true |
| Glaze | 3416.73 | 0.0790616 | 84.4553ms | 2889 | 80 | 32.5158 | 806.375 | 0.139708 | 0.701138 | 4(Loss) | true |
