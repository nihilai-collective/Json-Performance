
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1655.63 | 0.131827 | 1057.02ms | 18245 | 2560 | 491371 | 10509.5 | 0.131378 | 1.8317 | 1(Win) | true |
| Jsonifier | 1396.2 | 0.0560936 | 1254.08ms | 18245 | 4890 | 238963 | 12462.3 | 0.0407992 | 2.17211 | 2(Loss) | true |
| Glaze | 976.705 | 0.0432168 | 1790.16ms | 18245 | 4890 | 289851 | 17814.8 | 0.0619829 | 3.10791 | 3(Loss) | true |
| simdjson (ondemand) | 629.32 | 0.0875398 | 2769.8ms | 18245 | 2560 | 1.49967e+06 | 27648.6 | 0.0320608 | 4.82533 | 4(Loss) | true |
