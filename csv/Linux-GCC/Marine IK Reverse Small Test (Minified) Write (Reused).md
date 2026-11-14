
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1539.37 | 0.100024 | 1029.36ms | 4918 | 160 | 1486.01 | 3046.81 | 0.207573 | 3.39264 | 11.2666 | 1.32168 | 0.000744713 | 3.1771e-05 | 1.01667e-05 | 1(Win) | true |
| Jsonifier | 1469.62 | 0.12031 | 1021.73ms | 4604 | 4890 | 63178.8 | 2987.66 | 0.0165529 | 3.54905 | 9.45091 | 0.539966 | 0.000530525 | 3.69111e-05 | 1.63457e-05 | 2(Loss) | true |
| Glaze | 1353.81 | 0.169648 | 1047.32ms | 4604 | 640 | 19374.5 | 3243.22 | 0.088532 | 3.84772 | 12.2183 | 0.967203 | 0.000561672 | 2.47747e-05 | 9.50261e-06 | 3(Loss) | true |
