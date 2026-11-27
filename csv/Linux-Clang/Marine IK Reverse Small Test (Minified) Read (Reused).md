
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 919.329 | 0.165124 | 1312.74ms | 4604 | 2560 | 159216 | 4776 | 0.599085 | 5.59935 | 20.8606 | 4.59731 | 0.00540444 | 0.000109789 | 5.34522e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 788.186 | 0.0797619 | 1393.02ms | 4604 | 4890 | 96541.2 | 5570.66 | 0.223204 | 6.49036 | 25.9035 | 5.29909 | 0.00632903 | 0.000328025 | 0.000211162 | 2(Loss) | true |
| Glaze | 764.535 | 0.15233 | 1413.63ms | 4604 | 640 | 48980.9 | 5742.99 | 0.0768646 | 6.7837 | 29.3901 | 5.86664 | 0.00479576 | 5.26037e-05 | 1.62902e-05 | 3(Loss) | true |
| simdjson (ondemand) | 557.176 | 0.0769698 | 1621.6ms | 4604 | 2560 | 94181.8 | 7880.31 | 0.048726 | 9.11702 | 37.4991 | 6.51412 | 0.00271062 | 0.000131764 | 6.47365e-05 | 4(Loss) | true |
