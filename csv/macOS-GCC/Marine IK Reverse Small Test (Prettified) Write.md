
----
### Marine IK Reverse Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8071.75 | 0.313583 | 307.393ms | 24579 | 2560 | 212294 | 2904 | 0.966553 | 1(Win) | true |
| Glaze | 2962.04 | 1.07489 | 845.924ms | 24579 | 160 | 1.15771e+06 | 7913.6 | 3.77432 | 2(Loss) | true |
| simdjson (reflection) | 309.857 | 0.0737105 | 7795.95ms | 24893 | 4890 | 1.55955e+07 | 76615.3 | 0.130739 | 3(Loss) | true |
