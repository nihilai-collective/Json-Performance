
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1713.99 | 0.103448 | 475.731ms | 7932 | 40 | 833.789 | 4413.43 | 0.135199 | 1(Win) | true |
| simdjson (ondemand) | 1631.89 | 0.0465468 | 469.221ms | 7932 | 160 | 744.879 | 4635.46 | 0.0122711 | 2(Loss) | true |
