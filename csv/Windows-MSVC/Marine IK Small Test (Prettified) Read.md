
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1642.26 | 0.0785738 | 1125.74ms | 18245 | 80 | 5544.3 | 10595 | 0.39953 | 1.84717 | 1(Win) | true |
| Jsonifier | 1471.75 | 0.111227 | 1266.87ms | 18245 | 40 | 6916.67 | 11822.5 | 0.817953 | 2.06027 | 2(Loss) | true |
| simdjson (ondemand) | 1095.43 | 0.840191 | 1616.06ms | 18245 | 4890 | 8.70933e+07 | 15884 | 1.36454 | 2.76987 | 3(Loss) | true |
| Glaze | 927.165 | 0.135993 | 1982.6ms | 18245 | 30 | 19540.2 | 18766.7 | 0.23144 | 3.27591 | 4(Loss) | true |
