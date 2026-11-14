
----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 743.371 | 0.609272 | 1198.69ms | 7932 | 40 | 153758 | 10176 | 0.209205 | 1(Win) | true |
| simdjson (ondemand) | 354.022 | 0.428844 | 2627.97ms | 7932 | 30 | 251899 | 21367.5 | 0.0399202 | 2(Loss) | true |
