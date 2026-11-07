
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 515.116 | 0.165972 | 906.426ms | 4604 | 80 | 16011.1 | 8523.75 | 0.219491 | 4.79246 | 1(Win) | true |
| Jsonifier (two-stage) | 460.243 | 0.218204 | 979.188ms | 4604 | 40 | 17333.3 | 9540 | 0.0699301 | 5.36151 | 2(Loss) | true |
| simdjson (ondemand) | 183.731 | 0.120837 | 2464.38ms | 4604 | 2560 | 2.13474e+06 | 23897.5 | 0.0544612 | 13.4579 | 3(Loss) | true |
| Glaze | 162.754 | 0.128255 | 2734.73ms | 4604 | 2560 | 3.06477e+06 | 26977.7 | 0.080297 | 15.1939 | 4(Loss) | true |
