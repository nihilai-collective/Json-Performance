
----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 682.404 | 0.26924 | 6513.19ms | 183677 | 1280 | 6.11387e+08 | 256693 | 2.68312 | 1(Win) | true |
| simdjson (ondemand) | 252.918 | 0.210104 | 8744.87ms | 183677 | 320 | 6.77592e+08 | 692587 | 0.0138093 | 2(Loss) | true |
