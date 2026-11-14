
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 530.067 | 0.345068 | 9719.64ms | 409725 | 40 | 2.58817e+08 | 737160 | 0.346526 | 4.67039 | 1(Win) | true |
| simdjson (ondemand) | 246.579 | 0.3341 | 10255.7ms | 409725 | 30 | 8.40904e+08 | 1.58466e+06 | 0.953906 | 10.0401 | 2(Loss) | true |
