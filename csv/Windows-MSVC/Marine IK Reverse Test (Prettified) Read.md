
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 898.731 | 0.593831 | 5513.92ms | 7351818 | 40 | 8.58451e+10 | 7.80126e+06 | 1.75401 | 3.3816 | 1(Win) | true |
| simdjson (ondemand) | 669.823 | 0.910546 | 7322.85ms | 7351818 | 40 | 3.63357e+11 | 1.04673e+07 | 0.6359 | 4.53737 | 2(Loss) | true |
