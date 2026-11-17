
----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 823.582 | 0.106441 | 5386.89ms | 360584 | 320 | 6.32068e+07 | 417541 | 0.120634 | 3.00587 | 1(Win) | true |
| simdjson (ondemand) | 331.471 | 0.277772 | 6500.44ms | 360584 | 30 | 2.49126e+08 | 1.03743e+06 | 0.12605 | 7.46896 | 2(Loss) | true |
