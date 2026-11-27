
----
### Github Events Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 886.814 | 0.307377 | 236.822ms | 2158 | 4890 | 248822 | 2320.7 | 0.535736 | 1(Win) | true |
| simdjson (ondemand) | 661.873 | 0.243946 | 312.922ms | 2158 | 2560 | 147292 | 3109.4 | 0.575754 | 2(Loss) | true |
