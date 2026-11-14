
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.686 | 0.884545 | 5514.18ms | 7351818 | 40 | 1.96124e+11 | 7.91617e+06 | 1.78886 | 3.43143 | 1(Win) | true |
| simdjson (ondemand) | 668.548 | 0.63575 | 7342.65ms | 7351818 | 40 | 1.7781e+11 | 1.04873e+07 | 0.107404 | 4.54606 | 2(Loss) | true |
