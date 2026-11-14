
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1597.8 | 0.079461 | 6461.67ms | 108313 | 2560 | 6.75558e+06 | 64648.3 | 0.489026 | 1.54883 | 1(Win) | true |
| Jsonifier (generic) | 1544.18 | 0.109524 | 6733.86ms | 108313 | 1280 | 6.87057e+06 | 66893.2 | 0.642628 | 1.6026 | 2(Loss) | true |
