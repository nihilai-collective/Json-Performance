
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18444 | 0.175397 | 742.647ms | 3643 | 30 | 3.27471 | 188.367 | 0.373002 | 0.340864 | 1.13752 | 0.173758 | 0.000274499 | 9.14997e-06 | 9.14997e-06 | 1(Win) | true |
| Glaze | 4562.65 | 0.0967561 | 805.1ms | 3682 | 4890 | 2711.43 | 769.603 | 0.0887794 | 1.17372 | 3.92205 | 0.637154 | 0.000273758 | 3.12691e-05 | 1.18301e-05 | 2(Loss) | true |
| simdjson (reflection) | 545.406 | 0.0808168 | 1381.87ms | 3643 | 2560 | 67845.6 | 6369.99 | 0.0529363 | 9.29693 | 36.1073 | 7.56506 | 0.0144528 | 0.000215954 | 0.000105725 | 3(Loss) | true |
