
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1780.46 | 0.0502018 | 430.942ms | 7932 | 160 | 727.879 | 4248.64 | 0.0410594 | 1(Win) | true |
| simdjson (ondemand) | 1670.18 | 0.115112 | 469.354ms | 7932 | 40 | 1087.28 | 4529.18 | 0.0630696 | 2(Loss) | true |
