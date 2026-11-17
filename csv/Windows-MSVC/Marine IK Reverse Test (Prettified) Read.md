
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 699.54 | 1.38558 | 6967.49ms | 7351818 | 30 | 5.78565e+11 | 1.00226e+07 | 1.07961 | 3.53919 | 1(Win) | true |
| simdjson (ondemand) | 500.041 | 0.427788 | 10152.1ms | 7351818 | 40 | 1.43912e+11 | 1.40213e+07 | 0.915368 | 4.95123 | 2(Loss) | true |
