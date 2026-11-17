
----
### Marine IK Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1221.21 | 0.0638586 | 2174.76ms | 18245 | 320 | 26490.7 | 14248 | 0.00399164 | 4.22888 | 18.5921 | 3.8578 | 0.00502141 | 2.9974e-05 | 1.5929e-05 | 1(Win) | true |
| simdjson (ondemand) | 923.935 | 0.014007 | 2621.5ms | 18245 | 4890 | 34025.5 | 18832.3 | 0.0303367 | 5.57945 | 28.7775 | 5.63445 | 0.00593204 | 5.97413e-05 | 3.79183e-05 | 2(Loss) | true |
