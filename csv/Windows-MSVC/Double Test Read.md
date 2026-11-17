
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 493.679 | 0.676781 | 373.34ms | 1811 | 640 | 358777 | 3498.44 | 0.161045 | 6.11908 | 1(Win) | true |
| simdjson (ondemand) | 256.01 | 0.979569 | 688.341ms | 1811 | 320 | 1.39748e+06 | 6746.25 | 0.869078 | 11.832 | 2(Loss) | true |
