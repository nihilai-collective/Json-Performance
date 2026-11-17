
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2475.44 | 0.0669144 | 7197.85ms | 360584 | 2560 | 2.21201e+07 | 138917 | 0.0131878 | 0.999908 | 1(Win) | true |
| Jsonifier (generic) | 2187.44 | 0.112616 | 8024.15ms | 360584 | 1280 | 4.01193e+07 | 157206 | 0.00340776 | 1.13152 | 2(Loss) | true |
