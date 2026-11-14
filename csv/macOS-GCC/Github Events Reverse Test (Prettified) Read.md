
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 981.471 | 0.123093 | 6480.28ms | 65103 | 640 | 3.88055e+06 | 63259.2 | 0.0341336 | 1(Win) | true |
| simdjson (ondemand) | 538.076 | 0.19829 | 6121.67ms | 65103 | 160 | 8.37601e+06 | 115387 | 0.184083 | 2(Loss) | true |
