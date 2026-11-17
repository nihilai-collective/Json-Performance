
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2310.43 | 0.272197 | 92.0741ms | 2158 | 4890 | 28747 | 890.755 | 0.00897377 | 1.03787 | 1(Win) | true |
| Jsonifier (two-stage) | 2097.49 | 0.108723 | 101.823ms | 2158 | 80 | 91.0403 | 981.188 | 0.0827393 | 1.14651 | 2(Loss) | true |
| Glaze | 1966.2 | 0.0588812 | 108.779ms | 2158 | 160 | 60.7748 | 1046.71 | 0.307756 | 1.22482 | 3(Loss) | true |
| simdjson (ondemand) | 1630.86 | 0.302836 | 129.039ms | 2158 | 40 | 584.174 | 1261.92 | 0.0508224 | 1.48372 | 4(Loss) | true |
| Jsonifier | 1590.59 | 0.0560954 | 134.709ms | 2158 | 320 | 168.574 | 1293.88 | 0.499536 | 1.52259 | 5(Loss) | true |
