
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1530.96 | 0.0486041 | 1028.51ms | 4918 | 2560 | 5675.92 | 3063.55 | 0.193639 | 3.39802 | 11.2666 | 1.32168 | 0.000612307 | 4.63857e-05 | 2.37489e-05 | 1(Win) | true |
| Jsonifier | 1489.08 | 0.0876177 | 1016.52ms | 4604 | 4890 | 32638.3 | 2948.61 | 0.146812 | 3.48782 | 9.45161 | 0.539975 | 0.000520042 | 6.62712e-05 | 3.53121e-05 | 2(Loss) | true |
| Glaze | 1309.66 | 0.0484711 | 1056.98ms | 4604 | 4890 | 12913 | 3352.56 | 0.0263576 | 3.97221 | 12.2183 | 0.967203 | 0.000572944 | 4.34405e-05 | 1.94994e-05 | 3(Loss) | true |
