
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 824.93 | 0.887474 | 8935.63ms | 4506447 | 30 | 6.41308e+10 | 5.20975e+06 | 1.43087 | 3.00119 | 1(Win) | true |
| simdjson (ondemand) | 673.405 | 0.78058 | 10935.9ms | 4506447 | 80 | 1.98537e+11 | 6.38202e+06 | 0.513117 | 3.67653 | 2(Loss) | true |
