
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1533.42 | 0.133057 | 6797.61ms | 108313 | 4890 | 3.92847e+07 | 67362.9 | 0.530958 | 1.6138 | 1(Win) | true |
| Jsonifier (two-stage) | 1143.23 | 0.336501 | 9260.21ms | 108313 | 160 | 1.47906e+07 | 90353.8 | 0.212117 | 2.16474 | 2(Loss) | true |
| Glaze | 964.836 | 0.340077 | 5557.84ms | 108313 | 80 | 1.06047e+07 | 107060 | 0.160865 | 2.56555 | 3(Loss) | true |
| simdjson (ondemand) | 805.814 | 0.761437 | 6537.68ms | 108313 | 40 | 3.81083e+07 | 128188 | 0.0578915 | 3.0716 | 4(Loss) | true |
