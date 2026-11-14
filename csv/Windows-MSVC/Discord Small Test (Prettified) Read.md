
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1019.6 | 0.0997856 | 632.73ms | 6701 | 4890 | 191279 | 6267.75 | 0.124435 | 2.9705 | 1(Win) | true |
| Jsonifier (generic) | 1004.26 | 0.220457 | 643.983ms | 6701 | 640 | 125954 | 6363.44 | 0.00491063 | 3.01561 | 2(Loss) | true |
