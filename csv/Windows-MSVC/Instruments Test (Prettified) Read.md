
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1604.76 | 0.152381 | 5703.55ms | 183677 | 40 | 1.10664e+06 | 109155 | 1.56757 | 1.89349 | 1(Win) | true |
| simdjson (ondemand) | 1478.1 | 0.277146 | 6304.34ms | 183677 | 80 | 8.62992e+06 | 118509 | 0.142192 | 2.05579 | 2(Loss) | true |
