
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1478.4 | 0.130477 | 1176.57ms | 18245 | 640 | 150923 | 11769.4 | 0.0610322 | 2.05139 | 1(Win) | true |
| Jsonifier | 1241.2 | 0.0712481 | 1405.84ms | 18245 | 2560 | 255382 | 14018.5 | 0.0881308 | 2.44422 | 2(Loss) | true |
| Glaze | 878.334 | 0.128869 | 1990.43ms | 18245 | 30 | 19551.7 | 19810 | 0 | 3.45679 | 3(Loss) | true |
| simdjson (ondemand) | 554.273 | 0.0655035 | 3145.32ms | 18245 | 1280 | 541228 | 31392.1 | 0.165772 | 5.47951 | 4(Loss) | true |
