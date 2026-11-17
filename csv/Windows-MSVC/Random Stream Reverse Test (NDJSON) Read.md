
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 560.963 | 0.710313 | 5834.95ms | 4506447 | 40 | 1.18457e+11 | 7.66125e+06 | 0.163641 | 5.41803 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 371.599 | 0.650143 | 8378.8ms | 4506447 | 30 | 1.69613e+11 | 1.15654e+07 | 2.61265 | 8.17916 | -(Loss) | false |
