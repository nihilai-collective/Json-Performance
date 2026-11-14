
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 789.661 | 0.322555 | 8035.87ms | 65103 | 40 | 2.57269e+06 | 78625 | 0.0997284 | 3.84818 | 1(Win) | true |
| simdjson (ondemand) | 436.31 | 0.156687 | 7247.29ms | 65103 | 2560 | 1.27267e+08 | 142300 | 0.156742 | 6.96463 | 2(Loss) | true |
