
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 445.089 | 0.716235 | 8116.1ms | 5212421 | 30 | 1.91963e+11 | 1.11684e+07 | 3.91406 | 5.56238 | -(Win) | false |
| simdjson (ondemand) | 409.118 | 1.17276 | 8604.15ms | 5212421 | 40 | 8.12188e+11 | 1.21504e+07 | 1.53786 | 6.05141 | 2(Loss) | true |
