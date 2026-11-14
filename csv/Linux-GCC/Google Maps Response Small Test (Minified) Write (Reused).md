
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14332.3 | 0.109818 | 745.868ms | 4390 | 160 | 16.4653 | 292.113 | 0.34351 | 0.409066 | 1.67859 | 0.261503 | 0.00022779 | 1.99317e-05 | 2.84738e-06 | 1(Win) | true |
| simdjson (reflection) | 8693.62 | 0.0975467 | 770.428ms | 4390 | 4890 | 1079.1 | 481.575 | 0.652004 | 0.642041 | 2.4098 | 0.364693 | 0.000227977 | 3.12571e-05 | 1.44873e-05 | 2(Loss) | true |
| Glaze | 4194.83 | 0.246789 | 823.015ms | 4390 | 4890 | 29666.1 | 998.045 | 0.405622 | 1.27822 | 4.36743 | 0.663098 | 0.000231843 | 3.64278e-05 | 1.7981e-05 | 3(Loss) | true |
