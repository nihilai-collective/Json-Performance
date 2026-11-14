
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 781.758 | 0.464526 | 9770.33ms | 4506447 | 80 | 5.21715e+10 | 5.49746e+06 | 0.979772 | 3.16684 | 1(Win) | true |
| simdjson (ondemand) | 647.909 | 0.703194 | 5690.95ms | 4506447 | 30 | 6.52698e+10 | 6.63315e+06 | 0.206461 | 3.82109 | 2(Loss) | true |
