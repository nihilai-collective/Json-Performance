
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1957.87 | 0.0722639 | 5266.98ms | 108313 | 4890 | 7.10797e+06 | 52759.1 | 0.133057 | 1.26392 | 1(Win) | true |
| simdjson (ondemand) | 1727.92 | 0.185822 | 6040.74ms | 108313 | 320 | 3.94873e+06 | 59780.2 | 0.0755471 | 1.43221 | 2(Loss) | true |
