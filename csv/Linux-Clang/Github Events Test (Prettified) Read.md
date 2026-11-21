
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2207.21 | 0.366903 | 2870.1ms | 65103 | 320 | 3.40855e+06 | 28129.3 | 0.0147666 | 1.12064 | 1(Win) | true |
| Glaze | 1662.11 | 0.20678 | 3827.92ms | 65103 | 640 | 3.81839e+06 | 37354.4 | 0.0555099 | 1.48854 | 2(Loss) | true |
| Jsonifier | 1571.59 | 0.322128 | 3845.59ms | 65103 | 320 | 5.18238e+06 | 39505.8 | 0.202508 | 1.5742 | 3(Loss) | true |
| simdjson (ondemand) | 1213.27 | 0.1052 | 5253.4ms | 65103 | 2560 | 7.4192e+06 | 51173.4 | 0.0316106 | 2.03951 | 4(Loss) | true |
