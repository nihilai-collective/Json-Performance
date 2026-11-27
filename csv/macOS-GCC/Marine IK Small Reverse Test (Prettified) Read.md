
----
### Marine IK Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 840.992 | 0.305481 | 2092.58ms | 18245 | 2560 | 1.02262e+07 | 20689.6 | 1.86803 | 1(Win) | true |
| simdjson (ondemand) | 622.773 | 0.194449 | 2899.18ms | 18245 | 640 | 1.88894e+06 | 27939.2 | 0.0944017 | 2(Loss) | true |
