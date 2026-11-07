
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3746.94 | 0.0786944 | 4680.88ms | 183677 | 4890 | 6.6184e+06 | 46749.6 | 0.083361 | 0.660351 | 1(Win) | true |
| Jsonifier | 2276.09 | 0.043812 | 7704.87ms | 183677 | 4890 | 5.5594e+06 | 76960.2 | 0.0128982 | 1.08737 | 2(Loss) | true |
| Glaze | 2268.18 | 0.0781481 | 7745.43ms | 183677 | 640 | 2.33115e+06 | 77228.4 | 0.0177182 | 1.09117 | 3(Loss) | true |
| simdjson (ondemand) | 1182.01 | 0.0409248 | 7571.32ms | 183677 | 2560 | 9.41635e+06 | 148195 | 0.15774 | 2.0942 | 4(Loss) | true |
