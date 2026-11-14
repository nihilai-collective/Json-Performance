
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1521.82 | 0.0726751 | 1032.97ms | 4918 | 160 | 802.684 | 3081.96 | 0.105767 | 3.43042 | 11.3867 | 1.35177 | 0.000758693 | 4.8292e-05 | 1.52501e-05 | 1(Win) | true |
| Jsonifier | 1387.9 | 0.138904 | 1040.66ms | 4604 | 4890 | 94426.3 | 3163.56 | 0.10858 | 3.74607 | 9.55039 | 0.570591 | 0.000317275 | 6.3384e-05 | 2.97154e-05 | 2(Loss) | true |
| Glaze | 1220.46 | 0.0965756 | 1086.45ms | 4604 | 2560 | 30902.8 | 3597.59 | 0.00266027 | 4.27181 | 12.8371 | 1.11838 | 0.000655425 | 4.4798e-05 | 2.16354e-05 | 3(Loss) | true |
