
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1201.32 | 0.174675 | 6813.95ms | 83958 | 1280 | 1.73491e+07 | 66650.5 | 0.252314 | 2.0598 | 1(Win) | true |
| simdjson (ondemand) | 1041.18 | 0.098584 | 7919.94ms | 83958 | 2560 | 1.47139e+07 | 76901.9 | 0.366965 | 2.37694 | 2(Loss) | true |
