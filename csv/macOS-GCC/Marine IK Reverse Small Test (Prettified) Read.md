
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1801.84 | 0.108584 | 1037.34ms | 18245 | 4890 | 537648 | 9656.7 | 0.627752 | 1(Win) | true |
| simdjson (reflection) | 1761.97 | 0.57134 | 1016.08ms | 18245 | 40 | 127333 | 9875.2 | 0.237069 | 2(Loss) | true |
| Jsonifier | 1707.87 | 0.364653 | 1021.69ms | 18245 | 320 | 441659 | 10188 | 0.370429 | 3(Loss) | true |
| simdjson (ondemand) | 1318.66 | 0.0860785 | 1326.91ms | 18245 | 4890 | 630847 | 13195.1 | 0.260036 | 4(Loss) | true |
| Glaze | 1268.76 | 0.304485 | 1382.64ms | 18245 | 640 | 1.11594e+06 | 13714 | 0.0320737 | 5(Loss) | true |
