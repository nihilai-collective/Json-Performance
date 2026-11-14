
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1587.64 | 0.266004 | 5665.36ms | 183677 | 320 | 2.75632e+07 | 110332 | 0.224102 | 1.91395 | 1(Win) | true |
| simdjson (ondemand) | 1447.16 | 0.0884709 | 6199.16ms | 183677 | 2560 | 2.93576e+07 | 121043 | 0.144365 | 2.09974 | 2(Loss) | true |
