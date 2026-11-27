
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1368.86 | 0.190607 | 8119.36ms | 7351818 | 80 | 7.62505e+09 | 5.12197e+06 | 0.573533 | 3.71887 | 16.1875 | 3.42781 | 0.0114719 | 0.18707 | 0.00385918 | 1(Win) | true |
| simdjson (ondemand) | 929.088 | 0.233126 | 5331.77ms | 7351818 | 40 | 1.23799e+10 | 7.54636e+06 | 0.0039301 | 5.47029 | 27.0836 | 5.31268 | 0.00970294 | 0.436166 | 0.00407739 | 2(Loss) | true |
