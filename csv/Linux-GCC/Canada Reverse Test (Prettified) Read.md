
----
### Canada Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1642.56 | 0.108718 | 9499.66ms | 5212421 | 160 | 1.73206e+09 | 3.02635e+06 | 3.00174 | 1.50725 | -(Win) | false |
| simdjson (ondemand) | 1491.36 | 0.391539 | 10328.4ms | 5212421 | 30 | 5.10958e+09 | 3.33317e+06 | 1.11456 | 1.66008 | 2(Loss) | true |
