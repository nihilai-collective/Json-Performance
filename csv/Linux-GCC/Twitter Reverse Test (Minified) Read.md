
----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 708.776 | 0.0714088 | 9304.67ms | 264040 | 640 | 4.11912e+07 | 355272 | 0.0151938 | 7.18608 | 27.4563 | 5.05808 | 0.0265309 | 0.0017886 | 8.12436e-05 | 1(Win) | true |
| simdjson (ondemand) | 303.033 | 0.0755243 | 5294.86ms | 264040 | 320 | 1.26033e+08 | 830959 | 0.305824 | 16.7013 | 64.2725 | 13.068 | 0.0944468 | 0.00478753 | 8.95461e-05 | 2(Loss) | true |
