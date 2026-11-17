
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2717.28 | 0.277236 | 6476.82ms | 183677 | 320 | 1.02209e+07 | 64464.5 | 0.342686 | 0.910757 | 1(Win) | true |
| Jsonifier (generic) | 2598.26 | 0.408536 | 6781.52ms | 183677 | 160 | 1.21374e+07 | 67417.5 | 0.742343 | 0.95247 | 2(Loss) | true |
