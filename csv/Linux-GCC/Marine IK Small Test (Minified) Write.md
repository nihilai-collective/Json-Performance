
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1538.91 | 0.0450577 | 1026.03ms | 4918 | 4890 | 9221.42 | 3047.72 | 0.00419867 | 3.39603 | 11.3867 | 1.35177 | 0.000703771 | 2.71113e-05 | 9.39747e-06 | 1(Win) | true |
| Jsonifier | 1417.51 | 0.104346 | 1028.81ms | 4604 | 4890 | 51083.3 | 3097.49 | 0.152052 | 3.68327 | 9.55191 | 0.570591 | 0.000314877 | 8.81691e-05 | 5.00587e-05 | 2(Loss) | true |
| Glaze | 1236.27 | 0.0504484 | 1077.53ms | 4604 | 4890 | 15698.1 | 3551.58 | 0.254249 | 4.20672 | 12.8371 | 1.11838 | 0.000890796 | 4.3174e-05 | 1.82112e-05 | 3(Loss) | true |
