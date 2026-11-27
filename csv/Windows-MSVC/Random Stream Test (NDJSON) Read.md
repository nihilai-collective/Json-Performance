
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 666.213 | 0.461209 | 6965.53ms | 4506447 | 40 | 3.54077e+10 | 6.45091e+06 | 3.13965 | 3.71611 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 580.072 | 0.616544 | 7718.42ms | 4506447 | 40 | 8.34628e+10 | 7.40888e+06 | 17.089 | 4.26789 | -(Loss) | false |
