
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1924.93 | 0.376643 | 9123.55ms | 183677 | 30 | 3.52418e+06 | 90999.5 | 0.150263 | 1(Win) | true |
| simdjson (ondemand) | 1700.63 | 0.195213 | 5234.92ms | 183677 | 160 | 6.46886e+06 | 103002 | 0.146231 | 2(Loss) | true |
