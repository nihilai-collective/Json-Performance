
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2798.4 | 0.0816591 | 1072.92ms | 8051 | 4890 | 24546.9 | 2743.72 | 0.102039 | 1.83345 | 8.43709 | 1.37113 | 0.00048111 | 2.16158e-05 | 2.94645e-06 | 1(Win) | true |
| Glaze | 2063.92 | 0.103225 | 1168.32ms | 8051 | 2560 | 37750.6 | 3720.12 | 0.0701665 | 2.48827 | 11.1189 | 2.11253 | 0.00289987 | 2.34831e-05 | 3.20224e-06 | 2(Loss) | true |
| Jsonifier | 1937.74 | 0.10597 | 1197.21ms | 8051 | 4890 | 86214.8 | 3962.36 | 0.0380731 | 2.63537 | 10.0143 | 1.98969 | 0.00373948 | 3.62972e-05 | 1.46561e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1511.64 | 0.0599279 | 1306.33ms | 8051 | 4890 | 45307.2 | 5079.26 | 0.0879732 | 3.37284 | 13.095 | 2.08247 | 0.00282844 | 3.61956e-05 | 9.90617e-06 | 4(Loss) | true |
