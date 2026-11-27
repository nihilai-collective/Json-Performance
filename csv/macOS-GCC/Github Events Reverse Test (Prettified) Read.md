
----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1028.31 | 0.303081 | 6420.96ms | 65103 | 40 | 1.33946e+06 | 60377.6 | 0.247946 | 1(Win) | true |
| simdjson (ondemand) | 542.691 | 0.0599334 | 5975.28ms | 65103 | 2560 | 1.20358e+07 | 114406 | 0.187228 | 2(Loss) | true |
