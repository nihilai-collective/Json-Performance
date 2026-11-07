
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1505.56 | 0.188057 | 309.47ms | 4669 | 80 | 2474.68 | 2957.5 | 0 | 1.62763 | 1(Win) | true |
| Jsonifier (two-stage) | 1129.14 | 0.149042 | 433.281ms | 4669 | 320 | 11054 | 3943.44 | 0.00792393 | 2.17584 | 2(Loss) | true |
| Glaze | 936.754 | 0.219453 | 496.109ms | 4669 | 30 | 3264.37 | 4753.33 | 0.209937 | 2.62727 | 3(Loss) | true |
| simdjson (ondemand) | 752.57 | 0.116965 | 625.945ms | 4669 | 30 | 1436.78 | 5916.67 | 0.339175 | 3.26767 | 4(Loss) | true |
