
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1695.92 | 0.38514 | 215.524ms | 3770 | 40 | 2666.67 | 2120 | 0 | 1.77871 | 1(Win) | true |
| simdjson (ondemand) | 1593.21 | 0.407764 | 228.89ms | 3770 | 30 | 2540.23 | 2256.67 | 0 | 1.89327 | 2(Loss) | true |
