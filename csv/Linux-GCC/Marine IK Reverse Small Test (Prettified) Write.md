
----
### Marine IK Reverse Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8133.1 | 0.0790196 | 307.134ms | 24893 | 80 | 425.6 | 2918.91 | 0.1031 | 0.301779 | 1(Win) | true |
| Glaze | 3772.94 | 0.0737289 | 631.543ms | 24579 | 80 | 1678.54 | 6212.75 | 0.042636 | 0.653183 | 2(Loss) | true |
| simdjson (reflection) | 567.603 | 0.273852 | 4286.81ms | 24893 | 160 | 2.09901e+06 | 41824.7 | 0.225719 | 4.35895 | 3(Loss) | true |
