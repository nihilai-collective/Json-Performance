
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2932.33 | 0.0743481 | 3540.62ms | 108313 | 4890 | 3.35417e+06 | 35226.4 | 0.0144725 | 0.843665 | 1(Win) | true |
| Jsonifier (two-stage) | 2494.72 | 0.124222 | 4159.11ms | 108313 | 640 | 1.69316e+06 | 41405.6 | 0.0840137 | 0.991766 | 2(Loss) | true |
| simdjson (reflection) | 1611.96 | 0.0668684 | 6424.39ms | 108313 | 2560 | 4.70039e+06 | 64080.5 | 0.309093 | 1.53523 | 3(Loss) | true |
| Glaze | 1573.69 | 0.087994 | 6416.11ms | 108313 | 1280 | 4.27011e+06 | 65639 | 0.15842 | 1.57248 | 4(Loss) | true |
| simdjson (ondemand) | 1264.32 | 0.120741 | 8170.32ms | 108313 | 640 | 6.2278e+06 | 81700.4 | 0.156055 | 1.95755 | 5(Loss) | true |
