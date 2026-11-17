
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1588.54 | 0.208709 | 1106.43ms | 18245 | 30 | 15678.2 | 10953.3 | 0.182927 | 1.55306 | 1(Win) | true |
| Jsonifier | 1279.63 | 0.704662 | 1385.86ms | 18245 | 160 | 1.46892e+06 | 13597.5 | 0.584902 | 1.9288 | 2(Loss) | true |
| Glaze | 541.744 | 0.081263 | 3220.06ms | 18245 | 4890 | 3.33115e+06 | 32118.1 | 0.164741 | 4.56351 | 3(Loss) | true |
| simdjson (ondemand) | 354.014 | 0.341963 | 4950.09ms | 18245 | 160 | 4.51987e+06 | 49150 | 0.195446 | 6.98993 | 4(Loss) | true |
