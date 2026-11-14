
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11359.3 | 0.116309 | 1559.05ms | 183677 | 1280 | 411760 | 15420.7 | 0.340084 | 0.266875 | 1(Win) | true |
| simdjson (stage-1) | 10978 | 0.144337 | 1604.72ms | 183677 | 160 | 84866.4 | 15956.2 | 0.172644 | 0.276135 | 2(Loss) | true |
