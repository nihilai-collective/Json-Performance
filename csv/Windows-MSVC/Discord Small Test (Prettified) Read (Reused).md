
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1697.49 | 0.0690819 | 421.807ms | 6701 | 4890 | 33075.2 | 3764.72 | 0.419835 | 1.78098 | 1(Win) | true |
| Jsonifier (two-stage) | 1576.62 | 0.228555 | 461.833ms | 6701 | 30 | 2574.71 | 4053.33 | 0.246103 | 1.92067 | 2(Loss) | true |
| Jsonifier | 1475.75 | 0.0697494 | 486.181ms | 6701 | 4890 | 44611.2 | 4330.39 | 0.266768 | 2.05017 | 3(Loss) | true |
| simdjson (ondemand) | 1253.98 | 0.0650838 | 551.41ms | 6701 | 4890 | 53796.4 | 5096.24 | 0.145595 | 2.41444 | 4(Loss) | true |
