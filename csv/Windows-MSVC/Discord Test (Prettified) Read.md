
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1230.04 | 0.130464 | 6528.78ms | 83958 | 640 | 4.61581e+06 | 65094.4 | 0.0264109 | 2.46997 | 1(Win) | true |
| simdjson (ondemand) | 1152.64 | 0.11218 | 7036.37ms | 83958 | 640 | 3.88642e+06 | 69465.6 | 0.045865 | 2.63588 | 2(Loss) | true |
