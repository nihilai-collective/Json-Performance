
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 918.328 | 0.758165 | 5286.38ms | 7351818 | 30 | 1.00518e+11 | 7.63479e+06 | 0.445735 | 3.3095 | 1(Win) | true |
| simdjson (ondemand) | 665.49 | 1.0523 | 7195.91ms | 7351818 | 30 | 3.68729e+11 | 1.05354e+07 | 0.134902 | 4.56703 | 2(Loss) | true |
