
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 589.799 | 0.554081 | 8457.61ms | 7351818 | 30 | 1.30152e+11 | 1.18875e+07 | 0.169512 | 4.19764 | 1(Win) | true |
| simdjson (ondemand) | 443.942 | 0.576815 | 11048.6ms | 7351818 | 30 | 2.48961e+11 | 1.57932e+07 | 0.0116942 | 5.57679 | 2(Loss) | true |
