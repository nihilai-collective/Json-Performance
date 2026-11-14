
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 972.29 | 0.567416 | 5088.95ms | 7351818 | 40 | 6.69671e+10 | 7.21106e+06 | 4.95565 | 1(Win) | true |
| simdjson (ondemand) | 597.283 | 0.758623 | 8284.24ms | 7351818 | 40 | 3.17206e+11 | 1.17385e+07 | 2.25099 | 2(Loss) | true |
